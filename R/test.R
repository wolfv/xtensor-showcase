Rcpp::sourceCpp("bindings.cpp");

volcano <- as.matrix(read.csv("../assets/volcano.csv"))
shaded <- rayshade(volcano)

heatmap(shaded)