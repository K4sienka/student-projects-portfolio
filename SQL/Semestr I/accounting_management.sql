--CREATE DATABASE firma;
CREATE SCHEMA IF NOT EXISTS ksiegowosc;

CREATE TABLE IF NOT EXISTS ksiegowosc.pracownicy
(
  id_pracownika INT PRIMARY KEY,
  imie VARCHAR(40) NOT NULL,
  nazwisko VARCHAR(40) NOT NULL,
  adres VARCHAR(50) NOT NULL,
  telefon INT
);

COMMENT ON TABLE ksiegowosc.pracownicy IS 'Tabela zawierająca informacje o pracownikach firmy.';

CREATE TABLE IF NOT EXISTS ksiegowosc.godziny
(
  id_godziny INT PRIMARY KEY,
  data DATE NOT NULL,
  liczba_godzin INT NOT NULL,
  id_pracownika INT NOT NULL
);

COMMENT ON TABLE ksiegowosc.godziny IS 'Tabela przechowująca dane o przepracowanych godzinach pracowników.';

CREATE TABLE IF NOT EXISTS ksiegowosc.pensje
(
  id_pensji INT PRIMARY KEY, 
  stanowisko VARCHAR(40) NOT NULL,
  kwota DECIMAL(10,2) NOT NULL
);

COMMENT ON TABLE ksiegowosc.pensje IS 'Tabela zawierająca informacje o pensjach pracowników w firmie.';

CREATE TABLE IF NOT EXISTS ksiegowosc.premie
(
  id_premii INT PRIMARY KEY,
  rodzaj VARCHAR(40) NOT NULL,
  kwota DECIMAL(10,2)
);

COMMENT ON TABLE ksiegowosc.premie IS 'Tabela przechowująca informacje o przyznawanych premiach.';

CREATE TABLE IF NOT EXISTS ksiegowosc.wynagrodzenie
(
  id_wynagrodzenia INT PRIMARY KEY,
  data DATE NOT NULL,
  id_pracownika INT NOT NULL,
  id_pensji INT NOT NULL,
  id_premii INT NOT NULL
);

COMMENT ON TABLE ksiegowosc.wynagrodzenie IS 'Tabela zawierająca informacje o wynagrodzeniach pracowników.';

ALTER TABLE IF EXISTS ksiegowosc.godziny 
ADD FOREIGN KEY (id_pracownika) 
REFERENCES ksiegowosc.pracownicy(id_pracownika);


ALTER TABLE IF EXISTS ksiegowosc.wynagrodzenie 
ADD FOREIGN KEY (id_pracownika)
REFERENCES ksiegowosc.pracownicy(id_pracownika);

ALTER TABLE IF EXISTS ksiegowosc.wynagrodzenie 
ADD FOREIGN KEY (id_pensji)
REFERENCES ksiegowosc.pensje(id_pensji);

ALTER TABLE IF EXISTS ksiegowosc.wynagrodzenie 
ADD FOREIGN KEY (id_premii)
REFERENCES ksiegowosc.premie(id_premii);

INSERT INTO ksiegowosc.pracownicy(id_pracownika, imie, nazwisko, adres, telefon)
VALUES
(1, 'Anna', 'Kowalska', 'ul. Kwiatowa 5, Warszawa', 123456789),
(2, 'Jan', 'Nowak', 'ul. Słoneczna 10, Kraków', 987654321),
(3, 'Marta', 'Wojcik', 'ul. Parkowa 15, Wrocław', 555555555),
(4, 'Piotr', 'Zawisza', 'ul. Główna 20, Gdańsk', 777777777),
(5, 'Alicja', 'Jankowska', 'ul. Polna 25, Łódź', 444444444),
(6, 'Tomasz', 'Kaczor', 'ul. Leśna 30, Poznań', 666666666),
(7, 'Ewa', 'Nowakowska', 'ul. Wiosenna 35, Katowice', 222222222),
(8, 'Grzegorz', 'Adamczyk', 'ul. Zimowa 40, Lublin', 999999999),
(9, 'Natalia', 'Szymańska', 'ul. Morza 45, Szczecin', 111111111),
(10, 'Krzysztof', 'Wojciechowski', 'ul. Różana 50, Bydgoszcz', 333333333);

INSERT INTO ksiegowosc.godziny (id_godziny, data, liczba_godzin, id_pracownika)
VALUES 
(1, '2020-11-24', 80, 1),
  (2, '2000-12-3', 60, 2),
  (3, '2003-8-29', 20, 3),
  (4, '2021-6-24', 10, 4),
  (5, '2023-10-4', 70, 5),
  (6, '2023-7-4', 60, 6),
  (7, '2014-10-12', 80, 7),
  (8, '2015-9-28', 80, 8),
  (9, '2023-4-1', 80, 9),
  (10, '2022-6-13', 12, 10),
  (11, '2023-1-5', 10, 1),
  (12, '2023-2-12', 80, 2),
  (13, '2023-3-20', 90, 3),
  (14, '2023-4-15', 70, 4),
  (15, '2023-5-25', 11, 5),
  (16, '2023-6-8', 60, 6),
  (17, '2023-7-2', 80, 7),
  (18, '2023-8-14', 70, 8),
  (19, '2023-9-19', 90, 9),
  (20, '2023-10-28', 10, 10),
  (21, '2023-11-11', 80, 1),
  (22, '2023-11-10', 70, 2),
  (23, '2023-11-9', 90, 3),
  (24, '2023-11-8', 11, 4),
  (25, '2023-11-7', 60, 5),
  (26, '2023-11-6', 70, 6),
  (27, '2023-11-5', 80, 7),
  (28, '2023-11-4', 90, 8),
  (29, '2023-11-3', 10, 9),
  (30, '2023-11-2', 12, 10),
  (31, '2023-11-1', 80, 1),
  (32, '2023-10-31', 70, 2),
  (33, '2023-10-30', 9, 3),
  (34, '2023-10-29', 11, 4),
  (35, '2023-10-28', 60, 5),
  (36, '2023-10-27', 70, 6),
  (37, '2023-10-26', 80, 7),
  (38, '2023-10-25', 9, 8),
  (39, '2023-10-24', 10, 9),
  (40, '2023-10-23', 12, 10),
  (41, '2023-10-22', 80, 1),
  (42, '2023-10-21', 70, 2),
  (43, '2023-10-20', 9, 3),
  (44, '2023-10-19', 11, 4),
  (45, '2023-10-18', 60, 5),
  (46, '2023-10-17', 70, 6),
  (47, '2023-10-16', 80, 7),
  (48, '2023-10-15', 9, 8),
  (49, '2023-10-14', 10, 9),
  (50, '2023-10-13', 12, 10),
  (51, '2023-10-12', 80, 1),
  (52, '2023-10-11', 70, 2),
  (53, '2023-10-10', 9, 3),
  (54, '2023-10-9', 11, 4),
  (55, '2023-10-8', 60, 5),
  (56, '2023-10-7', 70, 6),
  (57, '2023-10-6', 80, 7),
  (58, '2023-10-5', 9, 8),
  (59, '2023-10-4', 10, 9),
  (60, '2023-10-3', 12, 10);

INSERT INTO ksiegowosc.premie (id_premii, rodzaj, kwota)
VALUES 
(1, 'Premia roczna', 1000),
(2, 'Premia kwartalna', 500),
(3, 'Premia miesięczna', 300),
(4, 'Premia roczna', 300 ),
(5, 'Premia kwartalna', 500),
(6, 'Premia miesięczna', NULL),
(7, 'Premia roczna', 1000),
(8, 'Premia kwartalna', NULL),
(9, 'Premia miesięczna', 300),
(10, 'Premia roczna', NULL);

INSERT INTO ksiegowosc.pensje (id_pensji, stanowisko, kwota)
VALUES 
(1, 'Kierownik', 900),
(2, 'Specjalista', 6000),
(3, 'Pracownik fizyczny', 500),
(4, 'Asystent', 4500),
(5, 'Specjalista', 2200),
(6, 'Kierownik', 8500),
(7, 'Pracownik fizyczny', 900),
(8, 'Asystent', 4600),
(9, 'Specjalista', 2300),
(10, 'Kierownik', 8500);

INSERT INTO ksiegowosc.wynagrodzenie (id_wynagrodzenia, data, id_pracownika, id_pensji, id_premii)
VALUES
(1, '2020-11-01', 1, 1, 1),
(2, '2021-06-11', 2, 2, 2),
(3, '2023-10-03', 3, 3, 3),
(4, '2023-09-23', 4, 4, 4),
(5, '2002-01-4', 5, 5, 5),
(6, '2003-01-15', 6, 6, 6),
(7, '2023-03-26', 7, 7, 7),
(8, '2022-04-17', 8, 8, 8),
(9, '2022-01-18', 9, 9, 9),
(10, '2020-05-09', 10, 10, 10);

--A) Id_pracownika i jego nazwisko
SELECT id_pracownika, nazwisko 
FROM ksiegowosc.pracownicy;

--B) Zarobki większe niz 1000
SELECT ksiegowosc.pracownicy.id_pracownika, ksiegowosc.pensje.kwota
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.wynagrodzenie.id_pensji = ksiegowosc.pensje.id_pensji
WHERE ksiegowosc.pensje.kwota > 1000
ORDER BY ksiegowosc.pensje.kwota DESC;

--C) Pracownicy bez premii i płacy większej niz 2000
SELECT ksiegowosc.pracownicy.id_pracownika, COALESCE(ksiegowosc.premie.kwota,0) AS Kwota_premii, COALESCE(ksiegowosc.pensje.kwota,0) AS Kwota_pensji
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.wynagrodzenie.id_pensji = ksiegowosc.pensje.id_pensji
LEFT JOIN ksiegowosc.premie ON ksiegowosc.wynagrodzenie.id_premii = ksiegowosc.premie.id_premii
WHERE ksiegowosc.premie.kwota IS NULL AND ksiegowosc.pensje.kwota > 2000;


--D) Imie na J
SELECT imie, nazwisko
FROM ksiegowosc.pracownicy
WHERE imie LIKE 'J%';

--E) Nazwisko zawiera N, imie konczy sie na A
SELECT imie, nazwisko
FROM ksiegowosc.pracownicy
WHERE imie LIKE '%a' AND nazwisko LIKE '%n%';

--F) Nadgodziny (>160h)
SELECT pracownicy.imie, pracownicy.nazwisko, GREATEST(SUM(ksiegowosc.godziny.liczba_godzin) - 160, 0) AS Suma_godzin
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.godziny ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.godziny.id_pracownika
GROUP BY pracownicy.imie, pracownicy.nazwisko;

--G)Pensja miedzy 1500/3000
SELECT pracownicy.imie, pracownicy.nazwisko, pensje.kwota
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
WHERE pensje.kwota BETWEEN 1500 AND 3000;

--H) Nadgodziny i nie dostali premii
SELECT pracownicy.imie, pracownicy.nazwisko, GREATEST(SUM(ksiegowosc.godziny.liczba_godzin) - 160, 0) AS Suma_godzin, COALESCE(premie.kwota, 0) AS Brak_premii
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.godziny ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.godziny.id_pracownika
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.premie ON ksiegowosc.wynagrodzenie.id_premii = ksiegowosc.premie.id_premii
GROUP BY pracownicy.imie, pracownicy.nazwisko, premie.kwota
HAVING premie.kwota IS NULL AND GREATEST(SUM(ksiegowosc.godziny.liczba_godzin) - 160, 0) > 0;

--I) Sortowanie od najwiekszej pensji
SELECT pracownicy.imie, pracownicy.nazwisko, pensje.kwota
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
ORDER BY kwota DESC;

--J) Sortowanie premii i pensji malejaca
SELECT ksiegowosc.pracownicy.imie, ksiegowosc.pracownicy.nazwisko, SUM(ksiegowosc.pensje.kwota) AS Suma_pensji, SUM(COALESCE(premie.kwota, 0)) AS Suma_premii
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.premie ON ksiegowosc.premie.id_premii = ksiegowosc.wynagrodzenie.id_premii
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
GROUP BY ksiegowosc.pracownicy.imie, ksiegowosc.pracownicy.nazwisko, pensje.kwota, premie.kwota
ORDER BY pensje.kwota DESC, premie.kwota DESC;


--K) Liczenie i grupowanie przez stanowisko
SELECT COUNT(pensje.stanowisko) AS Zliczone_stanowiska, pensje.stanowisko AS Nazwa_stanowiska
FROM ksiegowosc.pensje
GROUP BY pensje.stanowisko;

--I) Płaca dla kierownika
SELECT  pensje.stanowisko,  ROUND(AVG(pensje.kwota), 2) AS Srednia_placa, MIN (pensje.kwota) AS Minimalna_placa, MAX (pensje.kwota) AS Maksymalna_placa
FROM ksiegowosc.pensje
WHERE pensje.stanowisko = 'Kierownik'
GROUP BY pensje.stanowisko;

--M) Suma wynagrodzen
SELECT pracownicy.imie, pracownicy.nazwisko, SUM(pensje.kwota + COALESCE(premie.kwota, 0)) AS Wynagrodzenie
FROM ksiegowosc.pracownicy
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pracownicy.id_pracownika = ksiegowosc.wynagrodzenie.id_pracownika
LEFT JOIN ksiegowosc.premie ON ksiegowosc.premie.id_premii = ksiegowosc.wynagrodzenie.id_premii
LEFT JOIN ksiegowosc.pensje ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
GROUP BY pracownicy.imie, pracownicy.nazwisko
ORDER BY Wynagrodzenie DESC;

--N) Suma wynagrodzen wedlug stanowiska
SELECT pensje.stanowisko, SUM(pensje.kwota +premie.kwota) AS Wynagrodzenie
FROM ksiegowosc.pensje
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
LEFT JOIN ksiegowosc.premie ON ksiegowosc.premie.id_premii = ksiegowosc.wynagrodzenie.id_premii
GROUP BY pensje.stanowisko
ORDER BY Wynagrodzenie DESC;

--O) Liczba premii wedlug stanowiska
SELECT pensje.stanowisko, COUNT(premie.id_premii) AS Liczba_premii
FROM ksiegowosc.pensje
INNER JOIN ksiegowosc.wynagrodzenie ON ksiegowosc.pensje.id_pensji = ksiegowosc.wynagrodzenie.id_pensji
LEFT JOIN ksiegowosc.premie ON ksiegowosc.wynagrodzenie.id_premii = ksiegowosc.premie.id_premii
GROUP BY pensje.stanowisko
ORDER BY Liczba_premii DESC;

--P) Usuniecie pracownikow <1200zl
DELETE FROM ksiegowosc.pracownicy
WHERE id_pracownika IN 
(
    SELECT wynagrodzenie.id_pracownika
    FROM ksiegowosc.wynagrodzenie
    JOIN ksiegowosc.pensje ON ksiegowosc.wynagrodzenie.id_pensji = ksiegowosc.pensje.id_pensji
    WHERE pensje.kwota < 1200
);






