Rcpp::sourceCpp("bindings.cpp");
volcano <- as.matrix(read.csv("../assets/volcano.csv", colClasses="numeric"))
shaded <- rayshade(volcano)

X11()
image(shaded)

message("Press [Enter] To Continue")
invisible(readLines("stdin", n=1))
