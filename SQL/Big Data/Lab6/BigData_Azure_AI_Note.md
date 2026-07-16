## 1. Najważniejsze narzędzia analityczne/Big Data/AI.
W chmurze (np. Azure) jest sporo narzędzi, które pomagają wykonywać analizę danych, Big Data czy sztucznej inteligencji. Najpierw są narzędzia takie jak:
- do przechowywania danych:  Azure Data Lake albo Blob Storage (tu surowe dane, które spływają z różnych źródeł) 
- do przetwarzania danych: Azure Synapse Analytics (połączenie SQL i Sparka) albo Azure Data Factory (budowanie przepływów danych) 
- analiza na żywo albo dane z urządzeń: Azure Event Hubs, Stream Analytics czy IoT Hub
- do pracy z danymi i modeli używa się Azure Databricks (Spark w chmurze, ale bardziej user-friendly) 
- do tematów związanych ze sztuczną inteligencją, to mamy Azure Machine Learning (do tworzenia i trenowania modeli) i AutoML (jak nie chce się pisać kodu). 
    Gotowe są do tego modele AI, np. Cognitive Services, które potrafią rozpoznawać tekst, obraz, mowę itd. 
- do wizualizacji wyników używa się Power BI (do budowania raportów).


## 2. Opis wybranego zagadnienia 
### Analiza opinii klientów w e-commerce (Azure)
Chcemy sprawdzić, co klienci myślą o naszych produktach w sklepie internetowym. Zbieramy ich opinie, komentarze, oceny gwiazdkowe i chcemy to przeanalizować. 

W tym celu używamy Azure. Najpierw dane z formularzy, recenzji czy mediów społecznościowych wpadają do Azure Event Hubs albo od razu trafiają do Data Lake, gdzie przechowujemy je w formacie tekstowym albo JSON.
Potem używamy Azure Data Factory, żeby przenieść i przygotować te dane do analizy. Na etapie analizy tekstu możemy skorzystać z Cognitive Services – jest tam gotowe narzędzie do analizy sentymentu, które sprawdza, czy opinia jest pozytywna, neutralna czy negatywna. Można stworzyć cos bardziej zaawansowanego, wtedy w Azure Machine Learning można wytrenować swój własny model NLP (przetwarzania języka naturalnego).
Wyniki trafiają do Power BI, gdzie budujemy raporty: np. które produkty mają najwięcej negatywnych opinii, jak zmienia się sentyment w czasie, albo czy użytkownicy narzekają na konkretne funkcje. Dzięki temu dział marketingu albo product ownerzy mogą szybciej reagować i wprowadzać zmiany tam, gdzie trzeba.
