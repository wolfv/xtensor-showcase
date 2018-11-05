#include "../cpp/rayshade.hpp"
#include <numeric>                    // Standard library import for std::accumulate
#include <xtensor-r/rarray.hpp>       // R bindings

#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::plugins(cpp14)]]

// [[Rcpp::export]]
auto rayshade(const xt::rarray<double>& heightmap)
{
	std::cout << heightmap << std::endl;
	auto result = rayshade_impl(heightmap);
	std::cout << result << std::endl;
	return result;
}