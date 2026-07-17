# Data Analysis in Python

This folder contains laboratory projects completed for the **Data Analysis in Python** course. The notebooks cover data cleaning, exploratory data analysis, descriptive statistics, visualization, correlation, regression, clustering, and geospatial analysis.

## Projects

### 1. Holocene Volcanism

Analysis of volcanic eruptions recorded during the Holocene period.

- `01-data-preparation.ipynb` — cleaning eruption records, selecting variables, handling missing values, and preparing the dataset.
- `02-exploratory-analysis.ipynb` — identifying the largest eruptions, the most active volcanoes, recent major eruptions, and creating basic frequency distributions.
- `03-distributions-and-detection-methods.ipynb` — advanced frequency tables, eruption detection methods, and visualization of eruptions over time.

### 2. GDP During the 2008–2009 Financial Crisis

Analysis of GDP changes across countries during the global financial crisis.

- `01-data-preparation.ipynb` — importing, cleaning, combining, and preparing economic and country-level datasets.
- `02-tabular-and-visual-analysis.ipynb` — comparison of GDP changes by geographic region and income group using tables and charts.
- `03-descriptive-statistics.ipynb` — calculation and visualization of descriptive statistics, grouped distributions, skewness, and kurtosis.

### 3. Fremont Bridge Bicycle Traffic

Analysis of bicycle traffic and weather conditions in Seattle.

- `01-data-preparation.ipynb` — preparation of hourly bicycle traffic and weather data for 2022.
- `02-exploratory-analysis.ipynb` — tabular and graphical exploration of bicycle traffic and weather patterns.
- `03-correlation-and-regression.ipynb` — correlation analysis and linear and nonlinear regression between weather conditions and bicycle traffic.

### 4. Geospatial Analysis of Poland

Introductory spatial data processing and analysis using geographic data for Poland.

- `01-spatial-data-preparation-and-measurements.ipynb` — importing and preparing data on rivers, cities, districts, and voivodeships; coordinate reference system conversion; GeoPackage export; map visualization; and calculations of length, area, and distance.
- `02-spatial-operations-and-maps.ipynb` — geometric operations, identification of cities near rivers, spatial joins, counting cities by district, and static and interactive map visualization.

### 5. Final Project — Global Economic Indicators

A comprehensive analysis of global economic indicators from the World Bank for 2003–2023.

- `global-economic-indicators-analysis.ipynb` — data transformation and integration, analysis of GDP growth, inflation, unemployment, and economic structure by region and income group, animated choropleth maps, and K-Means clustering of countries based on agriculture, industry, and services.

## Suggested Repository Structure

```text
Data Analysis in Python/
├── README.md
├── 01-holocene-volcanism/
│   ├── 01-data-preparation.ipynb
│   ├── 02-exploratory-analysis.ipynb
│   └── 03-distributions-and-detection-methods.ipynb
├── 02-gdp-financial-crisis/
│   ├── 01-data-preparation.ipynb
│   ├── 02-tabular-and-visual-analysis.ipynb
│   └── 03-descriptive-statistics.ipynb
├── 03-fremont-bridge-bicycle-traffic/
│   ├── 01-data-preparation.ipynb
│   ├── 02-exploratory-analysis.ipynb
│   └── 03-correlation-and-regression.ipynb
├── 04-geospatial-analysis/
│   ├── 01-spatial-data-preparation-and-measurements.ipynb
│   └── 02-spatial-operations-and-maps.ipynb
└── 05-global-economic-indicators/
    └── global-economic-indicators-analysis.ipynb
```

## Technologies

- Python
- Jupyter Notebook
- pandas
- NumPy
- SciPy
- matplotlib
- seaborn
- Plotly
- GeoPandas
- Contextily
- scikit-learn
