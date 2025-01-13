#Zadanie 1
library(ggplot2)
data(quakes)
head(quakes)

#trzesienia o magnitudzie większej niż 4.0
quakes4<- quakes[quakes$mag > 4.0, ]

#mapa występowania epicentrów
ggplot() +
  geom_point(data = quakes4,aes(x = long, y = lat), color = "violet", size=0.9) +
  labs(title = "Wstępowania epicentrów trzęsień ziemi w Fidżi",
       x = "Długość geograficzna",
       y = "Szerokość geograficzna")


#Zadanie 2
ggplot(quakes, aes(x = mag, y = stations)) +
  geom_point(color = "blue", size=0.9) +
  labs(title = "Ilość stacji a magnituda trzęsień ziemi",
       x = "Magnituda",
       y = "Ilość stacji")


#Zadanie 3
#maksymalna wartosc o jaką mogą przemieścić się punkty
#dodanie szumu
quakes$szum <- jitter(quakes$mag, amount = 0.05)

ggplot(quakes, aes(x = szum, y = stations)) +
  geom_point(size=0.9) +
  labs(title = "Ilość stacji a magnituda trzęsień ziemi",
       x = "Magnituda",
       y = "Ilość stacji") +
  theme( panel.grid.major = element_blank(),  #usuwa główne linie siatki
         panel.background = element_rect(fill = "white", colour = "black"))  #tło panelu


#Zadanie 4
statystyki <- c(
  suma = sum(quakes$szum),
  srednia = mean(quakes$szum),
  mediana = median(quakes$szum),
  wariancja = var(quakes$szum),
  odchylenie_std = sd(quakes$szum),
  min = min(quakes$szum),
  max = max(quakes$szum)
)
statystyki


#Zadanie 5
#obliczanie kwartyli i rozstępu międzykwartylowego
kwartyle <- quantile(quakes$szum, c(0.25, 0.50, 0.75))
rozstep <- IQR(quakes$szum)
cat("Kwartyle:", kwartyle,"\nRozstęp miedzykwartylowy",rozstep)

#Zadanie 6
ggplot(quakes, aes(y = mag)) +
  geom_boxplot(color = "darkorange") +
  labs(title = "Wykres pudełkowy dla magnitudy",
       y = "Magnituda")


#Zadanie 7
kowariancja <- cov(quakes$mag, quakes$stations)
korelacja <- cor(quakes$mag, quakes$stations)
cat("Kowariancja: ", kowariancja,"\nWspółczynnik korelacji: ",korelacja)


#Zadanie 8
#tworzenie modelu regresji liniowej
model <- lm(stations ~ mag, data = quakes)


#Zadanie 9
#wykres z linią regresji
ggplot(quakes, aes(x = mag, y = stations)) +
  geom_point(color = "turquoise", size=0.9) +
  geom_smooth(method = "lm", se = FALSE, color = "black") +  #dodanie lini regresji
  labs(title = "Ilość stacji a magnituda trzęsień ziemi",
       x = "Magnituda",
       y = "Ilość stacji")


#Zadanie 10
#resztkowa suma kwadratów odchyleń
rss <- sum(residuals(model)^2)  #residual to roznica miedzy obserwowaną wartoscią a przewidywaną przez model

#odchylenie standardowe składnika resztkowego
rse <- sqrt(rss / (model$df.residual)) #df.residual to stopnie swobody n-p

# Obliczmy Współczynnik zbliżoności
ogolna_zmiennosc <- sum((quakes$stations - mean(quakes$stations))^2)
phi_sq <- rss / ogolna_zmiennosc

# Obliczmy Współczynnik determinacji (R²)
determination <- 1 - phi_sq

# Wyświetlmy wyniki
cat("Resztkowa suma kwadratów odchyleń (RSS):", rss, "\n")
cat("Odchylenie standardowe składnika resztkowego (RSE):", rse, "\n")
cat("Współczynnik zbliżoności (φ²):", phi_sq, "\n")
cat("Współczynnik determinacji (R²):", determination, "\n")

