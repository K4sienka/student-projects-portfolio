# Engineering Thesis — Stroke Risk Prediction

This folder contains my engineering thesis project focused on predicting stroke risk from demographic, health, and lifestyle data using machine learning.

The project was completed as part of the **Data Engineering and Analysis** degree programme at AGH University of Krakow.

## Project Objective

The objective of the study was to evaluate whether selected machine learning methods can identify patients at increased risk of stroke using tabular medical data.

The task was formulated as a binary classification problem:

- `0` — no stroke,
- `1` — stroke.

The analysis covers the complete machine learning workflow, including data cleaning, exploratory data analysis, preprocessing, model training, class-imbalance handling, evaluation, and model interpretation.

## Files

### `stroke-risk-prediction-analysis.ipynb`

The main Jupyter Notebook containing:

- data loading and cleaning,
- exploratory data analysis,
- visualisation of numerical and categorical features,
- correlation analysis,
- train, validation, and test splitting,
- feature encoding and scaling,
- model training and evaluation,
- class-imbalance experiments,
- threshold tuning,
- permutation feature importance,
- PCA and K-Means analysis,
- Precision–Recall curve comparison.

### `healthcare-stroke-data.csv`

The dataset used in the analysis. It contains demographic, medical, and lifestyle information for 5,110 patients. This dataset can be found here: https://www.kaggle.com/datasets/aouatifcherdid/healthcare-dataset-stroke-data

## Dataset

The dataset includes the following variables:

- gender,
- age,
- hypertension,
- heart disease,
- marital status,
- work type,
- residence type,
- average glucose level,
- BMI,
- smoking status,
- stroke occurrence.

The original dataset contains 5,110 observations. After removing the identifier column, missing BMI values, and one very rare gender category, 4,908 observations remained.

The positive class represents approximately 4.3% of the cleaned dataset, making this a strongly imbalanced classification problem.

## Methodology

The data was divided into training, validation, and test sets using stratified sampling:

- 64% training data,
- 16% validation data,
- 20% test data.

All transformations requiring fitted parameters were performed inside machine learning pipelines to reduce the risk of data leakage.

Numerical features were scaled where required, while categorical variables were encoded using One-Hot Encoding.

## Models

The following models were compared:

- Logistic Regression,
- Random Forest,
- XGBoost.

Several approaches to class imbalance were also evaluated:

- class weighting,
- decision-threshold tuning,
- random oversampling,
- random undersampling,
- SMOTENC.

## Evaluation Metrics

Because stroke cases form a small minority of the dataset, model evaluation focused on metrics suitable for imbalanced classification:

- recall,
- precision,
- F1-score,
- ROC-AUC,
- PR-AUC.

Accuracy alone was not treated as a reliable measure because a model could achieve high accuracy by predicting only the majority class.

## Main Results

- Logistic Regression achieved the highest ranking performance, with `ROC-AUC = 0.811` and `PR-AUC = 0.218`.
- XGBoost with a tuned decision threshold achieved the highest F1-score for the stroke class: `F1 = 0.248`.
- Random Forest predicted only the majority class at its default threshold and failed to identify any stroke cases.
- Random undersampling produced the highest recall (`0.786`) but also generated many false-positive predictions.
- Oversampling provided a more balanced precision–recall trade-off than undersampling.
- SMOTENC did not improve the results in this experiment.
- Age was consistently the most important feature according to permutation importance.
- PCA and K-Means showed that stroke and non-stroke observations were not clearly separable using the available features.

The results demonstrate that increasing stroke detection usually comes at the cost of a larger number of false alarms.

## Technologies

- Python 3.11
- Jupyter Notebook
- pandas
- NumPy
- matplotlib
- seaborn
- scikit-learn
- XGBoost
- imbalanced-learn

## Installation

Create and activate a virtual environment:

```bash
python -m venv venv
```

Windows:

```bash
venv\Scripts\activate
```

Linux or macOS:

```bash
source venv/bin/activate
```

Install the required packages:

```bash
pip install pandas numpy matplotlib seaborn scikit-learn xgboost imbalanced-learn jupyter
```

## Running the Analysis

Start Jupyter Notebook:

```bash
jupyter notebook
```

Open:

```text
stroke-risk-prediction-analysis.ipynb
```

The dataset should be loaded using a relative path:

```python
df = pd.read_csv("data/healthcare-stroke-data.csv")
```

## Limitations

The dataset contains a limited number of stroke cases and does not include complete clinical histories, longitudinal measurements, medical imaging, or detailed laboratory results.

The models were developed for educational and research purposes and were not externally validated on an independent patient population.

## Disclaimer

This project is not a medical diagnostic system and must not be used for clinical decision-making. The predictions and conclusions are intended only for educational and research purposes.
