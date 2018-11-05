#include <jlcxx/jlcxx.hpp>
#include <xtensor-julia/jlarray.hpp>

#include "../cpp/rayshade.hpp"

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
    mod.method("rayshade", [](const xt::jlarray<float>& arr) { return rayshade_impl(arr); });
}