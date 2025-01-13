--CREATE DATABASE firma;
CREATE SCHEMA IF NOT EXISTS rozliczenia;

CREATE TABLE IF NOT EXISTS rozliczenia.pracownicy
(
  id_pracownika INT PRIMARY KEY,
  imie VARCHAR(40) NOT NULL,
  nazwisko VARCHAR(40) NOT NULL,
  adres VARCHAR(50) NOT NULL,
  telefon INT
);

CREATE TABLE IF NOT EXISTS rozliczenia.godziny
(
  id_godziny INT PRIMARY KEY,
  data DATE NOT NULL,
  liczba_godzin INT NOT NULL,
  id_pracownika INT NOT NULL
);

CREATE TABLE IF NOT EXISTS rozliczenia.pensje
(
  id_pensji INT PRIMARY KEY, 
  stanowisko VARCHAR(40) NOT NULL,
  kwota DECIMAL(10,2),
  id_premii INT
);

CREATE TABLE IF NOT EXISTS rozliczenia.premie
(
  id_premii INT PRIMARY KEY,
  rodzaj VARCHAR(40) NOT NULL,
  kwota DECIMAL(10,2)
);

ALTER TABLE IF EXISTS rozliczenia.godziny 
ADD FOREIGN KEY (id_pracownika) 
REFERENCES rozliczenia.pracownicy(id_pracownika);

ALTER TABLE IF EXISTS rozliczenia.pensje
ADD FOREIGN KEY (id_premii)
REFERENCES rozliczenia.premie(id_premii);

INSERT INTO rozliczenia.pracownicy(id_pracownika, imie, nazwisko, adres, telefon)
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

INSERT INTO rozliczenia.godziny (id_godziny, data, liczba_godzin, id_pracownika)
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
  (10, '2022-6-13', 12, 10);

INSERT INTO rozliczenia.premie (id_premii, rodzaj, kwota)
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

INSERT INTO rozliczenia.pensje (id_pensji, stanowisko, kwota, id_premii)
VALUES 
(1, 'Kierownik', 900, 1),
(2, 'Specjalista', 6000, 2),
(3, 'Pracownik fizyczny', 500, 3),
(4, 'Asystent', 4500, 4),
(5, 'Specjalista', 2200, 5),
(6, 'Kierownik', 8500, 6),
(7, 'Pracownik fizyczny', 900, 7),
(8, 'Asystent', 4600, 8),
(9, 'Specjalista', 2300, 9),
(10, 'Kierownik', 8500, 10);

--5 nazwiska i adresy
SELECT nazwisko, adres
	FROM rozliczenia.pracownicy;
	
--6 jaki dzien tygodnia i miesiac
SELECT 
  DATE_PART('dow', data) AS dzien_tygodnia, 
  DATE_PART('month', data) AS miesiac
	FROM rozliczenia.godziny;
	
--7 Kwota netto
/*ALTER TABLE rozliczenia.pensje
RENAME COLUMN kwota to kwota_brutto;

ALTER TABLE rozliczenia.pensje
ADD COLUMN kwota_netto MONEY;

UPDATE rozliczenia.pensje
SET kwota_netto = kwota_brutto - (kwota_brutto * 0.23);*/

SELECT *
FROM rozliczenia.pensje;






	