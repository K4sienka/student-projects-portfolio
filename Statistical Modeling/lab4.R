library(ggplot2)

#Zadanie 1
dane<-read.table("C:/Users/wesol/OneDrive/Pulpit/Studia/Semestr IV/Modelowanie/dane.txt",header=TRUE) #wczytanie pliku

zad1<-ggplot(data=dane, mapping=aes(x=X, y=Y))+
  geom_point(color="blue")+
  labs(title="Pomiary pewnych geofizycznych pomiarów X i Y")
zad1

#Zadanie 2
model<-lm(Y~X,data=dane)
summary(model)

#a. Jaki jest błąd między prognozą modelu a rzeczywistymi wynikami?
residuals(model)  #residual to roznica miedzy obserwowaną wartoscią a przewidywaną przez model

#b. Podaj wyestymowane parametry modelu
coef(model) #coef sluzy do pobierania wspolczynnikow

#c. Oblicz wartość współczynnika R2 i zinterpretuj tą wartość.
summary(model)$r.squared
#około 79.5% zmienności jest wyjaśnione przez model regresji liniowej, model jest stosunkowo dobrym dopasowaniem do danych

#Zad3
zad3<-zad1+geom_smooth(method="lm",color="brown",se=FALSE) #dodanie linii regresji
zad3

#Zad4
#funkcja do generowania krzywej regresji wielomianowej dla danego stopnia
regresja_wielomianowa<-function(dane, stopien) 
  {
    lm(Y ~ poly(X, stopien, raw = TRUE), data = dane)
  }

#stopnie od 2 do 10
modele<-lapply(2:10, function(i) regresja_wielomianowa(dane, i))
wykres<-ggplot(dane, aes(X, Y)) + geom_point()

#dodawanie krzywych regresji do wykresu
wykres_krzywe<-wykres+lapply(2:10, function(i) 
  {
    geom_smooth(method = "lm", formula = y ~ poly(x, i, raw = TRUE), se = FALSE, color = rgb(runif(1), runif(1), runif(1)))
  })
wykres_krzywe

#Zadanie 5
#funkcja do obliczania współczynników regresji i metryk
wynik<- function(model) {
  wspolczynniki<-coef(model) 
  RSS<-sum(resid(model)^2)
  R2<-summary(model)$r.squared
  return(list(wspolczynniki = wspolczynniki, RSS = RSS, R2 = R2))
}

#obliczenia dla kazdego modelu
metryki <- lapply(modele,wynik)

# Wyświetlenie wyników
for (i in 2:10) 
  {
  cat("Stopień", i, ":\n")
  cat("Współczynniki regresji:", metryki[[i - 1]]$wspolczynniki, "\n")
  cat("Resztkowa suma kwadratów odchyleń:", metryki[[i - 1]]$RSS, "\n")
  cat("Współczynnik determinacji:", metryki[[i - 1]]$R2, "\n")
  cat("\n")
}







