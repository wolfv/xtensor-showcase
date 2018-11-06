#include "rayshade.hpp"
#include <xtensor/xcsv.hpp>
#include <istream>

#if __has_include(<xtensor-io/ximage.hpp>)
	#include <xtensor-io/ximage.hpp>
	#pragma message("Cool you have xtensor-io, don't forget to link -l OpenImageIO for the plot!")
	#define DO_PLOT
#endif

int main()
{
	std::ifstream in_file;
	in_file.open("../assets/volcano.csv");
	auto volcano = xt::load_csv<float>(in_file);
    std::cout << volcano << std::endl;

    auto result = rayshade_impl(volcano);

    std::cout << result << std::endl;

#ifdef DO_PLOT
    xt::xarray<uint8_t> image_result = xt::cast<uint8_t>(result * 255);
    xt::dump_image("shaded.png", image_result);
#endif

    return 0;
}