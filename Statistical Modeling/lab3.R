library(mosaic)
library(ggplot2)

data(airquality)
head(airquality)
brak <- sum(is.na(airquality))
brak

newairquality <- na.omit(airquality) #dane bez na
str(newairquality)                   #sprawdzenie struktury danych
 
#Zadanie 5
kwartyle<-quantile(newairquality$Ozone, c(0.25, 0.75)) #pierwszy i trzeci kwartyl
odstep<-IQR(newairquality$Ozone)  #odsyep miedzy kwartylowy
#grania dolna i górna
granice<-(c(kwartyle[1]-1.5*odstep,kwartyle[2]+1.3*odstep))

#usunięcie wartości odstających z danych
clean<-subset(newairquality,Ozone>=granice[1] & Ozone<=granice[2])

ggplot(data=clean, mapping=aes(y=Ozone)) +
    geom_boxplot(colour="brown") +
    labs(title="Wykres pudełkowy dla Ozonu")

#Zadanie 6
srednia6<-mosaic::mean(Ozone~Wind,data=newairquality)  #srednia za pomocą mosaic
print(round(srednia6,2))

#Zadanie 7
srednia7<-aggregate(Ozone~Wind,data=newairquality,FUN=mean)  #srednia za pomocą aggregate

ggplot(data=srednia7, mapping=aes(x=Wind,y=Ozone)) +
  geom_point(color="blue", size=2.5) + 
  geom_line(color="turquoise",size=1.1) +
  labs(title="Średnia wartość ozonu dla różnych prędkości wiatru",x="Prędkość wiatru",y="Średnia wartość ozonu")


#Zadanie 8
#funkcja mutate do przeksztalcenia Fahrenheita na Celsjusza
newairquality<-mutate(newairquality, Temp=5/9*(Temp-32))
print(round(newairquality,2))


#Zadanie 9
#a) zbior danych wedlug miesiecy
monthly<-split(newairquality,newairquality$Month)
monthly

#df do zapisywania współczynników regresji i determinacji
df<-data.frame(Miesiąc=integer(),Wyraz_wolny=double(),Współczynnik_kierunkowy=double(),Współczynnik_determinacji=double())

#model regresji liniowej dla każdego miesiąca i zapisanie współczynników
for (m in names(monthly)) 
  {
  model<-lm(Temp~Ozone,data=monthly[[m]])
  wolny<-coef(model)[1] #wyraz wolny to 1 kolumna regresji
  kierunkowy<-coef(model)[2] #kierunkowy to 2
  determinacji<-summary(model)$r.squared #z podsumowania statystycznego regresji bierzemy wspolczynnik determinacji
  #dodanie danych
  df<-rbind(df,data.frame(Miesiąc=as.numeric(m), Wyraz_wolny=wolny,
                          Współczynnik_kierunkowy=kierunkowy, Współczynnik_determinacji=determinacji))
  row.names(df)<-NULL  #usuwa nazwy wierszy
}
View(df)
