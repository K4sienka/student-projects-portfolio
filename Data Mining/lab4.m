close all; clear all; clc;

%wczytanie danych
dane = readtable("archiwum_tab_a_2025.xls", "VariableNamingRule","preserve");
disp(dane.Properties.VariableNames);

%wybór kolumn: data, EUR, CHF
nazwy = string(dane.Properties.VariableNames);

kolData = find(contains(lower(nazwy), "data"), 1);
kolEUR  = find(contains(nazwy, "EUR"), 1);
kolCHF  = find(contains(nazwy, "CHF"), 1);

daty  = dane{:, kolData};
kursA = dane{:, kolEUR};   % EUR
kursB = dane{:, kolCHF};   % CHF

%konwersja dat
if ~isdatetime(daty)
    daty = datetime(string(daty), ...
        "InputFormat", "dd-MMM-yyyy", ...
        "Locale", "en_US");
end

%--------------------------------
%ograniczenie do 2025 H1
idx = daty >= datetime(2025,1,1) & daty <= datetime(2025,6,30);
idx = idx & ~isnat(daty);

daty  = daty(idx);
kursA = kursA(idx);
kursB = kursB(idx);

%sztuczne rozdzielenie na dwa szeregi

%EUR
datyA = daty;
kursA = kursA;

%CHF
datyB = daty;
kursB = kursB;

%usuniecie losowych dat, żeby pokazać, że daty moga sie nie zgadzac
usunA = [8 16];          %do usuniecia z EUR
usunB = [5 12 20 35];    %do usuniecia z CHF

datyA(usunA) = [];
kursA(usunA) = [];

datyB(usunB) = [];
kursB(usunB) = [];

%sprawdzenie zgodnosci dat

tylkoA = setdiff(datyA, datyB);   %tylko w EUR
tylkoB = setdiff(datyB, datyA);   %tylko w CHF

disp("Liczba dat tylko w EUR:")
disp(length(tylkoA))

disp("Daty tylko w EUR:")
disp(tylkoA)

disp("Liczba dat tylko w CHF:")
disp(length(tylkoB))

disp("Daty tylko w CHF:")
disp(tylkoB)

%--------------------------------
%intersekcja dat
[wspolne, idxA, idxB] = intersect(datyA, datyB);

A_int = kursA(idxA);   % EUR po intersekcji
B_int = kursB(idxB);   % CHF po intersekcji

dane_int = table(wspolne, A_int, B_int, ...
    'VariableNames', {'Data','EUR','CHF'});

disp("Dane po intersekcji:")
disp(dane_int(1:5,:))

%interpolacja liniowa

unia = union(datyA, datyB);

A_interp = interp1(datenum(datyA), kursA, datenum(unia), 'linear', 'extrap');
B_interp = interp1(datenum(datyB), kursB, datenum(unia), 'linear', 'extrap');

dane_interp = table(unia, A_interp, B_interp, 'VariableNames', {'Data','EUR','CHF'});

disp("Dane po interpolacji:")
disp(dane_interp(1:5,:))

%wyniki intersekcja

%EUR
EUR_int = A_int;

EUR_abs = diff(EUR_int);
EUR_wzg = diff(EUR_int) ./ EUR_int(1:end-1);
EUR_log = diff(log(EUR_int));

%CHF
CHF_int = B_int;

CHF_abs = diff(CHF_int);
CHF_wzg = diff(CHF_int) ./ CHF_int(1:end-1);
CHF_log = diff(log(CHF_int));

wynik_int = table( ["EUR"; "CHF"], ...
    [std(EUR_abs); std(CHF_abs)], ...
    [std(EUR_wzg); std(CHF_wzg)], ...
    [std(EUR_log); std(CHF_log)], ...
    'VariableNames', {'Waluta','Std_abs','Std_wzg','Std_log'});

disp("Wyniki intersekcja")
disp(wynik_int)

%wyniki interpolacja

%EUR
EUR_i = A_interp;

EUR_abs_i = diff(EUR_i);
EUR_wzg_i = diff(EUR_i) ./ EUR_i(1:end-1);
EUR_log_i = diff(log(EUR_i));

%CHF
CHF_i = B_interp;

CHF_abs_i = diff(CHF_i);
CHF_wzg_i = diff(CHF_i) ./ CHF_i(1:end-1);
CHF_log_i = diff(log(CHF_i));

wynik_interp = table(["EUR"; "CHF"], ...
    [std(EUR_abs_i); std(CHF_abs_i)], ...
    [std(EUR_wzg_i); std(CHF_wzg_i)], ...
    [std(EUR_log_i); std(CHF_log_i)], ...
    'VariableNames', {'Waluta','Std_abs','Std_wzg','Std_log'});

disp("Wyniki interpolacja")
disp(wynik_interp)

%Zadanie 1 - komentarz
% Analizowany excel pochodziły z jednego pliku NBP i posiadał te same daty dla obydwu walut. 
% Dla sprawdzenia usunięto kilka obserwacji, żeby pokazać działanie porównania dat.
% 
% Po intersekcji zostały tylko wspólne daty dla obu walut. 
% Po interpolacji uzupełniono brakujące wartości liniowo.
% 
% Na podstawie std przyrostów widać, że CHF miał większą zmienność niż EUR. 
% Dla intersekcji odchylenie standardowe przyrostów logarytmicznych wyniosło około 0.00347 dla EUR i 0.00559 dla CHF. 
% Dla interpolacji wyniki są bardzo podobne: około 0.00341 dla EUR i 0.00546 dla CHF.
% 
% Na podstawie wyników mozna więc wnioskować, że w badanym okresie CHF był bardziej zmienny niż EUR. 
% Do porównania lepiej używać przyrostów względnych albo logarytmicznych, bo nie zależą tak mocno od poziomu kursu waluty.

%%
%Zadanie 2

%szereg EUR po intersekcji
data = dane_int.Data;
Y = dane_int.EUR;

n = length(Y);
osx = (1:n)';

%tren liniowy dla zakresu

par1 = polyfit(osx, Y, 1);
trend_globalny = polyval(par1, osx);

RMSE_globalny = sqrt(mean((Y - trend_globalny).^2));

disp("Trend liniowy dla calego zakresu:")
disp("Nachylenie:")
disp(par1(1))
disp("RMSE:")
disp(RMSE_globalny)

%-------------------------------------------------
%podzial na dwie połowy i trend liniowy osobno

polowa = floor(n/2);

%polowa nr1
osx1 = osx(1:polowa);
Y1 = Y(1:polowa);

par_p1 = polyfit(osx1, Y1, 1);
trend_p1 = polyval(par_p1, osx1);

RMSE_p1 = sqrt(mean((Y1 - trend_p1).^2));

%nr2
osx2 = osx(polowa+1:end);
Y2 = Y(polowa+1:end);

par_p2 = polyfit(osx2, Y2, 1);
trend_p2 = polyval(par_p2, osx2);

RMSE_p2 = sqrt(mean((Y2 - trend_p2).^2));

%wyniki
wyniki_trend = table( ...
    ["dla calego zakresu"; "1 polowa"; "2 polowa"], ...
    [par1(1); par_p1(1); par_p2(1)], ...
    [RMSE_globalny; RMSE_p1; RMSE_p2], ...
    'VariableNames', {'Trend','Nachylenie','RMSE'});

disp("Wyniki trendów liniowych:")
disp(wyniki_trend)

%------------------------
%wielomian stopnia 4
par4 = polyfit(osx, Y, 4);      
Yhat = polyval(par4, osx);

reszty = Y - Yhat;

RMSE_wielomian = sqrt(mean(reszty.^2));

disp("RMSE dla wielomianu stopnia 4:")
disp(RMSE_wielomian)

% wykres reszt
figure;
plot(data, reszty)
title("Reszty: EUR - wielomian stopnia 4")
xlabel("Data")
ylabel("Reszty")

% histogram reszt
figure;
histogram(reszty, 30)
title("Histogram reszt dla wielomianu stopnia 4")
xlabel("Reszty")
ylabel("Liczba wystąpień")

%----------------------------------------
%wykresy

%trendy polowek na jeden wykres
trend_1polowa = nan(n,1);
trend_2polowa = nan(n,1);

trend_1polowa(1:polowa) = trend_p1;
trend_2polowa(polowa+1:end) = trend_p2;

figure;
plot(data, Y)
hold on
plot(data, trend_globalny)
plot(data, trend_1polowa)
plot(data, trend_2polowa)
hold off

legend("EUR", "trend calego zakresu", "trend 1 połowy", "trend 2 połowy")
title("EUR - trend calego zakresu i trendy dla dwóch połówek")
xlabel("Data")
ylabel("Kurs EUR")
grid on

%Komentarz do zadania 2
% Nachylenia dwóch połówek różnią się. Dla 1 połowy nachylenie wynosi -0.00149, a dla 2 połowy -0.00044. Oba trendy są spadkowe, ale pierwszy spadek jest mocniejszy.
% 
% Trend globalny ma nachylenie dodatnie 0.00063, więc pokazuje wzrost w całym okresie. Oznacza to, że jest trochę sztucznym uśrednieniem, bo w danych widać duży skok kursu około początku kwietnia.
% 
% RMSE trendu globalnego wynosi 0.0396. Po podziale na połowy RMSE jest mniejsze: 0.0273 dla 1 połowy i 0.0162 dla 2 połowy. Zatem osobne trendy lepiej opisują dane niż jeden trend globalny.
% 
% Wielomian stopnia 4 ma RMSE = 0.0245, czyli lepiej dopasowuje się niż trend liniowy. Reszty są skupione wokół zera, ale nie wyglądają całkiem jak losowy szum. 
% Na wykresie reszt widać większe odchylenia szczególnie około kwietnia.
% 
% Wielomian stopnia 4 jest lepszy niż liniowy i dDobrze pokazuje ogólny kształt zmian kursu EUR, ale w danych nadal widać powtarzające się wahania.


%% 
%ZADANIE 3

%EUR po intersekcji
data = dane_int.Data;
Y = dane_int.EUR;

n = length(Y);

%trzy okna
k1 = 14;
k2 = 21;
k3 = 63;

ks = [k1 k2 k3];

%miejsce na szeregi
Y_sr = nan(n, length(ks));

%srednia ruchoma wsteczna
for j = 1:length(ks)

    k = ks(j);

    for t = k:n
        Y_sr(t,j) = mean(Y(t-k+1:t));
    end
end

%----------------------------------------------
%wykresy
figure;

subplot(4,1,1)
plot(data, Y)
title("Oryginał EUR")
xlabel("Data")
ylabel("Kurs EUR")
grid on

subplot(4,1,2)
plot(data, Y_sr(:,1))
title("Średnia ruchoma k = 14")
xlabel("Data")
ylabel("Kurs EUR")
grid on

subplot(4,1,3)
plot(data, Y_sr(:,2))
title("Średnia ruchoma k = 21")
xlabel("Data")
ylabel("Kurs EUR")
grid on

subplot(4,1,4)
plot(data, Y_sr(:,3))
title("Średnia ruchoma k = 63")
xlabel("Data")
ylabel("Kurs EUR")
grid on

%------------------------------------------
%reszty wygładzania
reszty14 = Y - Y_sr(:,1);
reszty21 = Y - Y_sr(:,2);
reszty63 = Y - Y_sr(:,3);

srednia_abs_14 = mean(abs(reszty14), "omitnan");
srednia_abs_21 = mean(abs(reszty21), "omitnan");
srednia_abs_63 = mean(abs(reszty63), "omitnan");

std_14 = std(reszty14, "omitnan");
std_21 = std(reszty21, "omitnan");
std_63 = std(reszty63, "omitnan");













