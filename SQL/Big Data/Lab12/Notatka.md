## Notatka – Spark UI
### Spark UI to interfejs, który pozwala podejrzeć, jak działa Spark „od środka” – czyli jak wykonywane są zadania, ile to trwało i co się działo z danymi.

1. Jobs
- Pokazuje wszystkie wykonane zadania.
- Każde zadanie (job) odpowiada jednej akcji (np. .count()).
- Widać, ile było etapów (stages), ile trwało, czy zakończyło się sukcesem.
2. Stages
- Każde zadanie dzieli się na etapy (stages).
- Widać, ile zadań (tasks) było w każdej partycji.
- Można podejrzeć szczegóły: czas, ilość danych, shuffle, input/output.
- Tutaj można podejrzeć dystrybucję danych – np. jak dane są rozłożone między partycje i w których było ich najwięcej.
3. Storage
- Pokazuje, jakie dane są zcache’owane w pamięci (np. .cache()).
- Widać rozmiar, liczbę partycji i ile jest w RAM vs na dysku.
4. Executors
- Pokazuje wszystkie wątki (executors), które przetwarzają dane.
- Widać zużycie pamięci, ilość tasków, ilość danych przetworzonych.
- Można zobaczyć, które executory wykonały najwięcej pracy.
5. SQL / DataFrame
- Widać historię zapytań SQL i operacji na DataFrame.
- Pokazuje plan zapytania (physical/optimized/logical plan).
- Można tu znaleźć, jak Spark zoptymalizował zapytanie.
