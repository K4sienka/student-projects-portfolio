import numpy as np
from abc import ABC, abstractmethod
import plotly.io as pio
pio.renderers.default = "browser"
import matplotlib.pyplot as plt
import plotly.graph_objects as go

#funckje testowe
class Problem(ABC):
    @abstractmethod
    def __call__(self, x: np.ndarray) -> float:
        """Compute the function value at point x."""
        raise NotImplementedError
    
    @abstractmethod
    def grad(self, x: np.ndarray) -> np.ndarray:
        """Compute the gradient at point x."""
        raise NotImplementedError

class Sphere(Problem):
    def __call__(self, x: np.ndarray) -> float:
        return np.sum(x**2)
    
    def grad(self, x: np.ndarray) -> np.ndarray:
        return 2 * x

class Rosenbrock(Problem):
    def __call__(self, x: np.ndarray) -> float:
        return np.sum(100.0 * (x[1:] - x[:-1]**2)**2 + (1 - x[:-1])**2)
    
    def grad(self, x: np.ndarray) -> np.ndarray:
        grad = np.zeros_like(x)
        n = x.size
        grad[0] = -400 * x[0] * (x[1] - x[0]**2) - 2 * (1 - x[0])
        for i in range(1, n - 1):
            grad[i] = 200 * (x[i] - x[i-1]**2) - 400 * x[i] * (x[i+1] - x[i]**2) - 2 * (1 - x[i])
        grad[-1] = 200 * (x[-1] - x[-2]**2)
        return grad

class Rastrigin(Problem):
    def __call__(self, x: np.ndarray) -> float:
        A = 10
        n = x.size
        return A * n + np.sum(x**2 - A * np.cos(2 * np.pi * x))
    
    def grad(self, x: np.ndarray) -> np.ndarray:
        A = 10
        return 2 * x + 2 * np.pi * A * np.sin(2 * np.pi * x)


#wizualizacje

def prepare_mesh_grid(
    problem: Problem,
    bounds: tuple[float, float] = (-5.0, 5.0),
    grid_size: int = 50,
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    x_vals = np.linspace(bounds[0], bounds[1], grid_size)
    y_vals = np.linspace(bounds[0], bounds[1], grid_size)
    X, Y = np.meshgrid(x_vals, y_vals)

    Z = np.zeros_like(X)
    for i in range(grid_size):
        for j in range(grid_size):
            xy = np.array([X[i, j], Y[i, j]])
            Z[i, j] = problem(xy)

    return X, Y, Z, x_vals, y_vals


def plot_3d_surface(
    problem: Problem,
    grid_size: int = 50,
):
    X, Y, Z, _, _ = prepare_mesh_grid(problem=problem, grid_size=grid_size)

    fig = plt.figure(figsize=(8, 6))
    ax = fig.add_subplot(111, projection="3d")
    surf = ax.plot_surface(X, Y, Z, cmap="viridis", edgecolor="none")

    ax.set_title(problem.__class__.__name__)
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("f(x, y)")

    fig.colorbar(surf, shrink=0.5, aspect=10)
    plt.tight_layout()
    plt.show()

def plot_contour_and_paths(
    problem: Problem,
    paths: list[np.ndarray],
    grid_size: int = 200,
    title: str = "",
):
    """
    Create an interactive contour plot of a 2D function and overlay multiple optimization paths.

    Args:
        problem: An instance of a Problem class.
        paths: List of numpy arrays; each array is of shape (epochs, 2) containing an optimization trajectory.
        title: Title for the plot.
    """
    _, _, Z, x_vals, y_vals = prepare_mesh_grid(problem, grid_size=grid_size)

    fig = go.Figure(
        data=go.Contour(
            x=x_vals,
            y=y_vals,
            z=Z,
            colorscale="Viridis",
            contours=dict(showlines=False),
            colorbar=dict(title="Function Value"),
        )
    )

    colors = ['red', 'blue', 'green', 'purple', 'orange', 'cyan', 'magenta', 'yellow', 'pink', 'brown']
    
    for idx, path in enumerate(paths):
        color_idx = idx % len(colors)
        fig.add_trace(
            go.Scatter(
                x=path[:, 0],
                y=path[:, 1],
                mode="lines+markers",
                marker=dict(size=4),
                line=dict(width=2, color=colors[color_idx]),
                name=f"Run {idx+1}",
                showlegend=True,
            )
        )

    fig.update_layout(
        title=title, xaxis_title="x", yaxis_title="y", width=800, height=700,
        legend=dict(orientation="h", yanchor="bottom", y=1.02, xanchor="right", x=1)
    )

    fig.show()




#ZADANIE 1
#wywolanie funkcji
problems = [Sphere(), Rosenbrock(), Rastrigin()]

for problem in problems:
    plot_3d_surface(problem)
    plot_contour_and_paths(problem, [], title=problem.__class__.__name__)

#najlatwiejsze wydaje sie sphere bo ma jedno gladkie min. Najtrudniejsze wydaje sie rastrigin bo ma wiele min lokalnych

#ZADANIE 2
#funkcja momentum
def momentum(problem, initial_solution, alpha, beta, number_of_epochs):
    '''
    Where:
    initial_solution is your starting point.
    alpha is the learning rate.
    beta is the momentum parameter (commonly 0.9).

    Returns a tuple of:
    positions: np.ndarray of shape (number_of_epochs, dim) — the optimization path.
    function_values: np.ndarray of shape (number_of_epochs,) — function value at each epoch.
    velocity_norms: np.ndarray of shape (number_of_epochs,) — velocity norm at each epoch.
    '''
    x = initial_solution.astype(float).copy() #aktualny punkt
    v = np.zeros_like(x) #predkosc

    positions = np.zeros((number_of_epochs, len(x))) #sciezka do optymalizacji
    function_values = np.zeros(number_of_epochs) #wartosc funkcji w kazdej epoce
    velocity_norms = np.zeros(number_of_epochs) #norma predkosci

    #po kazdej epoce
    for epoch in range(number_of_epochs):
        grad = problem.grad(x) #gradient
        v = beta * v + alpha * grad #nowe V
        x = x - v #przesuwamy punkt w strone minimum

        positions[epoch] = x #pozycja punktu -> do rysowania sciezki
        function_values[epoch] = problem(x) #zapisanie wartosci funkcji w tym punkcie -> spr czy f. maleje
        velocity_norms[epoch] = np.linalg.norm(v) #dlugosc predkosci -> spr czy algorytm zwalnia zblizajac sie do min

    return positions, function_values, velocity_norms

##Uzycie momentum
initial_solution = np.array([2.0, 2.0])

#sphere
positions, function_values, velocity_norms = momentum(
        problem=Sphere(),
        initial_solution=initial_solution,
        alpha=0.01,
        beta=0.9,
        number_of_epochs=100)

plt.figure()
plt.plot(function_values)
plt.title(f"Sphere - function value")
plt.xlabel("Epoch")
plt.ylabel("f(x)")
plt.show()

plt.figure()
plt.plot(velocity_norms)
plt.title(f"Sphere - velocity norm")
plt.xlabel("Epoch")
plt.ylabel("||v||")
plt.show()

#ZADANIE 3
#rosenbronck i rastrigin z mniejszymi alpha
for alpha in [0.001, 0.0001, 0.00001]:
    positions, function_values, velocity_norms = momentum(
        problem=Rosenbrock(),
        initial_solution=initial_solution,
        alpha=alpha,
        beta=0.9,
        number_of_epochs=100
    )

    plt.figure()
    plt.plot(function_values)
    plt.title(f"Rosenbrock - alpha={alpha}")
    plt.xlabel("Epoch")
    plt.ylabel("f(x)")
    plt.show()

for alpha in [0.001, 0.0001, 0.00001]:
    positions, function_values, velocity_norms = momentum(
        problem=Rastrigin(),
        initial_solution=initial_solution,
        alpha=alpha,
        beta=0.9,
        number_of_epochs=100
    )

    plt.figure()
    plt.plot(function_values)
    plt.title(f"Rastrigin - alpha={alpha}")
    plt.xlabel("Epoch")
    plt.ylabel("f(x)")
    plt.show()

#Predkosc na początku rosnie, bo algorytm sie rozpedza i szybciej schodzi w dol funkcji.
#Potem maleje, bo zbliza się do minimum i robi coraz mniejsze kroki
#To pokazuje, że norma predkosci ma związek z szybkoscia zbieżnosci
#-> im jest większa, tym algorytm porusza sie szybciej.


#ZADANIE 4
#rozne beta dla rosenbrock
alpha = 0.0001
initial_solution = np.array([2.0, 2.0])
number_of_epochs = 100

for beta in [0.5, 0.75, 0.9,0.95,0.99]:
    positions, function_values, velocity_norms = momentum(
        problem=Rosenbrock(),
        initial_solution=initial_solution,
        alpha=alpha,
        beta=beta,
        number_of_epochs=100
    )

    plt.figure()
    plt.plot(function_values)
    plt.title(f"Rosenbrock - beta={beta}")
    plt.xlabel("Epoch")
    plt.ylabel("f(x)")
    plt.show()

#wzrost beta powoduje, ze algorytm ma większy rozpęd, ale pojawiaja się oscylacje.
#Dla mniejszych wartosci beta zbieznośsc jest bardziej stabilna, a dla bardzo duzych,
#metoda staje sie niestabilna i trudniej dochodzi do minimum.

#ZADANIE 5
#Optymalizator Adama
def adam(problem, initial_solution, alpha, beta1, beta2, number_of_epochs, epsilon):
    x = initial_solution.astype(float).copy() #start
    m = np.zeros_like(x) #srednia gradientow
    v = np.zeros_like(x) #predkosc

    positions = np.zeros((number_of_epochs, len(x)))
    function_values = np.zeros(number_of_epochs)
    gradient_norms = np.zeros(number_of_epochs)

    for t in range(1, number_of_epochs + 1):
        grad = problem.grad(x)

        m = beta1 * m + (1 - beta1) * grad
        v = beta2 * v + (1 - beta2) * (grad ** 2)

        m_hat = m / (1 - beta1 ** t)
        v_hat = v / (1 - beta2 ** t)

        x = x - alpha * m_hat / (np.sqrt(v_hat) + epsilon)

        positions[t - 1] = x
        function_values[t - 1] = problem(x)
        gradient_norms[t - 1] = np.linalg.norm(grad)
    return positions, function_values, gradient_norms

#ZADANIE 6
#Porownanie metod
problems = [
    (Sphere(), 0.01),
    (Rosenbrock(), 0.0001),
    (Rastrigin(), 0.001)
]

for problem, alpha_m in problems:
    pos_m, val_m, vel_m = momentum(
        problem=problem,
        initial_solution=np.array([2.0, 2.0]),
        alpha=alpha_m,
        beta=0.9,
        number_of_epochs=100
    )

    pos_a, val_a, grad_a = adam(
        problem=problem,
        initial_solution=np.array([2.0, 2.0]),
        alpha=0.01,
        beta1=0.9,
        beta2=0.999,
        number_of_epochs=100,
        epsilon=1e-8
    )

    plot_contour_and_paths(problem, [pos_m, pos_a], title=problem.__class__.__name__)

    plt.figure()
    plt.plot(val_m, label="Momentum")
    plt.plot(val_a, label="Adam")
    plt.title(f"{problem.__class__.__name__} - function value")
    plt.xlabel("Epoch")
    plt.ylabel("f(x)")
    plt.legend()
    plt.show()

#Dla Sphere: Momentum zbiega szybciej
#Dla Rosenbrocka Adam schodzi bardziej plynnie i stabilnie
#Dla Rastrigina obie metody osiągają podobny wynik, chociaż Momentum ma wieksze oscylacje    
