#include "rayshade.hpp"
#include <xtensor/xcsv.hpp>
#include <istream>

int main()
{
	std::ifstream in_file;
	in_file.open("../assets/volcano.csv");
	auto volcano = xt::load_csv<float>(in_file);
    std::cout << volcano << std::endl;

    auto result = rayshade_impl(volcano);

    std::cout << result << std::endl;
    return 0;
}