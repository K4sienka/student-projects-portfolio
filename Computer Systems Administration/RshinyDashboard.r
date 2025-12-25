library(shiny)
library(leaflet)
library(dplyr)
library(readr)
library(rnaturalearth)
library(rnaturalearthdata)
library(sf)
library(plotly)
library(dplyr)


# Wczytaj dane z CSV
df <- read_csv("df_data.csv")
# Dodaj kolumnę Year: powtarzaj 2003–2023 dla każdego kraju
df$Year <- rep(2003:2023, times = nrow(df) / 21)

# Wczytaj dane o krajach do mapy
world <- ne_countries(scale = "medium", returnclass = "sf") %>%
  select(iso_a3, name, geometry)


# UI
ui <- fluidPage(
  tags$head(
    tags$link(rel = "stylesheet", type = "text/css", href = "custom.css")
  ),
  div(class = "title-custom","GLOBAL GDP GROWTH (%) BY YEAR"),
  sidebarLayout(
    sidebarPanel(
      div(class = "sidebar",
          h4("SELECT YEAR:"),
          div(class = "year-text", textOutput("selected_year")),
          sliderInput("rok", NULL,
                      min = min(df$Year), max = max(df$Year),
                      value = 2010, step = 1, sep = "",
                      animate = FALSE,
                      ticks = TRUE,
                      dragRange = FALSE,
                      width = "100%")
      ),
      div(class = "summary-box",
          uiOutput("stats")
      )
      
    ),
    mainPanel(
      div(
        style = "width: 840px; height: 650px;  margin-left: 80px;",
        leafletOutput("mapa", width = "100%", height = "100%")
      )
    )
  )
)

# SERVER
server <- function(input, output, session) {
  output$selected_year <- renderText({
    input$rok
  })
  output$stats <- renderUI({
    dane <- df %>%
      filter(Year == input$rok, !is.na(`GDP growth (%)`)) %>%
      left_join(
        world %>%
          st_drop_geometry() %>%
          select(iso_a3, name) %>%
          distinct(iso_a3, .keep_all = TRUE),
        by = c("Country Code" = "iso_a3")
      )
    
    if (nrow(dane) == 0) {
      return(h5("No data available for selected year."))
    }
    
    top_country <- dane %>% arrange(desc(`GDP growth (%)`)) %>% slice(1)
    worst_country <- dane %>% arrange(`GDP growth (%)`) %>% slice(1)
    
    tagList(
      tags$h4("STATISTICS:", class = "sidebar-title"),
      tags$p(HTML("<b>Countries with data:</b> "), nrow(dane)),
      tags$p(HTML("<b>Avg GDP Growth:</b> "), round(mean(dane$`GDP growth (%)`), 2), "%"),
      tags$p(HTML("<b>Median Growth:</b> "), round(median(dane$`GDP growth (%)`), 2), "%"),
      tags$p(HTML("<b>Highest GDP Growth:</b> "), paste0(top_country$name, " (", round(top_country$`GDP growth (%)`, 2), "%)")),
      tags$p(HTML("<b>Lowest GDP Growth:</b> "), paste0(worst_country$name, " (", round(worst_country$`GDP growth (%)`, 2), "%)"))
    )
  })
  
  
  output$mapa <- renderLeaflet({
    dane <- df %>% filter(Year == input$rok)
    mapa <- left_join(world, dane, by = c("iso_a3" = "Country Code"))
    
    pal <- colorNumeric("YlGnBu", domain = mapa$`GDP growth (%)`, na.color = "transparent")
    
    leaflet(mapa, options = leafletOptions(
      dragging = FALSE,
      zoomControl = FALSE,
      scrollWheelZoom = FALSE,
      doubleClickZoom = FALSE,
      boxZoom = FALSE,
      touchZoom = FALSE,
      worldCopyJump = FALSE,
      minZoom = 1.55,
      maxZoom = 1.55,
      maxBounds = list(
        list(-85, -180), list(85, 180)
      ),
      maxBoundsViscosity = 1.0
    )) %>%
      setView(lng = 15, lat = 15, zoom = 1.55) %>%
      addProviderTiles("CartoDB.Positron") %>%
      addProviderTiles("CartoDB.PositronOnlyLabels") %>%  # <-- dodaje nazwy kontynentów
      addPolygons(
        fillColor = ~pal(`GDP growth (%)`),
        fillOpacity = 0.8,
        color = "#BDBDC3",
        weight = 1,
        popup = ~paste0(name, "<br><b>GDP growth:</b> ", round(`GDP growth (%)`, 2), " %")
      ) %>%
      addLegend("bottomleft", pal = pal, values = ~`GDP growth (%)`,
                title = paste("GDP growth in", input$rok), opacity = 1)
  })
  
}

# Run the app
shinyApp(ui, server)

