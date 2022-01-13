#include <iostream>
#include <fmt/format.h>
#include <vector>
#include <string>
#include <range/v3/algorithm/stable_partition.hpp>
#include <range/v3/algorithm/find.hpp> 
#include <range/v3/view/subrange.hpp>

using namespace std;
namespace rn = ::ranges;
namespace ra = rn::actions;
namespace rv = rn::views;

struct Album
{
    string title,band,genre;
};

auto main() -> int 
{
    auto albums = vector<Album> {
        {"the dark side of the moon", "pink floyd", "rock"},
        {"tubular bells","mike oldfield","new age"},
        {"ok computer","radiohead","rock"},
        {"the magnificent tree","hooverphonic","pop"},
        {"favourite worst nightmare","arctic monkeys","rock"},
        {"the four seasons","vivaldi","classical"},
        {"parachutes","coldplay","pop"},
        {"the suburbs","arcade fire","rock"},
        {"gran turismo","the cardigans","pop"}
    };
    fmt::print("Introduce el titulo del album que deseas buscar: ");
    auto title_to_search = string {};
    getline(cin, title_to_search);

    auto const iter = rn::find(albums, title_to_search, &Album::title);
    if (iter != albums.end()){
        auto const& found_genre = iter->genre;
        auto same_genre = [&](Album const& a) {return a.genre == found_genre;};

        rn::stable_partition(iter +1, albums.end(),same_genre);
        rn::stable_partition(albums.begin(),iter, not_fn(same_genre));

        for (Album const& a : albums){
            fmt::print("{:>25}, by {:>15} | {}\n",a.title,a.band,a.genre);
        }

    }{
        fmt::print("El titulo del album que no se ha encontrado"); 
    }
}
