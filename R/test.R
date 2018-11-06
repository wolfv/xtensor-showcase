Rcpp::sourceCpp("bindings.cpp", cacheDir="__rcpp_cache__", verbose = TRUE);
volcano <- as.matrix(read.csv("../assets/volcano.csv", colClasses="numeric"))
shaded <- rayshade(volcano)

X11()
image(shaded)

message("Press [Enter] To Continue")
invisible(readLines("stdin", n=1))

library(tictoc)

tic("C++")
result <- rayshade(volcano)
toc()

source("r_impl.R")
source("r_impl_naive.R")

tic("R fast shade")
result <- ray_shade3(volcano)
toc()

tic("R slow shade")
result <- rayshade_slow(volcano)
toc()

library(rbenchmark)

benchmark("Vectorized R" = {
			result <- ray_shade3(volcano)
		  },
          "xtensor C++" = {
          	result <- rayshade(volcano)
          },
          replications = 50,
          columns = c("test", "elapsed", "relative", "user.self", "sys.self")
)


