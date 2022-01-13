#include <vector>
#include <chrono>
#include <cmath>
#include <range/v3/algorithm/partition.hpp>
#include <range/v3/view/subrange.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/generate_n.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/algorithm/shuffle.hpp>
#include <range/v3/action/shuffle.hpp>
#include <range/v3/algorithm/min_element.hpp>
#include <fmt/format.h>

using namespace std;
namespace rn = ::ranges;
namespace ra = rn::actions;
namespace rv = rn::views;

struct Point {
    double x,y,z;
};

struct Character {
    string name;
    Point punto;
};

auto main () -> int{
    auto heroes = vector< string > {"Chewbacca","Han Solo","Leia Organa","Luke Skywalker","Obi-Wan Kenobi","R2-D2","Yoda" };
    auto villains = vector< string > {"Conde Dooku","Darth Maul","Darth Vader","Jabba el Hutt","Jango Fett","Grand Moff Tarkin","Palpatine" }; 

    auto gen = mt19937{};
    
    gen.seed(chrono::steady_clock::now().time_since_epoch().count());
    rn::shuffle(heroes,gen);
    
    auto dist_xyz = uniform_real_distribution(-25.0,25.0);
    auto rand = bind(dist_xyz,gen);

    auto const allies = (heroes |= ra::shuffle(gen))
                                | rv::take(3)
                                | rv::transform([&](string n){return Character{n,Point{rand(),rand(),rand()}};})
                                | rn::to<vector>;
    auto const enemies = (villains |= ra::shuffle(gen))
                                   | rv::take(3)
                                   | rv::transform([&](string n){return Character{n,Point{rand(),rand(),rand()}};})
                                   | rn::to<vector>;
                                
    auto distance = [](Character const& c1, Character const& c2){
        return sqrt(pow(c1.punto.x - c2.punto.x,2)+pow(c1.punto.y - c2.punto.y,2)+pow(c1.punto.z - c2.punto.z,2));
    };
    /*
    for(Character const& a : allies){
        auto min_dist = double{1000.0};
        auto c = Character{};
        for(Character const& e : enemies){
            auto d = distance(a,e);
            if(d < min_dist){
                min_dist = d;
                c = e;
            }
        }
        fmt::print("{} vs {}\n",a.name,c.name);
    }
    */

   for(Character const& a : allies){
        auto comp = [&](Character e1,Character e2) -> bool {
            return distance(e1, a) < distance(e2, a);
        };
        auto iter = rn::min_element(enemies, comp);
        fmt::print("{} vs {}\n",a.name,iter->name);
   }
}