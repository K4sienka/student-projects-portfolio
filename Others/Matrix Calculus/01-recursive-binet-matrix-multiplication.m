close all; clc; clear;

%losowe macierze 8x8, zakres liczb 0-10
A = 10*rand(8, 8);
B = 10*rand(8, 8);

l = 1; %warunek uzycia algorytmu tradycyjnego
[C, ops] = mnozenie_bineta(A, B, l);

disp('Macierz A:');
disp(A);

disp('Macierz B:');
disp(B);

disp('Wynik operacje_C C=A*B:');
disp(C);

disp('Liczba operacji:');
disp(ops);

disp('Sprawdzenie czy zgodne z wynikiem Matlaba (1 - tak, 0 - nie)');
disp(norm(C - A * B, 'fro') < 1e-10);

%czas ops liczba operacji
wartosci_k = 2:10;
wartosci_l = [3 4 5];

czasy = zeros(length(wartosci_l), length(wartosci_k));
operacje = zeros(length(wartosci_l), length(wartosci_k));

%przejscie po wszystkich wartosciach k
for indeks_k = 1:length(wartosci_k)
   
    k = wartosci_k(indeks_k); %aktualne k z listy
    n = 2^k; %rozmiar macierzy
    
    %nowe macierze dla kazdego n
    A = 10*rand(n, n);
    B = 10*rand(n, n);
    
    %sprawdzenie wartosci l
    for indeks_l = 1:length(wartosci_l)
        
        l = wartosci_l(indeks_l);
        
        %dla l >= k nie liczymy
        if l >= k
            czasy(indeks_l, indeks_k) = NaN;
            operacje(indeks_l, indeks_k) = NaN;
            continue;
        end
        
        %mierzenie czasu
        start = tic;
        [C, ops] = mnozenie_bineta(A, B, l);
        czas = toc(start);
        
        czasy(indeks_l, indeks_k) = czas; %policzony czas
        operacje(indeks_l, indeks_k) = ops; %policzone operacje
    end
end


%wykres czasu -> dla kazdego l wszystkie wartosci k
figure;
hold on;
for indeks_l = 1:length(wartosci_l)
    plot(wartosci_k, czasy(indeks_l, :), '-o', 'LineWidth', 1.5, 'DisplayName', ['l = ', num2str(wartosci_l(indeks_l))]);
end
grid on;
xlabel('Rozmiar macierzy: 2^k x 2^k');
ylabel('Czas mnozenia [s]');
title('Czas mnozenia metoda tradycyjnej + rekurencyjna Bineta');
legend('Location', 'northwest');


%wykres liczby operacji -> dla kazdego l wszystkie wartosci k
figure;
hold on;
for indeks_l = 1:length(wartosci_l)
    plot(wartosci_k, operacje(indeks_l, :), '-o', 'LineWidth', 1.5, 'DisplayName', ['l = ', num2str(wartosci_l(indeks_l))]);
end
grid on;
xlabel('k (rozmiar macierzy: 2^k x 2^k)');
ylabel('Liczba operacji zmiennoprzecinkowych');
title('Liczba operacji dla metody tradycyjnej + rekurencyjnej Bineta');
legend('Location', 'northwest');

%mnozenie rekurencyjne bineta (z warunkiem operacje_C tradycyjnego)
function [wynik, ops] = mnozenie_bineta(A, B, l)

    n = size(A, 1);

    %warunek macierzy kwadratowych oraz czy macierze sa tego samego wymiaru
    if size(A, 1) ~= size(A, 2) || size(B, 1) ~= size(B, 2) || any(size(A) ~= size(B)) || mod(log2(n), 1) ~= 0
        error('Macierze musza byc kwadratowe, tego samego rozmiaru ops ich rozmiar musi byc potega liczby 2.');
    end

    %macierz mniejsza niz lxl
    if n <= 2^l
        [wynik, ops] = mnozenie_tradycyjne(A, B);
        return;
    end

    %macierz na 4 bloki
    blok = n / 2;
    
    %macierz(wiersz, kolumna)
    A11 = A(1:blok, 1:blok);
    A12 = A(1:blok, blok+1:n);
    A21 = A(blok+1:n, 1:blok);
    A22 = A(blok+1:n, blok+1:n);

    B11 = B(1:blok, 1:blok);
    B12 = B(1:blok, blok+1:n);
    B21 = B(blok+1:n, 1:blok);
    B22 = B(blok+1:n, blok+1:n);

    %metoda Bineta, rekurencja -> podzial na mniejsze bloki -> az macierz <= 2x2 -> A11*B11 + A12*B21
    %zawsze 8 wynikow, bo 4 operacje_C 2 macierzy
    [M1, i_1] = mnozenie_bineta(A11, B11, l);
    [M2, i_2] = mnozenie_bineta(A12, B21, l);
    C11 = M1 + M2;

    [M3, i_3] = mnozenie_bineta(A11, B12, l);
    [M4, i_4] = mnozenie_bineta(A12, B22, l);
    C12 = M3 + M4;

    [M5, i_5] = mnozenie_bineta(A21, B11, l);
    [M6, i_6] = mnozenie_bineta(A22, B21, l);
    C21 = M5 + M6;

    [M7, i_7] = mnozenie_bineta(A21, B12, l);
    [M8, i_8] = mnozenie_bineta(A22, B22, l);
    C22 = M7 + M8;

    wynik = [C11 C12; C21 C22];

    %ilosc operacji wyliczenia C.. -> 4 bloki gdzie kazdy blok ma blok^2
    %elem
    operacje_C = 4 * (blok^2);
    
    %liczba operacji -> ops to ilosc operacji mnozenia elem A*B
    ops = i_1 + i_2 + i_3 + i_4 + i_5 + i_6 + i_7 + i_8 + operacje_C;
end

%mnozenie tradycyjne
function [wynik, ops] = mnozenie_tradycyjne(A, B)

    n = size(A, 1);
    wynik = zeros(n, n);
    ops = 0;

    for wiersz = 1:n
        for kolumna = 1:n
            elem = A(wiersz, 1) * B(1, kolumna); %pierwsze mnozenie
            ops = ops+1; %na poczatku nie ma dodawania

            for indeks = 2:n %przesuwamy sie po danym wierszu ops kolumnie
                elem = elem + A(wiersz, indeks) * B(indeks, kolumna); %elem z danego wiersza*elem z danej kolumny
                ops = ops + 2; %1 mnozenie + 1 dodawanie
            end
            wynik(wiersz, kolumna) = elem; %wynik w danej komorce
        end
    end
end