Custom Printf Implementation in C

This project implements a simplified version of the `printf` function, supporting custom formatting for various data types, including integers, floating-point numbers, characters, and strings.

Features:
- **Supported Format Specifiers:**
  - `%d`: Prints integers, including negative values.
  - `%f`: Prints floating-point numbers with a precision of up to 9 decimal places.
  - `%c`: Prints single characters.
  - `%s`: Prints strings.
- Handles special cases:
  - Converts backticks (`) to apostrophes (').
  - Processes multiple `%` characters gracefully.
- Utilizes custom output functions (`outChar`, `outStr`, `outDec`, `outDouble`) for better control and modularity.
