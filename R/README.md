# Installation & building

- Install RCpp from CRAN
- Install xtensor, and xtensor-r:
	- https://github.com/QuantStack/xtensor
	- https://github.com/QuantStack/xtensor-r
- Either compile, or use Rcpp helper functions:
	- Rcpp::sourceCpp("bindings.cpp")
	- Note: I had to create the file ~/.R/Makevars with this content:
		```
		CPPFLAGS=-O3 -march=native
		```
	  For some reason, setting this value with `Sys.setenv(CPPFLAGS="-O3 -march=native")`
	  had no effect in the `Rscript` environment.
- Use the rayshade function!
