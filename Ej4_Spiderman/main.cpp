#include <iostream>
#include <fmt/format.h>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/view/subrange.hpp>
#include <range/v3/view/generate_n.hpp>
#include <range/v3/range/conversion.hpp>


using namespace std;
namespace rn = ::ranges;
namespace ra = rn::actions;
namespace rv = rn::views;

struct Point {
    double x,y,z;
};

struct Sable_guard {
    Point location;
    bool alert, attack;
};

auto euclidean_distance(Point const& p) ->double {
    return sqrt(p.x*p.x + p.y*p.y + p.z*p.z); 
}

auto guards_generator(int vector_size) -> vector<Sable_guard>{
    auto gen = mt19937{}; //algoritmo del generador Mersenne twister
    gen.seed(chrono::steady_clock::now().time_since_epoch().count()); //semilla
    auto distr = uniform_real_distribution{-15.0,15.0}; // el cubo es de 30x30 y spiderman está en el 00

    auto rand = bind(distr,gen);

    auto random_sable_generator = [&] {
        auto random_coordinate = Point{rand(),rand(),rand()};
        return Sable_guard{
            .location = random_coordinate, // double aleatorio
            .alert    = euclidean_distance(random_coordinate) < 10,
            .attack   = euclidean_distance(random_coordinate) <5
        };
    };

    return rv::generate_n(random_sable_generator, vector_size) | rn::to<vector>;
}

auto main() -> int 
{
    auto n_guardias=25;
    auto guards = guards_generator(n_guardias);

    auto alert_it = rn::partition(guards, &Sable_guard::alert);
    auto attack_it = rn::partition(guards.begin(),alert_it, &Sable_guard::attack);

    fmt::print("\n {:_^22}\n","En ataque");
    for (Sable_guard const& sg : rn::subrange{guards.begin(),attack_it}){
        fmt::print("x: {:>5.2f}, y: {:>5.2f}, z: {:>5.2f} -> distance {:>5.2f}m\n", sg.location.x,sg.location.y,sg.location.z,euclidean_distance(sg.location));
    }
    fmt::print("\n {:_^22}\n","En alerta");
    for (Sable_guard const& sg : rn::subrange{attack_it,alert_it}){
        fmt::print("x: {:>5.2f}, y: {:>5.2f}, z: {:>5.2f} -> distance: {:.2f}m\n", sg.location.x,sg.location.y,sg.location.z,euclidean_distance(sg.location));
    }

}
