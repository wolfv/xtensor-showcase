#include <jlcxx/jlcxx.hpp>
#include "/home/wolfv/Programs/xtensor-julia/include/xtensor-julia/jlarray.hpp"
#include "/home/wolfv/Programs/xtensor-julia/include/xtensor-julia/jltensor.hpp"

#include "../cpp/rayshade.hpp"

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
    mod.method("rayshade", [](xt::jltensor<float, 2> arr) {
    	return rayshade_impl(arr);
    });
}