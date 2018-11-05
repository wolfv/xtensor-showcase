#include <jlcxx/jlcxx.hpp>
#include "/home/wolfv/Programs/xtensor-julia/include/xtensor-julia/jlarray.hpp"

#include "../cpp/rayshade.hpp"

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
    mod.method("rayshade", [](xt::jlarray<float> arr) {
    	return rayshade_impl(arr);
    });
}