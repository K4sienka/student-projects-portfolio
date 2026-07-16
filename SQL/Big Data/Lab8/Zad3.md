## Zadanie 3
### 5 metody, które mogą być użyte w Pipeline tak aby tyły odporne na błędy użytkownika, jak najbardziej „produkcyjnie”. 
- Walidacja schematu wejściowego: schema.json lub StructType -> wymuszenie poprawnego typu danych przy wczytywaniu.

      schema = StructType().add("review", StringType()).add("stars", IntegerType())
      df = spark.read.schema(schema).json("/FileStore/reviews.json")

  
- Filtrowanie błędnych danych: usunąć rekordy z null i sprawdzić czy np. mieści się w jakimś zakresie.

      df_clean = df.filter("review IS NOT NULL AND stars BETWEEN 1 AND 5")
  
- Plik konfiguracyjny: trzymać ścieżki i kolumny w config.yaml, by nie edytować kodu przy każdej zmianie.

      with open("config.yaml") as f:
        config = yaml.safe_load(f)
      input_path = config["input_path"]
      columns = config["columns"]

- Logowanie błędnych rekordów: zapisywanie odrzuconych rekordów do osobnego folderu.

      bad_records = df.filter("review IS NULL OR stars IS NULL")
      bad_records.write.mode("overwrite").json("/FileStore/logs/bad_records/")

- Sprawdzenie wyjścia końcowego: dodawanie warunku -> jeśli po transformacji nie ma danych to zatrzymanie pipeline i rzucenie błędu.

      if df_clean.count() == 0:
        raise Exception("Brak danych po transformacji – zatrzymuję pipeline.")
