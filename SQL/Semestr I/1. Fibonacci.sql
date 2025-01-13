-- -- Database: AdventureWorks_

-- -- DROP DATABASE IF EXISTS "AdventureWorks_";

-- CREATE DATABASE "AdventureWorks_"
--     WITH
--     OWNER = postgres
--     ENCODING = 'UTF8'
--     LC_COLLATE = 'English_United Kingdom.1252'
--     LC_CTYPE = 'English_United Kingdom.1252'
--     TABLESPACE = pg_default
--     CONNECTION LIMIT = -1
--     IS_TEMPLATE = False;
	
	CREATE OR REPLACE FUNCTION fibonacci(n INT) --tworzy funkcje
RETURNS TABLE (ciag_fib INT) --zwraca kolumne o nazwie ciag_fib, $$ jak {}
AS $$ 
DECLARE		--deklaracje
    a INT := 1;
    b INT := 1;
    x INT := 0;

BEGIN	--begin/end to kod ktory zostal wykonany w ramach funkcji/procedury
    FOR i IN 1..n LOOP
        ciag_fib := a;
        x := a;
        a := b;
        b := x + b;
        RETURN NEXT; --zwroci zmienna ciag_fib
    END LOOP;
END;
$$ LANGUAGE plpgsql; --okresla jezyk proceduralny w jakim kod funkcji/procedury jest napisany


	CREATE OR REPLACE PROCEDURE print(n INT) --tworzenie procedury
AS $$
DECLARE
    rekord RECORD; --RECORD to zmienna ktora przechowuje rekordy
BEGIN
    FOR rekord IN SELECT * FROM fibonacci(n) --rekord=wyniki funkcji
    LOOP
        RAISE NOTICE 'Wartosci ciagu to: %', rekord.ciag_fib; --komunikat w konsoli, % konkretna wartosc
    END LOOP;
END;
$$ LANGUAGE plpgsql;

CALL print(10); --wywolanie funkcji
















