# Statistical Modeling

This folder contains university laboratory exercises and reports focused on statistical modeling in R. The projects cover descriptive statistics, correlation, linear and polynomial regression, multiple regression, generalized linear models, ordinal regression, model diagnostics, feature selection, and predictive modeling.

## Contents

### 1. Regression Metrics and Model Comparison

An introductory exercise using simulated data to explain residuals and compare linear and polynomial regression. It visualizes prediction errors and calculates MSE, RMSE, and MAE.

**File:** `01-regression-metrics-and-model-comparison.R`

### 2. Earthquake Regression Analysis

Analysis of the `quakes` dataset containing earthquake observations near Fiji. The script includes descriptive statistics, visualization of epicentres, covariance and correlation, linear regression between earthquake magnitude and the number of reporting stations, and calculation of RSS, RSE, and R².

**File:** `02-earthquake-regression-analysis.R`

### 3. Air Quality and Monthly Regression

Analysis of the built-in `airquality` dataset. The exercise covers missing-value removal, outlier detection, temperature conversion, grouped ozone summaries, and separate linear regression models for individual months.

**File:** `03-air-quality-outliers-and-monthly-regression.R`

### 4. Linear and Polynomial Regression

Comparison of linear regression with polynomial models of degrees 2–10 using geophysical measurements. The models are evaluated with regression coefficients, RSS, and R².

**File:** `04-linear-and-polynomial-regression.R`

### 5. Air Pollution Multiple Regression

A multiple linear regression model predicting temperature from concentrations of SO₂, NO₂, CO, and O₃. The exercise includes missing-data handling, correlation analysis, removal of strongly correlated particulate-matter variables, model evaluation, and prediction for selected pollutant concentrations.

**File:** `05-air-pollution-multiple-regression.R`

### 6. Annual Rainfall Regression Analysis

A weather-data project focused on predicting mean annual rainfall. It includes data cleaning, train-test splitting, correlation analysis, baseline models, simple and multiple linear regression, nonlinear transformations, forward and backward feature selection, and evaluation with RMSE and R².

**File:** `06-annual-rainfall-regression-analysis.R`

### 7. Generalized and Ordinal Regression Report

A comprehensive report covering multiple linear regression, Poisson regression, ordinal regression, and logistic regression. The analyses use datasets related to real estate prices, vehicle fuel economy, ship incidents, esophageal cancer, customer satisfaction, and wine ratings. The report also examines model assumptions using AIC, VIF, residual diagnostics, and statistical tests.

**File:** `07-generalized-and-ordinal-regression-report.pdf`

### 8. Diabetes Glucose Prediction with Tree Models

A predictive modeling report comparing CART, Random Forest, and XGBoost for forecasting a patient's mean glucose level on the next available day. The project uses historical glucose measurements, insulin, meals, and activity data, with temporal splitting, hyperparameter tuning, prediction-error analysis, and feature importance.

**File:** `08-diabetes-glucose-tree-models-report.pdf`

## Suggested Structure

```text
Statistical Modeling/
├── README.md
├── 01-regression-metrics-and-model-comparison.R
├── 02-earthquake-regression-analysis.R
├── 03-air-quality-outliers-and-monthly-regression.R
├── 04-linear-and-polynomial-regression.R
├── 05-air-pollution-multiple-regression.R
├── 06-annual-rainfall-regression-analysis.R
├── 06-annual-rainfall-regression-analysis.Rmd
├── 07-generalized-and-ordinal-regression-report.pdf
└── 08-diabetes-glucose-tree-models-report.pdf
```

## Technologies

- R
- R Markdown
- ggplot2
- tidyverse
- mosaic
- caTools
- GGally
- corrplot
- MASS
- ordinal
- lmtest
- car
- Random Forest
- XGBoost

## Main Topics

- Descriptive statistics and data visualization
- Correlation and covariance
- Linear, polynomial, and multiple regression
- Poisson, logistic, and ordinal regression
- Residual and assumption diagnostics
- Feature selection
- Regression error metrics
- Decision trees and ensemble models
- Predictive modeling and model comparison
