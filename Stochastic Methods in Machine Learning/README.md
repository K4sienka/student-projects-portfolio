# Stochastic Methods in Machine Learning

This folder contains laboratory exercises completed for the **Stochastic Methods in Machine Learning** course. The projects cover gradient-based optimization, adversarial examples, Bayesian and evolutionary optimization, multiobjective problems, and neural network generalization.

## Laboratory Exercises

### 01 — Gradient Descent for Linear Regression

Implementation of gradient descent in R for a simple linear regression problem. The exercise examines learning rates, training epochs, the loss landscape, and comparison with the analytical least-squares solution.

**File:** `01-gradient-descent-linear-regression.R`

### 02 — Momentum and Adam Optimization

Implementation and comparison of Momentum and Adam on the Sphere, Rosenbrock, and Rastrigin benchmark functions. The project includes convergence analysis and optimization-path visualizations.

**File:** `02-momentum-and-adam-optimization.py`

### 03 — Adversarial Examples with FGSM

Training a neural network on MNIST and generating adversarial examples with the Fast Gradient Sign Method. The notebook also compares SGD, Adagrad, and Adam and studies the effect of the attack strength.

**File:** `03-adversarial-examples-fgsm-mnist.ipynb`

### 04 — Model-Based Offline Optimization

Optimization of black-box functions using a neural surrogate model trained on previously collected data. The experiments investigate the impact of dataset size and the robustness of gradient-based optimization.

**File:** `04-model-based-offline-optimization.ipynb`

### 05 — CatBoost and Optuna Classification

Forest cover type classification using CatBoost. Optuna is used for hyperparameter tuning, followed by model evaluation, confusion-matrix analysis, and feature-importance interpretation.

**File:** `05-catboost-optuna-forest-cover-classification.ipynb`

### 06 — Bayesian Optimization

Introduction to Bayesian optimization with a Gaussian-process surrogate model. The notebook compares acquisition strategies such as Upper Confidence Bound, Probability of Improvement, and exploratory alternatives.

**File:** `06-bayesian-optimization.ipynb`

### 07 — Gaussian Distributions and the Central Limit Theorem

Experiments with univariate and multivariate normal distributions, the three-sigma rule, covariance matrices, and simulations illustrating the Central Limit Theorem.

**File:** `07-gaussian-distributions-and-clt.ipynb`

### 08 — CMA-ES Black-Box Optimization

Application of the Covariance Matrix Adaptation Evolution Strategy to benchmark functions. The experiments examine starting points, global step size, convergence, covariance adaptation, and search dynamics.

**File:** `08-cma-es-black-box-optimization.ipynb`

### 09 — CMA-ES vs Gradient-Based Training

Comparison of CMA-ES with gradient-based neural network training on the Two Moons classification problem. The analysis covers accuracy, training time, network size, and decision boundaries.

**File:** `09-cma-es-vs-gradient-neural-network-training.ipynb`

### 10 — Differential Evolution and SHADE

Implementation of Differential Evolution with mutation, crossover, and selection. The notebook evaluates the method on benchmark functions, studies its hyperparameters, and introduces the adaptive SHADE variant.

**File:** `10-differential-evolution-and-shade.ipynb`

### 11 — LLM-Generated Evolutionary Heuristics

Use of a large language model to generate, evaluate, and evolve optimization heuristics. Generated algorithms are benchmarked on the Rastrigin function and compared across repeated runs.

**File:** `11-llm-generated-evolutionary-heuristics.ipynb`

> **Security note:** The API key must be loaded from an environment variable. Never store or commit an API key directly in a notebook.

### 12 — Multiobjective Portfolio Optimization

Portfolio allocation as a multiobjective optimization problem balancing expected return and risk. The notebook uses Pareto-optimal solutions and evolutionary multiobjective optimization.

**File:** `12-multiobjective-portfolio-optimization.ipynb`

### 13 — Grokking and Delayed Generalization

Reproduction of the grokking phenomenon using a neural network trained on modular addition. The experiment compares memorization and generalization and studies the influence of optimization methods.

**File:** `13-grokking-delayed-generalization.ipynb`

### 14 — Markov Chains and Monte Carlo Text Analysis

A text-analysis project based on the dialogue from Shakespeare's *Hamlet*. A first-order word-level Markov chain is used to model transitions between words and generate new sentences. The project also compares Markov-based generation with independent random word sampling.

The analysis includes:

- extraction and cleaning of character dialogue,
- construction of word-transition probabilities,
- Markov and random sentence generation,
- Monte Carlo sampling of generated sentences,
- word-frequency and Zipf-distribution analysis,
- transition entropy for identifying unpredictable words,
- interactive word-transition networks created with PyVis.

**Folder:** `14-markov-chain-text-analysis/`

## Technologies

- Python
- R
- Jupyter Notebook
- NumPy
- pandas
- matplotlib
- Plotly
- PyTorch
- scikit-learn
- CatBoost
- Optuna
- Bayesian Optimization
- CMA-ES
- pymoo
- PyVis

## Topics

- Gradient descent, Momentum, and Adam
- Stochastic and black-box optimization
- Adversarial machine learning
- Bayesian optimization
- Evolutionary algorithms
- Probability distributions and the Central Limit Theorem
- Markov chains and transition probabilities
- Monte Carlo simulation
- Entropy and Zipf's law
- Text generation and network visualization
- Multiobjective optimization
- Neural network training and generalization
