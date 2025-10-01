# 2D Ising Model Monte Carlo Simulation (Metropolis)

This repository contains a C++ implementation of a **2D Ising Model** Monte Carlo simulation using the **Metropolis algorithm**. It allows simulations on square lattices with various starting configurations and customizable parameters. The program supports seeding from `/dev/urandom` for reproducibility and can save/load configurations.

---

## Contents

* **`main.cpp`** – Main program: initializes the system, performs sweeps, and measures observables.
* **`init.cpp`** – Initializes lattice configurations (cold, hot, or from a previous run).
* **`met.cpp`** – Metropolis sweep implementation.
* **`measure.cpp`** – Measures energy (E) and magnetization (M).
* **`end.cpp`** – Saves the final configuration to `conf`.
* **`options.cpp`** – Handles command-line options and seeding.
* **`include.h`** – Header file with global variables, constants, and function declarations.

---

## Features

* **2D Square Lattice Ising Model**
* **Metropolis Algorithm** for Monte Carlo updates
* **Supports three initial configurations:**

  * Cold start (`start=0`): all spins up
  * Hot start (`start=1`): random spins
  * Previous configuration (`start=2`): load from `conf`
* **Command-line options** to customize simulations
* **Seeding options**: manual or `/dev/urandom`
* Saves final configuration and RNG state for reproducibility

---

## Compilation

```bash
g++ -std=c++11 main.cpp init.cpp met.cpp measure.cpp end.cpp options.cpp -o is
```

---

## Usage

```bash
./is -L <lattice_length> -b <beta> -s <start> -S <seed> -n <nsweep>
```

### Options

* `-L` : Lattice length (N = L*L)
* `-b` : Inverse temperature β (overrides value in config)
* `-s` : Start configuration (0=cold, 1=hot, 2=old config)
* `-S` : RNG seed (overrides value in config)
* `-n` : Number of sweeps (measurements of E and M)
* `-u` : Seed using `/dev/urandom`
* `-h` : Display help message

**Example:**

```bash
./is -L 20 -b 0.4 -s 1 -S 12345 -n 1000
```

* Output is printed as energy (E) and magnetization (M) per sweep.
* Final configuration and RNG state are saved in `conf`.

---

## Notes

* The program is based on *M.E.J. Newman and G.T. Barkema, Monte Carlo Methods in Statistical Physics, 2002*.
* Probabilities for spin flips are precomputed during initialization.
* Supports reproducibility by saving and loading RNG state.
* Designed for experimentation with lattice sizes, β values, and sweep numbers.

---

## Dependencies

* C++11 or higher
* Standard libraries (`<iostream>`, `<fstream>`, `<random>`, `<string>`, `<ctime>`, `<unistd.h>`)
* Optional: `MIXMAX` random number engine (included in repository)

---

## Output

* **Standard output:** energy and magnetization per sweep.
* **Files:**

  * `conf` : final lattice configuration and RNG state
  * `conf.old` : backup of previous configuration

---

## Author

C++ implementation adapted for Metropolis Monte Carlo simulations of the 2D Ising model.
