#Przykładowe dane
set.seed(123)
x1 <- 1:100
y <- 3*x1 + 10 + rnorm(100, mean=0, sd=30) #Wartości rzeczywiste
y_pred <- 3*x1 + 10 #Predykcje (bez błędu)

#MSE
mse <- mean((y - y_pred)^2)
print(paste("MSE:", mse))

#Wizualizacja
plot(x1, y, col="#7657EE", pch=16, main="Rozkład reszt w modelu regresji liniowej", xlab="X", ylab="Y")
points(x1, y_pred, col="#87A8D9", pch=16)

#Rysowanie błędów
for(i in 1:length(x1)) 
{
  lines(c(x1[i], x1[i]), c(y[i], y_pred[i]), col="black", lty=2) #Linie błędu
}

legend("topleft", legend=c("Wartości rzeczywiste", "Predykcje", "Błąd"), 
       col=c("#7657EE", "#87A8D9", "black"), 
       pch=c(16, 16, NA),
       lty=c(NA, NA, 2))

#---------------------------------------------------
#Przykładowe dane
set.seed(48)
x <- seq(-10, 10, by=0.1)

#Regresja liniowa
y1 <- 2 * x + 3 + rnorm(length(x), mean = 0, sd = 2) #Wartości rzeczywiste
y_pred1 <- 2 * x + 3 #Predykcje

#Regresja liniowa
lm_model <- lm(y1 ~ x)

#Predykcje z modelu liniowego
lm_predict <- predict(lm_model)

#MSE dla regresji liniowej
mse1 <- mean((y1 - lm_predict)^2)
print(paste("MSE dla regresji liniowej:", mse1))

#Wizualizacja
plot(x, y1, col="#7657EE", pch=16, main="Regresja liniowa - MSE", xlab="X", ylab="Y")
abline(lm_model, col="#87A8D9", lwd=2) #Prosta regresji
legend("topleft", legend=c("Wartości rzeczywiste", "Model regresji liniowej"), col=c("#7657EE", "#87A8D9"), pch=16)

#---------------------

#Regresja wielomianowa (stopień 2)
y2 <- 2 * x^2 + 3 * x + 5 + rnorm(length(x), mean = 0, sd = 2)  # #Wartości rzeczywiste
y_pred2 <- 2 * x^2 + 3 * x + 5 #Predykcje
#y2 <- 2 * x + 3 + rnorm(length(x), mean = 0, sd = 2) #Wartości rzeczywiste
#y_pred2 <- 2 * x + 3 #Predykcje

poly_model <- lm(y2 ~ poly(x, 2))  # Użycie funkcji poly() do stopnia 2

#Predykcje z modelu wielomianowego
poly_predict <- predict(poly_model)

#MSE dla regresji wielomianowej
mse2 <- mean((y2 - poly_predict)^2)
print(paste("MSE dla regresji wielomianowej:", mse2))

plot(x, y2, col="#769484", pch=16, main="Regresja wielomianowa - MSE", xlab="X", ylab="Y")
lines(x, poly_predict, col="#FF6347", lwd=2)
legend("topleft", legend=c("Wartości rzeczywiste", "Model regresji wieloliniowej"), col=c("#769484", "#87A8D9"), pch=16)


#------------------------
#Porównanie
plot(x, y1, col=rgb(118/255, 87/255, 238/255, alpha=0.8), pch=16, main="Porównanie regresji liniowej i wielomianowej", xlab="X", ylab="Y")
points(x, y2, col=rgb(118/255, 148/255, 132/255, alpha=0.8), pch=18)
abline(lm_model, col="#87A8D9", lwd=2) 
lines(x, poly_predict, col="#FF6347", lwd=2)  #Krzywa regresji wielomianowej
legend("bottomright", legend=c("Wartości rzeczywiste (liniowe)","Wartości rzeczywiste (wielomianowe)", "Regresja liniowa", "Regresja wielomianowa"),
       col=c("#7657EE","#769484", "#87A8D9", "#FF6347"), pch=c(16, 16, NA, NA), lty=c(NA, NA, 1, 1), lwd=c(NA, NA, 2, 2), cex=0.7) 

#---------------------------------------
#RMSE i MAE
#metryki
mse <- mean((y - y_pred)^2)
rmse <- sqrt(mse)
mae <- mean(abs(y - y_pred)) 

cat("MSE:", mse, "\nRMSE:", rmse, "\nMAE:", mae, "\n")

#Wizualizacja
plot(x1, y, col="#7657EE", pch=16, main="MSE, RMSE i MAE na przykładzie regresji liniowej", xlab="X", ylab="Y")
points(x1, y_pred, col="#87A8D9", pch=16)

#Rysowanie błędów
for(i in 1:length(x)) 
{
  lines(c(x1[i], x1[i]), c(y[i], y_pred[i]), col="black", lty=2) # Linie błędu
}

legend("topleft", legend=c("Wartości rzeczywiste", "Predykcje", "Błąd"), 
       col=c("#7657EE", "#87A8D9", "black"), 
       pch=c(16, 16, NA),
       lty=c(NA, NA, 2))

#Tekst na wykresie
text(x = 10, y = min(y)+200 , 
     labels = paste("MSE:", round(mse, 2), 
                    "\nRMSE:", round(rmse, 2), 
                    "\nMAE:", round(mae, 2)), 
     adj = 0, col = "black")


