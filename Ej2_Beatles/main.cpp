#include <iostream>
#include <fmt/format.h>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <fstream>
#include <range/v3/view/getlines.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/algorithm/sort.hpp> // se usa cuando vas a ordenar una cosa en una line
#include <range/v3/action/sort.hpp> // se usa cuando has realizado varias cosas a la vez con |



using namespace std;
namespace rn = :: ranges;
namespace rv = rn::view;
namespace ra = rn::actions;


using nlohmann::json;

//serializa los datos de las bandas
void save_data(auto direccion)
{
    auto bands = map<string, vector<string>>{}; // MAPA inicialmente vacío
    // guardamos los datos en el mapa
    bands["The Beatles"]= {"Paul McCartney", "John Lennon", "Ringo Starr", "George Harrison"};
    bands["Pink Floyd"]= {"Nick Mason", "Syd Barrett", "Roger Waters", "Richard Wright", "David Gilmour", "Bob Klose"};
    bands["Arctic Monkeys"]= {"Alex Turner", "Matt Helders", "Jamie Cook", "Nick O'Malley", "Andy Nicholson", "Glyn Jones"};
    bands["Arcade Fire"]= {"Win Butler", "Regine Chassagne", "Richard Reed Parry", "Tim Kingsbury", "William Butler", "Jeremy Gara"};
    bands["Radiohead"]= {"Thom Yorke", "Jonny Greenwood", "Colin Greenwood", "Ed O'Brien", "Philip Selway"};
    auto ofs = ofstream{direccion, ios::binary};    // abrimos el flujo para guardar los datos en un fichero
    if(!ofs) throw ios_base::failure{"Unable to open the file"};    // comprobamos que el flujo se ha abierto
    for (auto const& [band, members]: bands){   //recorremos el mapa
        // los datos del nombre de la banda y los miembros los parseamos a un objeto json
        //Ese objeto lo mandamos al flujo y lo guarda en el fichero
        ofs << json {{"band",band},{"members",members}} << '\n';    // el '\n' lo usamos porque es un jsonl 
    }
}
//deserializa los datos de las bandas
auto read_data(auto direccion)
{
    auto ifs = ifstream{direccion, ios::binary};//abrimos el flujo para leer los datos
    if(!ifs) throw ios_base::failure{"Unable to open the file"};//comprobamos que el flujo está abierto
    return rn::getlines(ifs) //leo el fichero linea a linea
        | rv::transform([](string ln){ //casteamos la linea leida a json y devolvemos los dos valores
            auto j =json::parse(ln); //parseamos el string a json
            return pair<string,vector<string>>{j.at("band"),j.at("members")}; // devuelve los dos valores 
        })
        | rn::to<map>;//guardamos los valores en un mapa
    ;
}

auto main() -> int 
{
    auto direccion = string{"C:/Users/Mario/Documents/Universidad/2/Pel/Workspace/Recursos_Ejercicios/Ejercicio2/bandas.jsonl"};
    save_data(direccion);
    auto bands = read_data(direccion);
    
    fmt::print("Introduce el nombre de la banda que deseas buscar: "); 
    auto aux=string{};
    getline(cin,aux);

    auto it=bands.find(aux);
    if (it != bands.end()){
        for ( string const& member :bands[aux] |= ra::sort){
            fmt::print("{}\n",member);
        }  
    } else{
        fmt::print("no hemos encontrado la banda: {}\n", aux);
    }    


/*  Buscar una banda
    fmt::print("Introduce el nombre de la banda que deseas buscar: "); 
    auto aux=string{};
    getline(cin,aux);

    auto it=bands.find(aux);
    if (it != bands.end()){
        auto& [band_name,members] = *it;
        fmt::print("{:_^30}\n",band_name);
        rn::sort(members);
        for (auto const& member : members){
            fmt::print("{:^30}\n",member);
        }  
    }
    else{
        fmt::print("No hemos encontrado la banda");
    }

*/    
/*  Bucle que muestra todas las bandas y ordena alfabeticamente el nombre de los miembros
    for (auto& [band, members] : bands){ //structure binding
        fmt::print("{:_^30}\n",band);
        rn::sort(members);
        for (auto const& member : members){
            fmt::print("{:^30}\n",member);
        }  
        fmt::print("\n",band);  
    } 
*/    
}