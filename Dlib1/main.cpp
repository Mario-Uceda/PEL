#include <cmath>
#include <vector>
#include <fmt/format.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>
#include <range/v3/view/linear_distribute.hpp>
#include <thread>

namespace rv = ::ranges::views;

auto main() -> int
{
    using Vec = dlib::vector<double,3>;

    //construir la esfera
    auto sphere_dots = std::vector<dlib::perspective_window::overlay_dot>{}; //vector de los puntos de la esfera
    auto r_max = 6.0; // Radio máximo de la circunferencia
    auto rng = dlib::rand{}; //numero aleatorio para dispersion de los puntos

    for (auto const radios : rv::linear_distribute(0.0,r_max, 6)){
        for (auto const i : rv::linear_distribute(-r_max,r_max, 15)){
            for (auto const j : rv::linear_distribute(0.0,r_max, 500)){
                auto x=radios*std::cos(i)*std::sin(j);
                auto y=radios*std::sin(i)*std::sin(j);
                auto z=radios*std::cos(j);
                auto p = Vec{x,y,z};
                p+= Vec{rng.get_random_gaussian(),rng.get_random_gaussian(),rng.get_random_gaussian()} / 20; //Dispersión
                auto const color = dlib::colormap_jet(i,-r_max,r_max);
                sphere_dots.emplace_back(p,color);
            }    
        }
    }
    
/*    
    for (auto const r : rv::linear_distribute(-r_max,r_max, 1'000)){
        auto p = Vec{std::cos(4*r), std::sin(4*r), r};
        p+= Vec{rng.get_random_gaussian(),rng.get_random_gaussian(),rng.get_random_gaussian()} / 20; //Dispersión
        auto const color = dlib::colormap_jet(r,-r_max,r_max);
        sphere_dots.emplace_back(p,color);
    }
*/   
    //construir el cubo
    auto cube_dots = std::vector<dlib::perspective_window::overlay_dot>{}; //vector de los puntos del cubo
    
    for (auto const x : rv::linear_distribute(-r_max,r_max,1'000)){
        //lineas del eje x
        cube_dots.push_back(Vec{x,-r_max,-r_max});
        cube_dots.push_back(Vec{x,-r_max,r_max});
        cube_dots.push_back(Vec{x,r_max,-r_max});
        cube_dots.push_back(Vec{x,r_max,r_max});
        //lineas del eje y
        cube_dots.push_back(Vec{-r_max,x,-r_max});
        cube_dots.push_back(Vec{-r_max,x,r_max});
        cube_dots.push_back(Vec{r_max,x,-r_max});
        cube_dots.push_back(Vec{r_max,x,r_max});
        //lineas del eje z
        cube_dots.push_back(Vec{-r_max,-r_max,x});
        cube_dots.push_back(Vec{-r_max,r_max,x});
        cube_dots.push_back(Vec{r_max,-r_max,x});
        cube_dots.push_back(Vec{r_max,r_max,x});
    }

    //ventana 
    auto win = dlib::perspective_window{};
    win.set_title("esfera dentro de cubo");
    win.set_size(700,700);
    win.set_pos(0,0);
    win.add_overlay(cube_dots);
    win.add_overlay(sphere_dots);
    win.wait_until_closed();

}
