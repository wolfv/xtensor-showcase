# Building

- Install pybind11 (e.g. using conda, pip or CMake) https://github.com/pybind/pybind11)
- Install xtensor and xtensor-python
	- https://github.com/QuantStack/xtensor
	- https://github.com/QuantStack/xtensor-python
- Compile using the following snippet:

```
g++ -I/usr/include/python3.7m/ `python3-config --ldflags` -shared -fPIC bindings.cpp -o rayshade.so
```

- Run example file: