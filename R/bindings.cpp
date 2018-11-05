#include "../cpp/rayshade.hpp"
#include <numeric>                    // Standard library import for std::accumulate
#include <xtensor-r/rarray.hpp>       // R bindings

#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::plugins(cpp14)]]

// [[Rcpp::export]]
auto rayshade(xt::rarray<double>& heightmap)
{
	return rayshade_impl(heightmap);
}