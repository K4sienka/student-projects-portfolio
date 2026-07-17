# Spatial Data Analysis

This folder contains laboratory exercises and a final project completed for the **Spatial Data Analysis** course. The work focuses on spatial point patterns, point-process intensity, spatial dependence, covariates, inhomogeneous processes, and density-based spatial clustering in R.

## Projects

### 1. Random Point Patterns and Complete Spatial Randomness

Simulation of uniformly distributed points inside rectangular and circular observation windows. The exercise creates a spatial point pattern, applies a quadrat test, and compares the result with a homogeneous Poisson process.

**File:** `01-random-point-patterns-and-csr.Rmd`

### 2. Point-Process Intensity Analysis

Analysis of gold deposit locations from the `murchison` dataset. The script examines quadrat counts, tests whether points follow a random spatial pattern, and visualizes kernel density estimates using standard, contour, and 3D plots.

**File:** `02-point-process-intensity-analysis.R`

### 3. Spatial Relationships Between Points

Comparison of independent, regular, and clustered point patterns generated with Poisson, Strauss, and Matérn cluster processes. The analysis uses nearest-neighbour distances, the G-function, Ripley's K-function, and distance maps.

**File:** `03-spatial-point-pattern-interactions.R`

### 4. Spatial Covariates: Gold Deposits and Faults

Analysis of the relationship between gold deposits and geological faults in the Murchison region. The script creates distance maps and distance functions and estimates how point intensity changes with distance from the nearest fault.

**File:** `04-spatial-covariates-gold-and-faults.R`

### 5. Inhomogeneous Point-Process Modeling

Analysis of tree locations from the `lansing` dataset. The script compares species-specific density patterns, fits homogeneous and spatial-trend Poisson point-process models, examines residuals, generates simulated patterns, and performs model diagnostics.

**File:** `05-inhomogeneous-point-process-modeling.R`

### 6. Spatial Clustering in Kraków

A spatial clustering project comparing DBSCAN and HDBSCAN on point data for Kraków. The analysis examines how `eps` and `minPts` influence detected clusters and noise and compares both methods for areas with different point densities.

**File:** `06-krakow-spatial-clustering-dbscan-hdbscan.Rmd`

## Suggested Structure

```text
Spatial Data Analysis/
├── README.md
├── 01-random-point-patterns-and-csr.Rmd
├── 02-point-process-intensity-analysis.R
├── 03-spatial-point-pattern-interactions.R
├── 04-spatial-covariates-gold-and-faults.R
├── 05-inhomogeneous-point-process-modeling.R
├── 06-krakow-spatial-clustering-dbscan-hdbscan.Rmd
└── data/
    ├── krakow-points/
    └── krakow-districts/
```

## Technologies

- R
- R Markdown
- `spatstat`
- `sf`
- `dbscan`
- `ggplot2`

## Main Topics

- Spatial point-pattern simulation
- Complete Spatial Randomness
- Quadrat tests
- Kernel density estimation
- Homogeneous and inhomogeneous Poisson processes
- Strauss and Matérn cluster processes
- Nearest-neighbour analysis
- G-functions and Ripley's K-functions
- Spatial covariates and distance functions
- DBSCAN and HDBSCAN
- Spatial visualization and model diagnostics
