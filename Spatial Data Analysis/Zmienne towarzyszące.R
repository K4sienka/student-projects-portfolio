library(spatstat)

data(murchison)

#Zadanie 1
gold <- murchison$gold
faults <- murchison$faults

plot(gold, pch=17, cols="gold", main="Murchison Gold and Faults")
plot(faults, add=TRUE, col="red")
legend("topright", legend=c("Gold", "Faults"), 
       col=c("gold", "red"), pch=c(17, NA), lty=c(NA, 1), 
       bty="n", lwd=2)

#Zadanie 2
zu <- distmap(faults)
plot(zu)

#Zadanie 3
plot(gold, add=TRUE, pch=17, cols="gold")

#Zadanie 4
density <- rhohat(gold,zu) #gestosc w zaleznosci od odleglosci
plot(density)
#najwiecej zloz zlota jest bliskiej odleglosci od uskokow

#Zadanie 5
zuf <- distfun(faults)
zuf

#Zadanie 6
odl <- zuf(400000,7000000)
cat("Odległość najbliższego uskoku od zadanego punktu wynosi:",odl,"m.")

#Zadanie 7
plot(zuf)
