# Matrix Calculus

This folder contains MATLAB projects completed for the **Matrix Calculus** course. The exercises cover matrix multiplication, systems of linear equations, matrix factorizations, induced norms, condition numbers, eigenvalue algorithms, and singular value decomposition.

## Projects

### 1. Recursive Binet Matrix Multiplication

Implementation of recursive block matrix multiplication based on Binet's method, combined with the classical multiplication algorithm for smaller submatrices.

The script:

- multiplies square matrices whose dimensions are powers of two,
- switches to traditional multiplication below a selected recursion threshold,
- counts floating-point operations,
- measures execution time for different matrix sizes and threshold values,
- verifies the result against MATLAB's built-in matrix multiplication.

**File:** `01-recursive-binet-matrix-multiplication.m`

### 2. Gaussian Elimination and LU Factorization

Implementation and comparison of four methods for solving systems of linear equations:

- Gaussian elimination without pivoting,
- Gaussian elimination with partial pivoting,
- LU factorization without pivoting,
- LU factorization with partial pivoting.

The Live Script uses a controlled test matrix, compares solution errors and residuals, and demonstrates why pivoting improves numerical stability.

**File:** `02-gaussian-elimination-and-lu-factorization.mlx`

### 3. Matrix Norms and Condition Numbers

Analysis of induced matrix norms and condition numbers.

The project calculates:

- the matrix 1-norm and `cond₁`,
- the matrix 2-norm and `cond₂`,
- a numerically approximated p-norm for `p = 3` and its condition number,
- the infinity norm and `cond∞`.

Manual calculations are compared with MATLAB's built-in `norm` and `cond` functions.

**File:** `03-matrix-norms-and-condition-numbers.mlx`

### 4. Singular Value Decomposition of a Rectangular Matrix

Manual construction of the singular value decomposition of a rectangular matrix using two approaches:

1. eigenvalues and eigenvectors of `A * Aᵀ`,
2. eigenvalues and eigenvectors of `Aᵀ * A`.

The project constructs the `U`, `S`, and `V` matrices, verifies the reconstruction `A = U * S * Vᵀ`, examines the null space and column space, and compares the results with MATLAB's `svd` function.

**File:** `04-rectangular-matrix-svd.mlx`

### 5. Power Method, Deflation, and SVD

Implementation of the power method for a random `3 × 3` matrix.

The script:

- applies the power method to `B = A * Aᵀ`,
- uses deflation to approximate three eigenvalue–eigenvector pairs,
- compares convergence for the norms `p = 1, 2, 3, 4, ∞`,
- generates fifteen convergence plots,
- constructs an SVD from the eigenvectors of `A * Aᵀ`,
- compares eigenvalues, eigenvectors, and reconstruction errors with MATLAB's `eig` and `svd` functions.

**File:** `05-power-method-deflation-and-svd.m`

## Technologies

- MATLAB
- MATLAB Live Scripts
- numerical linear algebra
- matrix visualization
- performance measurement

## Main Topics

- Classical and recursive matrix multiplication
- Floating-point operation counting
- Gaussian elimination
- Partial pivoting
- LU factorization
- Matrix norms
- Condition numbers
- Eigenvalues and eigenvectors
- Power method and deflation
- Singular value decomposition
- Matrix rank, column space, and null space
- Numerical accuracy and reconstruction errors
