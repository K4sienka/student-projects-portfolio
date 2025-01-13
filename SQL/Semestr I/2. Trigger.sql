CREATE OR REPLACE FUNCTION cap_lastname()
RETURNS TRIGGER AS $$		--zwroci wartosc triggera
BEGIN
    NEW.lastname := UPPER(NEW.lastname); --NEW to specjalny alias, który odnosi się do nowego rekordu
    RETURN NEW.lastname;							--UPPER zwiększa nazwe
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER t_cap_lastname --tworzenie triggera
BEFORE INSERT OR UPDATE ON person.person --kazdy wiersz updatuje lub dodaje wartosc do person
FOR EACH ROW
EXECUTE FUNCTION cap_lastname(); --wywoluje funkcje w ramach trigger