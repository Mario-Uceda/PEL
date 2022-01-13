#include <string>
#include <fmt/format.h>
#include <vector>
#include <iostream>
#include <array>
#include <range/v3/action/sort.hpp>

using namespace std;
namespace rn = ::ranges;
namespace ra= ::rn::actions;

template<typename T> // T es el tipo de dato contenido
class Vector {
    T* v_;     //Puntero al primer elemento del vector
    T* space_; //Puntero al primer hueco libre en la capacidad adicional del vector
    T* last_;  //Puntero a un hipotético hueco uno pasado el último de los huecos 
public:
    Vector() //constructor que genera un vector vacío
        : v_{new T[0]}, space_{v_}, last_{v_}  { }

    ~Vector() { delete[] v_ ;} //destructor

    //capacidad
    auto size() const -> size_t {return space_ - v_; } //devuelve cuantos elemento hay en el vector
    auto capacity() const -> size_t {return last_ - v_; } //devuelve cuantos espacios se han reservado para elementos 
    auto empty() const -> bool {return v_ == space_; } // devuelve si no hay elementos en el vector

    //introducción de datos
    void push_back(T val) {
        if(space_==last_){ //capacidad del vector agotada o llamada por primera vez
            size_t old_capacity = capacity(); //capacidad actual del vector
            size_t new_capacity = (old_capacity == 0)? 2 : 2*old_capacity;
            //reservamos un bloque de memoria con capacidad igual a new_capacity
            T* new_block = new T[new_capacity];
            try{
                for(auto i = size_t{0};i<old_capacity;++i){ //copiamos los datos del vector original
                    new_block[i]=v_[i];                    
                }
                //guardamos el nuevo elemento
                new_block[old_capacity]=val;
            }catch(...){
                delete[] new_block;
                throw;
            }
            delete[] v_;
            v_ = new_block;
            space_ = new_block + old_capacity + 1;
            last_ = new_block + new_capacity;


        }else{
            *space_ = val; //desrreferencio space_ y lo igualo a val
            ++space_;
        }
    }

    //Funciones de acceso
    auto begin() ->T* {return v_;}
    auto end ()  ->T* {return space_;}
    auto begin() const ->T const* {return v_;}
    auto end ()  const ->T const* {return space_;}

    auto operator[](int indice) -> T& {return v_[indice]; }
    auto operator[](int indice) const -> T const& {return v_[indice]; }

};


struct Student {
    string name;
    array <double,3> grades;
    auto average() const -> double {return (grades[0] + grades[1] + grades[2])/3.0;}
};

auto main() -> int
{
    auto students = Vector<Student>{};
    auto message = [] {fmt::print("Name:"); return true;};
    auto aux = Student{};
    while (message and getline(cin, aux.name)){
        for (
            auto i = 0; 
            auto& grd : aux.grades){
            fmt::print("grade {}: ", ++i);
            (cin >> grd).ignore();
        }
        students.push_back(aux);
        fmt::print("Name:");
    }
    cin.clear();

    for (auto i = size_t{0};i < students.size();++i)
        fmt::print("nombre de {}: {:.2f}\n",students[i].name);

    for (auto const& s : (students |= ra::sort(rn::less{}, &Student::name)))
        fmt::print("media de {}: {:.2f}\n",s.name,s.average());
    

}
