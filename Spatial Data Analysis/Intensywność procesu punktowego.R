library(spatstat)

data(murchison)

gold <- murchison$gold
faults <- murchison$faults
greenstone <- murchison$greenstone

plot(greenstone, main="Murchison data", col="lightgreen")
plot(gold, add=TRUE, pch=16,col="gold")
plot(faults, add=TRUE, col="red")
legend("right", legend=c("Greenstone", "Gold", "Faults"), 
       fill=c("lightgreen", "gold", "red"), bty="n")
grid()

class(gold) #ppp sluzy do wyswietlania punktow 2D
class(faults) #psp i list sluzy do wyswietlania segmentow lub linii w 2D
class(greenstone) #owin reprezentuje okno obserwacyjne definujące przestrzen z innymi obiektami

summary(gold) #estymator średniej wynosi 1.924569e-09 punktów na m^2

plot(gold, main='Rozmieszenie punktów', cols='#800000', pch=19, size=0.75)
net <- quadratcount(gold,5, 5) #zliczenie punktow w kwadratach
plot(net,add=TRUE)

#czy dane są rozmieszczone losowo?
test <- quadrat.test(net) #test chi2
cat("Wartość pvalue wynosi", test$p.value, "\n")
#Wartość pvalue jest na tyle mała, że praktycznie zerowa. Zatem punkty z całą pewnością nie są rozmieszczone losowo 
#i istnieje jakiś wzorzec w ich rozkładzie

density_estymator <- density(gold) #estymator jadrowy gestosci

plot(density_estymator,main="Estymator gęstości wykres", lwd=3) #lwd pogrubia ramke przy legendzie
contour(density_estymator, col = heat.colors(13), main = "Izolinie 2D z kolorami", lwd=3) 
persp(density_estymator,theta = 14, phi = 8, shade = 0.3, col = "lightblue",main="3D mapa", xlab='Zmienna X (gold)', ylab='Odległość Y w funkcji jądrowej', zlab='Zakres gęstości') #theta i phi ustawia kat widzenia


