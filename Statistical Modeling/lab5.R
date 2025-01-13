#Zadanie 1 
dane<-read.table("C:/Users/wesol/OneDrive/Pulpit/Studia/Semestr IV/Modelowanie/zanieczyszczenia.txt",header=TRUE) #wczytanie pliku
#head(dane)
#dane

#Zadanie 2
dane <- dane[complete.cases(dane), ]  #complete cases czysci wiersze gdzie występuje NA
dane1 <- subset(dane, select = -c(month, day, hour))
dane1

#Zadanie 3
korelacja <- cor(dane1, method="pearson")
korelacja #wykluczyc pm2.5 i pm10 z powodu wysokich wartosci korelacji

dane2 <- subset(dane1, select = -c(PM2.5, PM10))
dane2

#korelacja1 <- cor(dane2, method="pearson")
#korelacja1

#Zadanie 4
model_liniowy<- lm(TEMP~SO2+NO2+CO+O3,data=dane2) #zmienna niezalezna to temperatura, reszte to zalezne

#Zadanie 5
#a
wspl<-coef(model_liniowy) #wspolczynniki modelu
wspl
#b
RSS<- sum(resid(model_liniowy)^2)
RSE<- sqrt(RSS / (model_liniowy$df.residual))
R2<- summary(model_liniowy)$r.squared
cat("Resztkowa suma kwadratów odchyleń (RSS):", RSS, "\n\n")
cat("Odchylenie standardowe składnika resztkowego (RSE):", RSE, "\n\n")
cat("Współczynnik determinacji (R²):", R2, "\n\n")

#Zadanie 6
przewidywania <- data.frame(SO2=25, NO2=90, CO=2000, O3=50)
przewidywana_temperatura <- predict(model_liniowy, newdata= przewidywania) #predict to regresja wieloraka, pozwala obliczyc regresje dla wiekszej ilosci zmiennych zaleznych (tu areozole)
cat("\nPrzewidywana temperatura dla wybranych koncentracji areozoli to:",przewidywana_temperatura, "\n\n")
