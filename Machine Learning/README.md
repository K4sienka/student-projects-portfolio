# Machine Learning

This folder contains university laboratory exercises and projects covering supervised and unsupervised machine learning, classification, regression, clustering, exploratory data analysis, feature engineering, and data preprocessing.

## Projects

### Wine Classification

Classification of wines from the scikit-learn Wine dataset using K-Nearest Neighbors and Random Forest. The notebook includes feature scaling, train-test splitting, model evaluation, confusion matrices, and comparison of classification metrics.

**File:** `01-wine-classification-knn-random-forest.ipynb`

### Volve Well-Log Clustering

Unsupervised analysis of geological well-log data from the Volve oil field. The notebook covers data cleaning, outlier detection, interpolation, feature transformation, K-Means clustering, cluster evaluation, and visualization of geological profiles.

**File:** `02-volve-well-log-clustering.ipynb`

### Boston Housing Regression

Supervised regression analysis using the Boston Housing dataset. Linear Regression and XGBoost models are compared using MSE, MAE, and R². The notebook also includes hyperparameter tuning with GridSearchCV and residual diagnostics.

**File:** `03-boston-housing-regression.ipynb`

### Plant Protection Products EDA

Exploratory analysis of a registry of plant protection products. The project examines missing data, manufacturers, product types, authorization dates, package sizes, and health, environmental, and physical hazard categories.

**File:** `04-plant-protection-products-eda.ipynb`

### Titanic Data Preparation

A set of exercises focused on preparing the Titanic dataset for machine learning.

- `05-titanic-missing-data-analysis-report.tex` — a LaTeX report covering initial inspection, missing-value analysis, visualization, and discussion of missing-data mechanisms.
- `06-titanic-feature-cardinality-reduction.ipynb` — analysis of categorical cardinality and reduction of cabin labels.
- `07-titanic-train-test-preprocessing.ipynb` — train-test splitting, category mapping, handling unseen labels, and comparison of original and reduced categorical features.

## Related Team Project

A separate repository named **`agh-projekt-uczenie-maszynowe`** is available on my GitHub profile. It contains a team project developed with other students in which we integrated an external AI service through an API and created an application that prepares personalized diet plans for users.

## Suggested Structure

```text
Machine Learning/
├── README.md
├── 01-wine-classification-knn-random-forest.ipynb
├── 02-volve-well-log-clustering.ipynb
├── 03-boston-housing-regression.ipynb
├── 04-plant-protection-products-eda.ipynb
├── 05-titanic-missing-data-analysis-report.tex
├── 06-titanic-feature-cardinality-reduction.ipynb
└── 07-titanic-train-test-preprocessing.ipynb
```

## Technologies

- Python
- Jupyter Notebook
- pandas
- NumPy
- matplotlib
- seaborn
- scikit-learn
- XGBoost
- GridSearchCV
- K-Means
- Isolation Forest
- LaTeX

## Main Topics

- Exploratory data analysis
- Data cleaning and feature engineering
- Classification and regression
- Clustering and outlier detection
- Hyperparameter tuning
- Model evaluation
- Missing-data analysis
- Categorical feature preprocessing