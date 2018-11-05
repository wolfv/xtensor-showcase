# Installation

- Install CxxWrap.jl in Julia:
	- Press `]` to enter the Pkg mode, then type "add CxxWrap"
- Install C++ dependencies: libcxxwrap-julia, xtensor, xtensor-julia with 
  `git clone ...; mkdir build; cd build; cmake ..; sudo make install` for each of
	- https://github.com/JuliaInterop/libcxxwrap-julia
	- https://github.com/QuantStack/xtensor
	- https://github.com/QuantStack/xtensor-julia
- Build (note: you can use the julia-config.jl to get the appropriate flags),
  e.g. `/usr/share/julia/julia-config.jl --allflags`

```
g++ -I/usr/include/julia/ -shared  -Wl,--export-dynamic
    -ljulia -lcxxwrap_julia 
    -fPIC
	-DJULIA_ENABLE_THREADING=1
	bindings.cpp  -o bindings.so
```
