#include <cmath>
#include <vector>
#include <fmt/format.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>
#include <range/v3/view/linear_distribute.hpp>
#include <thread>

namespace rv = ::ranges::views;
using namespace std::chrono_literals;
auto main() -> int
{
    using Vec = dlib::vector<double,3>; // el 3 indica el número de dimensiones 3 = x y z ; 2 = x y
/* Ejemplo vector de dlib
    auto v1 = Vec{1.0,2.0,3.0};
    auto v2 = Vec{5.0,6.0,-1.0};
    auto v3 = v1+v2;
    fmt::print("{},{},{}",v3.x(),v3.y(),v3.z());
*/

    auto dots = std::vector<dlib::perspective_window::overlay_dot>{}; //vector de puntos

    auto win = dlib::perspective_window{};
    win.set_title("helice 3D");
    win.set_size(700,700);
    win.set_pos(0,0);

    auto const t_min = 0.0,
               t_max = 5.0;
    auto rng = dlib::rand{};
    for (auto const t : rv::linear_distribute(t_min,t_max, 10'000)){
        auto p = Vec{std::sin(4*t) , std::cos(4*t) , t};
        p+= Vec{rng.get_random_gaussian(),
                rng.get_random_gaussian(),
                rng.get_random_gaussian()} / 10; //Dispersión
        auto const color = dlib::colormap_jet(t,t_min,t_max);
        dots.emplace_back(p,color);
        std::this_thread::sleep_for(1us);
        win.add_overlay(std::vector{dlib::perspective_window::overlay_dot{p,color}});
    }

    win.wait_until_closed();

}
