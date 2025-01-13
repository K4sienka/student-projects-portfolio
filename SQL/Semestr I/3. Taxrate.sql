CREATE OR REPLACE FUNCTION sales.taxrate() --funkcja do zmieniania 
RETURNS TRIGGER AS $$                   --zwraca wartosc typu trigger
DECLARE                     --zmienne
    old NUMERIC;
    new NUMERIC;
BEGIN
    -- Pobierz stare i nowe wartości pola 'taxrate'
    old= := COALESCE(OLD.taxrate, 0); --ustawia na old wartosci przed aktualizacją, jeśli jest NULL to zmienia na 0
    new= := COALESCE(NEW.taxrate, 0); --to samo po aktualizacji

    NUMERIC zmiana = ABS(new - old) / old; --do sprawdzenia o ile % zmieniono

    IF zmiana > 0.3 THEN            --wyrzuca blad jesli > 30%
        RAISE EXCEPTION 'Zmiana wartości w polu taxrate o więcej niż 30%% jest niedozwolona';
    END IF;

    RETURN NEW;     --zwraca co nowego
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER taxRate
BEFORE UPDATE ON sales.salestaxrate
FOR EACH ROW
EXECUTE FUNCTION sales.taxrate();
