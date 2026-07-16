Ship Navigation Simulation in C

This project simulates a ship navigating a grid-based map to find a route from the starting position to a destination port. The map includes depth constraints, and the ship must avoid areas where the water is too shallow.

Features:
- **Grid-Based Map:**
  - The map is represented as a 2D grid where each cell indicates water depth.
- **Dynamic Navigation:**
  - The ship dynamically calculates a path from the top-left corner to the bottom-right corner of the grid.
  - Movement is constrained by water depth and avoids revisiting cells.
- **Recursive Pathfinding:**
  - Uses recursion to explore possible routes and backtracks when a path is blocked.

