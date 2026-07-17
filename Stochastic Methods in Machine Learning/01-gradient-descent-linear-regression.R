set.seed(123)

x <- rnorm(100)
y <- 2*x + 5 + rnorm(100, sd =0.2) #waga 2, bias 5

x_bias <- cbind(1,x) #pierwsza kolumna bias, druga cecha

w <- c(0,0) #bias i waga cechy

#Zadanie 4
learning_rate <- 0.01 #krok w gradient descent
dl <- length(y)

y_pred <- x_bias %*% w #przewidywane wartosci, czyli y_pred = bias + waga*xi
gradient <- (2 / dl) * t(x_bias) %*% (y_pred - y) #wzor na gradient: 2/n wspl. pochodnej z MSE; transponowane x_bias; wektor bledow
w <- w - learning_rate * as.vector(gradient) #aktualizacja wag: obecne - wielkosc kroku*griadent (odejmujemy bo chcemy malujeacy blad)

#zadanie 5
w <- c(0, 0) #od nowa
n <- 100 #ilosc iteracji
losses <- numeric(n) #zapisywanie strat z kazdej iteracji

for (epoch in 1:n) 
{
  y_pred <- x_bias %*% w #przewidywanue
  losses[epoch] <- mean((y_pred - y)^2) #sredni blad dla danej iteracji -> strata MSE
  
  gradient <- (2 / n) * t(x_bias) %*% (y_pred - y)
  w <- w - learning_rate * as.vector(gradient)
}
cat("Wyuczone wagi:\n")
cat("bias =", w[1], "\n")
cat("waga =", w[2], "\n")

#Zadanie 6
#wykres straty
plot(losses, type = "l", xlab = "Iteracja", ylab = "MSE - strata", main = "Wykres strat")
#punkty danych
plot(x, y, pch = 16, cex=0.8, xlab = "x", ylab = "y", main = "Dane i linia dopasowania", col = 'orange')
abline(a = 5, b = 2, lty = 2, lwd = 2, col = 'blue') #oczekiwana
abline(a = w[1], b = w[2], lwd = 2, col = 'red') #przewidywana
legend("topleft", legend = c("Oczekiwanie", "Przewidywanie"), col = c("blue","red"), lty = c(2, 1), lwd = 2)


#Zadanie 7
learning_rates <- c(1e-6, 1e-5, 1e-4, 1e-3, 1e-2, 1e-1)

wyniki <- data.frame(alpha = learning_rates, bias = NA, weight = NA, final_loss = NA)

par(mfrow = c(2, 3)) #6 wykresow na raz

for (i in 1:length(learning_rates)) #trening dla kazdego learning_rate
{
  learning_rate <- learning_rates[i]
  w <- c(0, 0)          #wagi od zera
  losses <- numeric(n)  #strata od nowa
  
  for (epoch in 1:n) #trening
  {
    y_pred <- x_bias %*% w
    losses[epoch] <- mean((y_pred - y)^2)
    
    gradient <- (2 / n) * t(x_bias) %*% (y_pred - y)
    w <- w - learning_rate * as.vector(gradient)
  }
  
  plot(losses, type = "l", main = paste("temp uczenia się =", learning_rate), xlab = "Iteracja", ylab = "Strata") #wykresy strat
  
  #zapis koncowych wynikow
  wyniki$bias[i] <- w[1]
  wyniki$weight[i] <- w[2]
  wyniki$final_loss[i] <- losses[n]
}

par(mfrow = c(1, 1))

wyniki
#Male tempo uczenia daje bardzo wolna nauke, a wieksze znaczaco przyspiesza. W tym przypadku najlepsze wyniki daje 0.1, bo strata spada najszybciej.

#Zadanie 8
learning_rate <- 0.01
iters <- c(10, 100, 1000)

results_iters <- data.frame(epochs = iters, bias = NA, weight = NA, final_loss = NA, distance_to_true = NA)

par(mfrow = c(1, 3))

for (i in 1:length(iters)) 
{
  iteracja <- iters[i]
  w <- c(0, 0)
  losses <- numeric(iteracja)
  
  for (epoch in 1:iteracja) 
  {
    y_pred <- x_bias %*% w
    losses[epoch] <- mean((y_pred - y)^2)
    
    gradient <- (2 / n) * t(x_bias) %*% (y_pred - y)
    w <- w - learning_rate * as.vector(gradient)
  }
  
  plot(losses, type = "l", main = paste("epoki =", iteracja), xlab = "Iteracja", ylab = "Strata")
  
  results_iters$bias[i] <- w[1]
  results_iters$weight[i] <- w[2]
  results_iters$final_loss[i] <- losses[iteracja]
  results_iters$distance_to_true[i] <- sqrt((w[1] - 5)^2 + (w[2] - 2)^2) #odleglosc od prawdziwych wag
}

par(mfrow = c(1, 1))

results_iters
#Wraz ze wzrostem liczby epok strata maleje, ale po pewnym czasie wykres się wyplaszcza
#Najwieksza poprawa nastepuje na poczatku treningu, a dalsze zwiekszanie liczby epok daje już niewielkie korzysci


#zadanie 9
bias_vals <- seq(-1, 7, length.out = 100) #100 rozne wartosci biasu od -1 do 7
waga_vals <- seq(-1, 4, length.out = 100) #100 wag od -1 do 4

loss_matrix <- matrix(0, nrow = length(bias_vals), ncol = length(waga_vals)) #macierz strat na pary bias, waga

for (i in 1:length(bias_vals)) #po roznych biasach i wagach
{
  for (j in 1:length(waga_vals)) 
  {
    w_iter <- c(bias_vals[i], waga_vals[j])     #wektor wag dla danej iteracji
    y_pred <- x_bias %*% w_iter                 #przewidywania dla danej iteracji
    loss_matrix[i, j] <- mean((y_pred - y)^2)   #zapis danego MSE do macierzy strat
  }
}

w_start <- c(0, 0)      #punkt startowy gradientu
w <- c(0, 0)            #startowe wagi i temp uczenia
learning_rate <- 0.01

for (epoch in 1:100) #trening
{
  y_pred <- x_bias %*% w
  gradient <- (2 / n) * t(x_bias) %*% (y_pred - y)
  w <- w - learning_rate * as.vector(gradient)
}

w_end <- w         #zapis koncowych wyuczonych wag
w_true <- c(5, 2)  #prawdziwe wagi

#wykres konturowy funkcji straty
contour(waga_vals, bias_vals, loss_matrix, xlab = "Waga", ylab = "Bias", main = "Loss landscape")

points(w_start[2], w_start[1], pch = 16, col = "violet", cex = 1.2) #punkt startowy
points(w_end[2], w_end[1], pch = 16, col = "green", cex = 1.2)      #punk po gradiencie
points(w_true[2], w_true[1], pch = 8, col = "cyan", cex = 1.2)      #prawdziwe wagi

legend("bottomright", legend = c("Start", "Koniec", "Prawdziwe wagi"), col = c("violet", "green", "cyan"), pch = c(16, 16, 8), cex = 0.7)

#minimum funkcji straty znajduje się w poblizu prawdziwych wag
#Punkt startowy lezy daleko od minimum, a po treningu przesuwa wagi dużo blizej optimum
#Koncowe wagi są bliskie prawdziwym wartosciom, więc model uczy się poprawnie
  

#Zadanie 10
#gradient jeszcze raz
w <- c(0, 0)
learning_rate <- 0.01

for (epoch in 1:100) 
{
  y_pred <- x_bias %*% w
  gradient <- (2 / n) * t(x_bias) %*% (y_pred - y)
  w <- w - learning_rate * as.vector(gradient)
}

#porownanie z metoda najmniejszych kwadratow
w_ls <- solve(t(x_bias) %*% x_bias) %*% t(x_bias) %*% y #rozwiazanie z wzoru
w_ls <- as.vector(w_ls)

mse_gradient <- mean((x_bias %*% w - y)^2) #blad
mse_ls <- mean((x_bias %*% w_ls - y)^2)

cat("Gradient descent:\n")
cat("bias =", w[1], "\n")
cat("waga =", w[2], "\n")
cat("MSE =", mse_gradient, "\n\n")

cat("Rozwiązanie metoda najmniejszych kwadratow:\n")
cat("bias =", w_ls[1], "\n")
cat("waga =", w_ls[2], "\n")
cat("MSE =", mse_ls, "\n")

#Rozwiązanie uzyskane metoda najmniejszych kwadratww daje mniejszy blad MSE niż gradient descent
#Gradient descent w tym przypadku nie zbiegl jeszcze do optimum
#Mimo to wyniki obu metod są zblizone
  