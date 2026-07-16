#Temat projektu: Własny geom do rysowania zakresu wiatrów huraganu
#Autor: Katarzyna Wesołowska
#Dane: ebtrk_atlc_1988_2015.txt
#Wynik: ike_hurricane_map.png

library(ggplot2)
library(dplyr)
library(tidyr)
library(geosphere) #destPoint() do wyznaczania punktów polygonu
library(maps) #mapa USA
library(patchwork)

#Wczytanie danych
ext_tracks_widths <- c(7, 10, 2, 2, 3, 5, 5, 6, 4, 5, 4, 4, 5, 3, 4, 3, 3, 3,
                       4, 3, 3, 3, 4, 3, 3, 3, 2, 6, 1)

ext_tracks_colnames <- c("storm_id", "storm_name", "month", "day", "hour", "year", "latitude", 
                         "longitude", "max_wind", "min_pressure", "rad_max_wind", "eye_diameter",
                         "pressure_1", "pressure_2", 
                         paste("radius_34", c("ne", "se", "sw", "nw"), sep = "_"),
                         paste("radius_50", c("ne", "se", "sw", "nw"), sep = "_"),
                         paste("radius_64", c("ne", "se", "sw", "nw"), sep = "_"),
                         "storm_type", "latitude", "hemisphere")

hurricane_data <- utils::read.fwf("ebtrk_atlc_1988_2015.txt", 
                           widths = ext_tracks_widths, 
                           col.names = ext_tracks_colnames)

head(hurricane_data)
head(hurricane_data[, c("storm_name", "year", "month", "day", "hour",
                        "latitude", "longitude",
                        "radius_34_ne", "radius_34_se", "radius_34_sw", "radius_34_nw")])

str(hurricane_data)


#Uporzadkowanie danych
#storm_id = nazwa + rok
#longitude ma ujemne wartości dla polkuli zachodniej
#latitude zostaje bez zmian, bo dane dotyczą polkuli polnocnej
#date = year + month + day + hour
#radius_*_* -> 34/50/64 to poziom prędkości wiatru, a ne/se/sw/nw oznacza cwiartke huraganu

unique(hurricane_data$hour)[1:10]
unique(hurricane_data$storm_name)[1:10] #zbedne spacje

hurricanes_cleaned <- hurricane_data %>%
  dplyr::mutate(
    storm_name = trimws(storm_name), #usuwa zbedne spacje
    storm_id = paste(storm_name, year, sep = "-"),
    longitude = -longitude,
    #tworzenie typu datatime
    date = as.POSIXct(paste(year, month, day, hour),format = "%Y %m %d %H",tz = "UTC")
    )

hurricanes_longer <- hurricanes_cleaned %>%
  tidyr::pivot_longer( #przeksztalcenie radius_* do formatu long
    cols = starts_with("radius_"),
    names_to = c("wind_speed", "quadrant"),
    names_pattern = "radius_(34|50|64)_(ne|se|sw|nw)",
    values_to = "radius"
  )

hurricanes_longer %>%
  dplyr::select(storm_name, year, date, wind_speed, quadrant, radius) %>%
  head(12)


hurricanes_wider <- hurricanes_longer %>%
  tidyr::pivot_wider(
    names_from = quadrant,
    values_from = radius
    )

hurricanes_wider %>%
  dplyr::select(storm_name, year, date, wind_speed, ne, se, sw, nw) %>%
  head(12)

#radius nie moze byc ujemny
hurricanes <- hurricanes_wider %>%
  dplyr::filter(ne >= 0, se >= 0, sw >= 0, nw >= 0)

#szukam IKE
hurricanes %>%
  dplyr::filter(grepl("IKE", storm_name)) %>%
  dplyr::distinct(storm_name, year)

#wybieram IKE-2008
ike_all <- hurricanes %>%
  dplyr::filter(storm_name == "IKE", year == 2008)

#sensowny moment blisko USA, im blizej long -90 tym blizej USA
ike_all %>%
  dplyr::distinct(date, latitude, longitude, max_wind) %>%
  dplyr::arrange(date) %>%
  tail(15)

ike <- ike_all %>%
  dplyr::filter(date == as.POSIXct("2008-09-12 00:00:00", tz = "UTC"))

#3 wiersze, kazde dla poziomów wiatru 34, 50 i 64
ike %>%
  dplyr::select(storm_name, year, date, latitude, longitude, wind_speed, ne, se, sw, nw)


#Z promieni NE/SE/SW/NW wyliczam punkty zasiegu huraganu
#funkcja przyjmujaca: srodek huraganu, 4 cwiartki, ilosc pkt na luk, skalowanie promieni
hurricane_polygon <- function(lon, lat, r_ne, r_se, r_sw, r_nw, n_points = 30, scale_radii = 1)
{
  #jesli promien pusty to 0, inaczej skalujemy
  scale_ne <- ifelse(is.na(r_ne), 0, r_ne) * scale_radii
  scale_se <- ifelse(is.na(r_se), 0, r_se) * scale_radii
  scale_sw <- ifelse(is.na(r_sw), 0, r_sw) * scale_radii
  scale_nw <- ifelse(is.na(r_nw), 0, r_nw) * scale_radii
  
  #katy dla cwiartek do luku z wielu punktow
  ang_ne <- seq(0, 90, length.out = n_points)
  ang_se <- seq(90, 180, length.out = n_points)
  ang_sw <- seq(180, 270, length.out = n_points)
  ang_nw <- seq(270, 360, length.out = n_points)
  
  #funkcja do luku
  make_arc <- function(angles, rad)
  {
    #jesli brak promienia to punkt srodka
    if (rad <= 0) 
    {
      matrix(rep(c(lon, lat), each = length(angles)), ncol = 2, byrow = FALSE)
    } 
    else 
    { 
      #wspolrzedne punktow (+mile na metry -> *1852) -> pkt start, jaki kierunek (kat) i w jakiej odleglosci
      geosphere::destPoint(p = c(lon, lat), b = angles,d = rad * 1852)
    }
  }
  
  #liczenie lukow dla wszystkich cwiartek
  arch_ne <- make_arc(ang_ne, scale_ne)
  arch_se <- make_arc(ang_se, scale_se)
  arch_sw <- make_arc(ang_sw, scale_sw)
  arch_nw <- make_arc(ang_nw, scale_nw)
  
  #tworzenie polygonu z lukow
  poly <- rbind(
    arch_ne,
    arch_se[-1, , drop = FALSE], #-1 zeby nie powielac stykniec na granicach cwiartek
    arch_sw[-1, , drop = FALSE],
    arch_nw[-1, , drop = FALSE]
  )
  
  #wynik
  data.frame(x = poly[, 1], y = poly[, 2])
}

#test mojej funkcji
poly_34 <- hurricane_polygon(
  lon = ike$longitude[1],
  lat = ike$latitude[1],
  r_ne = ike$ne[1],
  r_se = ike$se[1],
  r_sw = ike$sw[1],
  r_nw = ike$nw[1]
)

head(poly_34)

#test polygon ggplotem dla 34
ggplot2::ggplot(poly_34, aes(x = x, y = y)) +
  ggplot2::geom_polygon(fill = "red", color = "black", alpha = 0.5) +
  ggplot2::coord_fixed()


#tworzenie wlasnego obiektu typu ggproto w ggplot2
#Ten stat liczy granicę huraganu z danych wejściowych
StatHurricane <- ggplot2::ggproto(
  "StatHurricane", #nazwa nowego obiektu
  ggplot2::Stat, #dziedziczy po stat
  required_aes = c("x", "y", "r_ne", "r_se", "r_sw", "r_nw"),  #co wymagac ma do podania w aes
  
  #bierze dane jednej obserwacji huraganu i zamienia je na punkty polygonu do narysowania
  #przyjmuje: dane wejsciowe, ile pkt ma luk, skalowanie promieni (scales nie uzywane)
  compute_group = function(data, scales, points = 30, scale_radii = 1) 
  {
    #wywolanie wlasnej funkcji
    #dla danej grupy (34, 50, 64) wyciaga srodek i 4 promienie w 4 kierunkach
    poly_df <- hurricane_polygon(
      lon = data$x[1],
      lat = data$y[1],
      r_ne = data$r_ne[1],
      r_se = data$r_se[1],
      r_sw = data$r_sw[1],
      r_nw = data$r_nw[1],
      n_points = points,
      scale_radii = scale_radii
    )
    
    #polygon musi miec kolor wypelnienia, obrys i beda 3 grupy wiatru
    poly_df$fill <- data$fill[1]
    poly_df$colour <- data$colour[1]
    poly_df$group <- data$group[1]
    
    poly_df #wynik
  }
)


#funkcja do rysowania huraganu
#mapping = null -> mozna przekazac estetyke przez aes()
#data = null -> mozna przekazac dane bez uzycia aes()
#position = "identity" -> nie przesuwaj automatycznie
#... -> dodatkowe argumenty (np alpha)
#na.rm = false -> nie usuwac NA 
#show.legend = na -> wyswietlanie legenda
#inherit.aes = true -> moze miec estetyke z samego ggplot()
geom_hurricane <- function(mapping = NULL, data = NULL, position = "identity", ..., points = 30, 
                           scale_radii = 1, na.rm = FALSE, show.legend = NA, inherit.aes = TRUE) 
{
  ggplot2::layer(
    data = data,
    mapping = mapping,
    stat = StatHurricane,         #liczenie punktow polygonu
    geom = ggplot2::GeomPolygon,  #rysowanie polygonu
    position = position,
    show.legend = show.legend,
    inherit.aes = inherit.aes,
    params = list(
      points = points,
      scale_radii = scale_radii,
      na.rm = na.rm,
      ...
    )
  )
}

#test nowego geomu bez mapy
ggplot(data = ike) +
  geom_hurricane(
    aes(
      x = longitude,
      y = latitude,
      r_ne = ne,
      r_se = se,
      r_sw = sw,
      r_nw = nw,
      fill = wind_speed,
      colour = wind_speed,
      group = wind_speed
    ),
    alpha = 0.5
  ) +
  ggplot2::scale_colour_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::scale_fill_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::coord_fixed()

#mapa USA
usa_map <- ggplot2::map_data("state")

base_map <- ggplot() +
  ggplot2::geom_polygon(
    data = usa_map,
    aes(x = long, y = lat, group = group),
    fill = "grey95",
    color = "grey70",
    linewidth = 0.2
  ) +
  ggplot2::coord_quickmap(
    xlim = c(-95, -80),
    ylim = c(22, 32)
  ) +
  ggplot2::theme_minimal() +
  ggplot2::theme(
    panel.grid.minor = element_blank(),
    plot.title = element_text(size = 11, face = "bold"),
    plot.subtitle = element_text(size = 9)
  )

#geom na mapie i z testem skali
ike_map_full <- base_map +
  geom_hurricane(
    data = ike,
    aes(
      x = longitude,
      y = latitude,
      r_ne = ne,
      r_se = se,
      r_sw = sw,
      r_nw = nw,
      fill = wind_speed,
      colour = wind_speed,
      group = wind_speed
    ),
    alpha = 0.6
  ) +
  ggplot2::scale_colour_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::scale_fill_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::labs(
    title = "scale_radii = 1",
    x = "Longitude",
    y = "Latitude"
  )

ike_map_half <- base_map +
  geom_hurricane(
    data = ike,
    aes(
      x = longitude,
      y = latitude,
      r_ne = ne,
      r_se = se,
      r_sw = sw,
      r_nw = nw,
      fill = wind_speed,
      colour = wind_speed,
      group = wind_speed
    ),
    alpha = 0.6,
    scale_radii = 0.5
  ) +
  ggplot2::scale_colour_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::scale_fill_manual(
    name = "Wind speed (kts)",
    values = c("34" = "red", "50" = "orange", "64" = "yellow")
  ) +
  ggplot2::labs(
    title = "scale_radii = 0.5",
    x = "Longitude",
    y = "Latitude"
  )

#legenda
comparison_plot <- ike_map_full + ike_map_half +
  patchwork::plot_layout(guides = "collect") &
  ggplot2::theme(legend.position = "right")

comparison_plot

#zapis
ggplot2::ggsave(
  filename = "ike_hurricane_compare.png",
  plot = comparison_plot,
  width = 12,
  height = 5,
  dpi = 300
)