#include <xtensor/xtensor.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor/xnpy.hpp>
#include <xtensor/xio.hpp>

template <class E>
auto bilinear_kernel(E& Z, float x0, float y0)
{
    std::size_t i = std::floor(x0), j = std::floor(y0);
    float XT = x0 - i, YT = y0 - j;
    float result = (1 - YT) * (1 - XT) * Z(i, j);
    std::size_t nx = Z.shape()[0], ny = Z.shape()[1];

    if (i + 1 < nx)
    {
        result = result + (1 - YT) * XT * Z(i + 1, j);
    }
    if (j + 1 < ny)
    {
        result = result + YT * (1 - XT) * Z(i, j + 1);
    }
    if (i + 1 < nx && j + 1 < ny)
    {
        result = result + YT * XT * Z(i + 1, j + 1);
    }
    return result;
}

template <class E>
auto rayshade_impl(const E& volcano)
{
    auto volcanoshadow = xt::ones_like(volcano);
    auto sunangle = 45. / 180. * xt::numeric_constants<double>::PI;
    auto angle = -90. / 180. * xt::numeric_constants<double>::PI;
    auto diffangle = 90. / 180. * xt::numeric_constants<double>::PI;
    auto nangles = 25;

    xt::xtensor<double, 1> anglebreaks = xt::tan(xt::linspace<double>(angle, diffangle, nangles));

    int64_t maxdistance = std::floor(std::sqrt(double(volcano.shape()[0] * volcano.shape()[0] +
                                                      volcano.shape()[1] * volcano.shape()[1]))) + 1;
    float sinsun = std::sin(sunangle), cossun = std::cos(sunangle);

    for (std::size_t i = 0; i < volcano.shape()[0]; ++i)
    {
        for (std::size_t j = 0; j < volcano.shape()[1]; ++j)
        {
            auto vij = volcano(i, j);
            for (auto& anglei : anglebreaks)
            {
                for (std::size_t k = 1; k < maxdistance; ++k)
                {
                    float xcoord = (i + sinsun * k);
                    float ycoord = (j + cossun * k);
                    if (xcoord >= volcano.shape()[0] - 1 or
                        ycoord >= volcano.shape()[1] - 1 or
                        xcoord < 0 or ycoord < 0)
                    {
                        break;
                    }
                    else
                    {
                        auto tanangheight = vij + anglei * k;
                        std::size_t cx = std::ceil(xcoord), cy = std::ceil(ycoord);
                        std::size_t fx = std::floor(xcoord), fy = std::floor(ycoord);

                        if (volcano(cx, cy) < tanangheight or
                            volcano(fx, cy) < tanangheight or 
                            volcano(cx, fy) < tanangheight or
                            volcano(fx, fy) < tanangheight)
                        {
                            continue;
                        }

                        if (tanangheight < bilinear_kernel(volcano, xcoord, ycoord))
                        {
                            volcanoshadow(i, j) -= 1.f / (float) nangles;
                            break;
                        }
                    }
                }
            }
        }
    }
    return volcanoshadow;
}
