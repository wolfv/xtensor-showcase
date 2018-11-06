# Installation

- Install xtensor
	- `conda install xtensor`
 	- optionally, for simple plotting from C++, install `xtensor-io` as well
- Build: `g++ main.cpp -O3 -march=native -o main` (optionally add `-lOpenImageIO` for plotting!)
- Run: `./main` if plotting is enabled, a `shaded.png` file will appear in the folder