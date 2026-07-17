%% Program 5 - metoda potegowa i SVD dla macierzy 3x3
% Skrypt przygotowany tak, aby mozna go bylo otworzyc jako Live Script.
% Uklad sekcji jest raportowy: najpierw opis kroku, potem kod i wynik.
%
% Zadanie sklada sie z czterech czesci:
% 1) implementacja metody potegowej dla macierzy 3x3,
% 2) wyznaczenie SVD na podstawie wartosci i wektorow wlasnych macierzy A*A',
% 3) porownanie zbieznosci metody potegowej dla roznych norm,
% 4) porownanie otrzymanego rozkladu z wynikiem funkcji svd z MATLAB-a.
%
% W tej wersji metoda potegowa jest stosowana do macierzy B = A*A'.
% To jest zgodne z dalsza czescia zadania: wlasnie z macierzy A*A'
% otrzymujemy macierze U oraz D potrzebne do SVD.

clear; clc; close all;
format short g;

%% Ustawienia eksperymentu
% epsilon_start odpowiada warunkowi z punktu 1b: jezeli wylosowany wektor
% startowy daje zbyt maly blad poczatkowy, to losujemy go ponownie.
%
% epsilon_iter to dokladnosc metody potegowej wymagana w punkcie 3.

p_list = [1 2 3 4 inf];
epsilon_start = 1e-8;
epsilon_iter = 1e-4;
max_iter = 1000;
show_builtin_svd = true;

%% Pseudokod metody potegowej uzytej w tym programie
% 1. Losuj wektor startowy z0 o wspolrzednych z przedzialu (0,1).
% 2. Oblicz w0 = B*z0.
% 3. Oblicz przyblizenie wartosci wlasnej jako wybrany wspolczynnik skali.
%    W implementacji bierzemy element o najwiekszym module, bo to jest
%    stabilniejsze numerycznie niz zwykle max(w).
% 4. Licz blad ||B*z - lambda*z||_p.
% 5. Jesli wektor startowy daje blad mniejszy od 1e-8, losujemy nowy.
% 6. Iterujemy: w = B*z, normalizacja, obliczenie bledu, sprawdzenie stopu.
% 7. Po znalezieniu dominujacej pary wlasnej stosujemy deflacje i
%    powtarzamy algorytm dla kolejnych dwoch wartosci i wektorow wlasnych.

%% Losowanie macierzy A 3x3
% W zadaniu jest zapisane, ze kazdy student powinien miec inna macierz.
% Dlatego tutaj ziarno generatora jest losowane przez rng('shuffle').
% Dla wygody wypisujemy seed, aby w razie potrzeby mozna bylo odtworzyc
% dokladnie te same wyniki z raportu.

rng('shuffle');
state = rng;

A = rand(3);
while rank(A) < 3 || min(abs(diff(sort(eig(A*A'), 'descend')))) < 1e-6
    A = rand(3);
end

fprintf('===============================================\n');
fprintf('PROGRAM 5 - METODA POTEGOWA I SVD\n');
fprintf('===============================================\n\n');
fprintf('Seed generatora liczb losowych: %d\n\n', state.Seed);

disp('Wylosowana macierz A:');
disp(A);

figure('Name','Macierz A');
imagesc(A); colorbar;
axis equal tight;
title('Wylosowana macierz A');

%% Macierz B = A*A'
% W dalszych obliczeniach metoda potegowa dziala dla macierzy B = A*A'.
% Macierz ta jest symetryczna i dodatnio okreslona (dla macierzy A pelnego
% rzedu), wiec dobrze nadaje sie do badania wartosci i wektorow wlasnych.

B = A * A.';

disp('Macierz B = A*A'':');
disp(B);

figure('Name','Macierz B = A*A''');
imagesc(B); colorbar;
axis equal tight;
title('Macierz B = A*A''');

%% Dokladne wartosci i wektory wlasne macierzy B z funkcji eig
% To jest punkt odniesienia do porownania metody potegowej.
% Wartosci wlasne sortujemy malejaco.

[U_exact_raw, Lambda_exact_raw] = eig(B);
lambda_exact = diag(Lambda_exact_raw);
[lambda_exact, idx] = sort(real(lambda_exact), 'descend');
U_exact = real(U_exact_raw(:, idx));
U_exact = fix_column_signs(U_exact);
D_exact = diag(sqrt(max(lambda_exact, 0)));

disp('Dokladne wartosci wlasne macierzy B = A*A'':');
disp(lambda_exact);

disp('Dokladna macierz U z eig(B):');
disp(U_exact);

disp('Macierz D = diag(sqrt(lambda_i)):');
disp(D_exact);

%% Wyznaczenie macierzy V ze wzoru V = A'' * U * inv(D)
% Poniewaz macierz A jest 3x3 i pelnego rzedu, D jest odwracalna.
% Wektory prawe V liczymy bezposrednio ze wzoru z wykladu.

D_inv = diag(1 ./ diag(D_exact));
V_from_eig = A.' * U_exact * D_inv;
V_from_eig = normalize_columns(V_from_eig);
V_from_eig = fix_column_signs(V_from_eig);

A_svd_manual = U_exact * D_exact * V_from_eig.';
manual_svd_residual = norm(A - A_svd_manual, 'fro');

disp('Macierz V otrzymana ze wzoru A''*U*inv(D):');
disp(V_from_eig);

fprintf('Blad rekonstrukcji A - U*D*V'' (norma Frobeniusa): %.3e\n\n', manual_svd_residual);

%% Metoda potegowa dla 3 wartosci i 3 wektorow wlasnych
% Dla kazdej normy z listy p = 1,2,3,4,inf wykonujemy trzy przebiegi:
% - pierwszy dla najwiekszej wartosci wlasnej,
% - drugi po jednej deflacji,
% - trzeci po dwoch deflacjach.
%
% W kazdym przebiegu zapisujemy historie bledu, aby potem narysowac wykres.

results = struct();

for ip = 1:numel(p_list)
    p = p_list(ip);
    [lambda_pm, U_pm, histories] = power_method_with_deflation(B, p, epsilon_start, epsilon_iter, max_iter);

    U_pm = fix_signs_against_reference(U_pm, U_exact);

    results(ip).p = p;
    results(ip).lambda = lambda_pm;
    results(ip).U = U_pm;
    results(ip).histories = histories;

    fprintf('--- Norma p = %s ---\n', p_to_text(p));
    disp('Wartosci wlasne z metody potegowej:');
    disp(lambda_pm(:).');
    disp('Wektory wlasne z metody potegowej (kolumny):');
    disp(U_pm);
    fprintf('\n');
end

%% Wykresy zbieznosci - 15 wykresow
% Zgodnie z poleceniem generujemy 5*3 = 15 wykresow.
% Os pozioma: iteracje.
% Os pionowa: blad ||B*z - lambda*z||_p.

for ip = 1:numel(p_list)
    p = results(ip).p;
    for k = 1:3
        h = results(ip).histories{k};
        figure('Name', sprintf('Zbieznosc - p=%s - wektor %d', p_to_text(p), k));
        semilogy(1:numel(h), h, 'LineWidth', 1.5);
        grid on;
        xlabel('Iteracja');
        ylabel('Blad');
        title(sprintf('Metoda potegowa dla p=%s, para wlasna nr %d', p_to_text(p), k));
    end
end

%% Zestawienie z dokladnymi wartosciami z eig
% W tej sekcji pokazujemy roznice pomiedzy wynikami metody potegowej i
% wynikiem funkcji eig dla kazdej normy. Znak wektora wlasnego nie ma
% znaczenia, dlatego porownanie wektorow prowadzimy po uzgodnieniu znakow.

for ip = 1:numel(p_list)
    p = results(ip).p;
    lambda_pm = results(ip).lambda;
    U_pm = results(ip).U;

    lambda_err = abs(lambda_pm(:) - lambda_exact(:));
    vec_err = zeros(3,1);
    for k = 1:3
        vec_err(k) = norm(U_pm(:,k) - U_exact(:,k), 2);
    end

    T = table((1:3).', lambda_exact(:), lambda_pm(:), lambda_err, vec_err, ...
        'VariableNames', {'nr','lambda_dokladna','lambda_metoda_potegowa','blad_lambda','blad_wektora'});

    fprintf('Porownanie z eig dla p = %s\n', p_to_text(p));
    disp(T);
end

%% SVD z biblioteki numerycznej MATLAB-a
% Teraz liczymy SVD za pomoca funkcji wbudowanej i porownujemy otrzymana
% rekonstrukcje z nasza rekonstrukcja z punktu 2.

if show_builtin_svd
    [U_builtin, D_builtin, V_builtin] = svd(A);
    A_svd_builtin = U_builtin * D_builtin * V_builtin.';

    disp('Macierz U z funkcji svd:');
    disp(U_builtin);
    disp('Macierz D z funkcji svd:');
    disp(D_builtin);
    disp('Macierz V z funkcji svd:');
    disp(V_builtin);
else
    U_builtin = [];
    D_builtin = [];
    V_builtin = [];
    A_svd_builtin = A;
end

%% Porownanie dokladnosci ||UDV - SVD(A)||_p dla p=1,2,3,4,inf
% Dla p = 1, 2 i inf korzystamy z klasycznych norm macierzowych.
% Dla p = 3 i 4 stosujemy numeryczne przyblizenie indukowanej normy p.

Delta = A_svd_manual - A_svd_builtin;
svd_errors = zeros(numel(p_list), 1);
p_labels = cell(numel(p_list), 1);

for ip = 1:numel(p_list)
    svd_errors(ip) = matrix_norm_general(Delta, p_list(ip));
    p_labels{ip} = p_to_text(p_list(ip));
end

T_svd = table(p_labels, svd_errors, ...
    'VariableNames', {'p','norma_UDV_minus_SVDA'});

disp('Porownanie ||UDV - SVD(A)||_p:');
disp(T_svd);

%% Krotkie podsumowanie
% W tej sekcji mamy najwazniejsze wyniki potrzebne do raportu:
% - wylosowana macierz A,
% - macierze U, D, V otrzymane z A*A',
% - 15 wykresow zbieznosci,
% - 5 bledow porownujacych nasz rozklad z funkcja svd.

fprintf('===============================================\n');
fprintf('PODSUMOWANIE\n');
fprintf('===============================================\n');
fprintf('Blad rekonstrukcji A - U*D*V'' (Frobenius): %.3e\n', manual_svd_residual);
if show_builtin_svd
    fprintf('Najwiekszy z 5 bledow ||UDV - SVD(A)||_p: %.3e\n', max(svd_errors));
end
fprintf('\nMacierze do raportu:\n');
fprintf('- A\n- U\n- D\n- V\n- 15 wykresow zbieznosci\n- tabela 5 bledow porownawczych\n');

%% Funkcje pomocnicze
function [lambda_all, U_all, histories] = power_method_with_deflation(B, pnorm, epsilon_start, epsilon_iter, max_iter)
    n = size(B,1);
    B_work = B;
    lambda_all = zeros(n,1);
    U_all = zeros(n,n);
    histories = cell(n,1);

    for k = 1:n
        [lambda_k, u_k, hist_k] = power_method_single(B_work, pnorm, epsilon_start, epsilon_iter, max_iter);
        u_k = u_k / norm(u_k, 2);

        lambda_all(k) = real(lambda_k);
        U_all(:,k) = real(u_k);
        histories{k} = hist_k;

        B_work = B_work - lambda_k * (u_k * u_k.');
        B_work = (B_work + B_work.') / 2;
    end
end

function [lambda, z, history] = power_method_single(B, pnorm, epsilon_start, epsilon_iter, max_iter)
    z = random_start_vector(B, pnorm, epsilon_start);
    history = zeros(max_iter,1);

    for k = 1:max_iter
        w = B * z;
        [~, idx] = max(abs(w));
        mu = w(idx);

        if abs(mu) < eps
            history = history(1:max(k-1,1));
            break;
        end

        err = vector_norm_general(w - mu * z, pnorm);
        history(k) = err;

        z = w / mu;

        if err < epsilon_iter
            history = history(1:k);
            break;
        end

        if k == max_iter
            history = history(1:k);
        end
    end

    z = real(z);
    z = z / norm(z, 2);
    lambda = real((z.' * B * z) / (z.' * z));
end

function z = random_start_vector(B, pnorm, epsilon_start)
    while true
        z = rand(3,1);
        w = B * z;
        [~, idx] = max(abs(w));
        mu = w(idx);
        err0 = vector_norm_general(w - mu * z, pnorm);

        if err0 >= epsilon_start
            return;
        end
    end
end

function val = vector_norm_general(x, p)
    if isinf(p)
        val = max(abs(x));
    else
        val = norm(x, p);
    end
end

function val = matrix_norm_general(M, p)
    if p == 1
        val = norm(M, 1);
    elseif p == 2
        val = norm(M, 2);
    elseif isinf(p)
        val = norm(M, inf);
    else
        val = induced_p_norm_numeric(M, p);
    end
end

function val = induced_p_norm_numeric(M, p)
    n = size(M,2);
    val = 0;

    for s = 1:200
        x = randn(n,1);
        x = x / norm(x, p);

        for it = 1:50
            y = M * x;
            y_norm = norm(y, p);
            if y_norm == 0
                break;
            end

            g = M.' * (abs(y).^(p-2) .* y);
            if norm(g) == 0
                break;
            end

            x = sign(g) .* abs(g).^(1/(p-1));
            x = x / norm(x, p);
            val = max(val, norm(M * x, p));
        end
    end
end

function X = normalize_columns(X)
    for j = 1:size(X,2)
        nrm = norm(X(:,j), 2);
        if nrm > 0
            X(:,j) = X(:,j) / nrm;
        end
    end
end

function X = fix_column_signs(X)
    for j = 1:size(X,2)
        [~, idx] = max(abs(X(:,j)));
        if X(idx,j) < 0
            X(:,j) = -X(:,j);
        end
    end
end

function X = fix_signs_against_reference(X, Xref)
    for j = 1:size(X,2)
        if X(:,j).' * Xref(:,j) < 0
            X(:,j) = -X(:,j);
        end
    end
end

function txt = p_to_text(p)
    if isinf(p)
        txt = 'inf';
    else
        txt = num2str(p);
    end
end
