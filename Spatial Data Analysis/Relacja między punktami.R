library(spatstat)

#Zadanie 1
lambda1 <- 0.5
u <- 0.8
#a)
p_poisson <- rpoispp(lambda1,win=disc(10))
#b)
p_regular <- rStrauss(lambda1, gamma=0.3,  W=disc(10))
#c)
p_cluster <- rMatClust(kappa=lambda1,scale=1,mu=u,win=disc(10))

par(mfrow = c(1, 3)) #dla 3 wykresow
plot(p_poisson, cols="lightblue", pch=17)
plot(p_regular, cols="lightpink", pch=17)
plot(p_cluster, cols="brown", pch=17)


#Zadanie 2
p <- nndist(p_poisson)
hist(p, main="Dla rozkładu niezależnego")
r <- nndist(p_regular)
hist(r, main="Dla rozkładu regularnego")
c <- nndist(p_cluster)
hist(c, main="Dla rozkładu pogrupowanego")


#Zadanie 3
odl_p <- Gest(p_poisson)
odl_r <- Gest(p_regular)
odl_c <- Gest(p_cluster)
plot(odl_p)
plot(odl_r)
plot(odl_c)

#Zadanie 4
k_p <- Kest(p_poisson,correction = c("border"))
k_r <- Kest(p_regular,correction = c("border"))
k_c <- Kest(p_cluster,correction = c("border"))
plot(k_p)
plot(k_r)
plot(k_c)

#Zadanie 5
d_p <- distmap(p_poisson)
d_r <- distmap(p_regular)
d_c <- distmap(p_cluster)
plot(d_p)
plot(d_r)
plot(d_c)


