#include <fstream>
#include <fmt/format.h>
#include <vector>
#include <map>
#include <cctype>
#include <regex>
#include <range/v3/action/transform.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/view/tokenize.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/group_by.hpp>
#include <range/v3/range/conversion.hpp> // rn::to para materializar vistas en contenedores

using namespace std;
namespace rn = ::ranges;
namespace rv = rn::view;
namespace ra = rn::action;

[[nodiscard]] auto file_to_string(char const *filename) -> string
{
   auto in = ifstream{};
   in.exceptions(ifstream::failbit | ifstream::badbit);
   in.open(filename, ios::binary);

   auto contents = string{};
   in.seekg(0, ios::end);
   if (auto const sz = streamoff{in.tellg()}; sz > 0)
   {                       // sz es entero con signo
      contents.resize(sz); // bloque de memoria contigua desde C++11
      in.seekg(0, ios::beg);
      in.read(&contents[0], sz);
   }
   return contents;
}

auto main() -> int
{
   auto const freq_tokens_map = [] {
      auto const text = file_to_string("C:/Users/Mario/Documents/Universidad/2/PEL/Workspace/Recursos_Ejercicios/Ejercicio3/ulysses.txt") | ra::transform(::tolower);
      auto tokens = text | rv::tokenize(regex{R"([\w]+)"}) | rn::to<vector<string>>;
      // creamos un mapa que asocia a cada frecuendcia de uso, el listado de palabras asociadas
      auto res = map<int, vector<string>, rn::greater>{};
      // Predicado binario -> función para el group by
      auto same_word = [](string s1, string s2) { return s1 == s2;};
      for (auto grp : (tokens |= ra::sort) | rv::group_by(same_word))
      {
         res[rn::distance(grp)].push_back(*grp.begin());
      }
      return res;
   }();

   for (auto [freq, tokens] : freq_tokens_map | rv::take(5))
   {
      fmt::print("Frecuencia: {}___________\n", freq);
      for (string tk : tokens)
      {
         fmt::print("{} ", tk);
      }
      fmt::print("\n");
   }

   auto ofs = ofstream{"C:/Users/Mario/Documents/Universidad/2/PEL/Workspace/Recursos_Ejercicios/Ejercicio3/data_2.csv",ios::binary};
   auto rank = int{0};
   for (auto const& [freq,tokens] : freq_tokens_map){
      for (string const& tk : tokens){
         fmt::print(tk);
         ofs << ++rank << ',' << freq << '\n';
      }
   }
}
