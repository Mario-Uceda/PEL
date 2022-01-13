#include <vector>
#include <string>
#include <array>
#include <nlohmann/json.hpp>
#include <fstream>
#include <fmt/format.h>
#include <sstream>
#include <range/v3/view/getlines.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/algorithm/count_if.hpp>


using nlohmann::json;

namespace rn = ::ranges;
namespace ra = ranges::actions;
namespace rv = ranges::views;

struct Target {
    bool achieved;
    int level;
    std::array<double, 3> location;
    std::string name;
};

void from_json(json const& j,Target& t)
{
    j.at("achieved").get_to(t.achieved);
    j.at("level").get_to(t.level);
    j.at("location").get_to(t.location);
    j.at("name").get_to(t.name);
}

auto main() -> int {
    
    //vector donde guardaré los objetivos leidos desde el json
    auto targets = []{
        //Url donde guardo el fichero json
        std::string fileURL = "c:/Users/Mario/Documents/Universidad/2/Pel/Workspace/Recursos_Ejercicios/Ejercicio1/military_camp.jsonl";
        
        auto ifs = std::ifstream (fileURL,std::ios::binary); //flujo de entrada para leer el fichero json
        if(!ifs) throw std::ios_base::failure{"unable to open the file"}; //compruebo que el flujo está abierto y funciona
        
        return rn::getlines(ifs) 
             | rv::transform([](std::string In){return json::parse(In).get<Target>();})
             | rn::to<std::vector>;
    }();

    auto same_name = [](Target t1, Target t2){return t1.name == t2.name;};

    for(auto grp : (targets |= ra::sort(rn::less{}, &Target::name))
                            | rv::group_by(same_name)){
        auto type_name = grp.begin()->name;
        auto total = rn::distance(grp);
        auto done = rn::count_if(grp, &Target::achieved);
        fmt::print("\t-> logrado: {}, total: {}, nombre: {}\n",done,total,type_name);
    }

}