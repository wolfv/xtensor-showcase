#include <pybind11/pybind11.h>
#define FORCE_IMPORT_ARRAY
#include <xtensor-python/pyarray.hpp>
#include "../cpp/rayshade.hpp"

PYBIND11_MODULE(rayshade, m) {
    xt::import_numpy();

    m.doc() = "Shade some rays in Python!";
    m.def("rayshade", [](const xt::pyarray<float, xt::layout_type::row_major>& arr) { return rayshade_impl(arr); } );
}