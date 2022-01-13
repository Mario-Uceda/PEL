#include <string>
#include <map>
#include <vector>
#include <regex>
#include <fstream>

#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <range/v3/view/getlines.hpp>
#include <range/v3/view/tokenize.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/numeric/accumulate.hpp>

using namespace std;
namespace rn = ::ranges;
namespace ra = rn::views;
namespace rv = rn::views;

struct Review
{
    string prod_id, text;
};

void from_json(nlohmann::json const& j,Review& r)
{
    j.at("asin").get_to(r.prod_id);
    j.at("reviewText").get_to(r.text);
}

auto main() -> int
{
    auto prod_lenghts_map = unordered_map<string, vector<double>>{};

    std::string fileURL = "c:/Users/Mario/Documents/Universidad/2/Pel/Workspace/amazon/amazon_automotive.jsonl";
    auto ifs = std::ifstream(fileURL, std::ios::binary); //flujo de entrada para leer el fichero json
    if (!ifs) throw std::ios_base::failure{"unable to open the file"}; //compruebo que el flujo está abierto y funciona

    for(string ln : rn::getlines(ifs)){
        auto review = nlohmann::json::parse(ln).get<Review>();
        auto tokens = review.text | rv::tokenize(regex{R"([\w]+)"})
                                  | rn::to<vector<string>>;
        prod_lenghts_map[review.prod_id].push_back(tokens.size()); 
    }
    auto prod_lenghts_media_map = unordered_map<string, double>{};
    for(auto const& [id,words] : prod_lenghts_map){
        prod_lenghts_media_map[id]=rn::accumulate(words,0.0) / words.size(); 
    }
    for (auto const& [id, media] : prod_lenghts_media_map | rv::take(5)){
        fmt::print("{} --> {}",id,media);
    }

    auto media_prodis_map = map<double, vector<string>, rn::greater>{};
    for (auto const& [id, media] : prod_lenghts_media_map){
        media_prodis_map[media].push_back(id);
    }

    for (auto const& [media, id] : media_prodis_map | rv::take(5)){
        fmt::print("{} --> {}",media);

    }
}
