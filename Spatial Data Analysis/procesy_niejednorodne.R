library(spatstat)

#Zad1
data("lansing")
str(lansing)
plot(lansing, size = 0.5, main = "Rozmieszczenie wszystkich gatunków drzew")

unique(lansing$marks)  #gatunki
plot(split(lansing), main = "Rozmieszczenie gatunków drzew osobno")

#Zad2
split_lansing <- split(lansing)
blackoak <- split_lansing$blackoak
maple <- split_lansing$maple

doak <- density(blackoak)
dmaple <- density(maple)

par(mfrow = c(1, 2))
plot(doak, main = "Density Black Oak") #skoncentrowana intensywność w danym miejscu
points(blackoak, col = "lightblue")
plot(dmaple, main = "Density Maple") #dosyć równomierne rozmieszczenie
points(maple, col = "lightblue")
par(mfrow = c(1, 1))

#Zad3
poisson_blackoak <- ppm(blackoak, ~1) #jednorodny proces poissona
poisson_maple <- ppm(maple, ~1)
poisson_maple
poisson_blackoak

#Zad4
`blackoak_trend <- ppm(blackoak, ~x + y) #zmiana intensywnosci log-liniowo
par(mfrow = c(1, 1))
plot(blackoak_trend, main = "Trend Black Oak")
points(blackoak, col="lightblue")

residuum <- residuals(blackoak_trend)
plot(residuum, main = "Residuals Black Oak")
points(blackoak, pch = 16, col = "blue")

#Zad5
set.seed(123)
rand_blackoak <- rmh(blackoak_trend)
plot(rand_blackoak, size=0.5,main = "Random Black Oak")

randd_blackoak <- density(rand_blackoak) #funkcja intensywnosci
plot(randd_blackoak, main = "Density random Black Oak")
points(rand_blackoak, col = "lightblue")

#Zad6
diagnose.ppm(blackoak_trend)




