#include <cassert>
#include <fmt/format.h>
#include <string>
#include <concepts>

template<typename T>
    requires std::floating_point<T>
class Rectangle{
    T height_, width_;
public:
    explicit Rectangle(T height =T{},T width=T{}) 
        :height_{height}, width_{width} //lista de inicializadores
        // precondición: height > 0.0 , width > 0.0
    {
        assert(height_ > 0.0 and width_ > 0.0);
    }    
    auto heigth() const -> T { return height_;}
    void height (T new_height) { height_ = new_height; }
    auto width() const -> T { return width_;}
    void width(T new_width) { width_ = new_width; }

    auto area() const -> T { return height_*width_; }
};

struct Student{
    std::string name;
    double grade_1,grade_2,grade_3;

    auto average() const -> double { return (grade_1+grade_2+grade_3)/3.0;}
};

struct Employee{
    std::string name;
    int id;
    Employee(std::string n = "", int i = 0)
        : name{n}, id{i}
    {
        // cuerpo de constructor
        fmt::print("construyendo a {}\n",name);
    }
    ~Employee() // destructor
    {
        fmt::print("destruyendo a {}\n",name);
    }
};

template<typename T>
class Dynarray {
    T* p_; // direccion en memoria del array de objetos tipo T
    std::size_t sz_; // tamaño del array de objetos de tipo T
public:
    Dynarray(std::size_t sz)
        : p_{new T[sz]}, sz_{sz}
    {

    }  

    auto operator[](std::size_t idx) -> T& {return *(p_ + idx);}
    auto size() -> std::size_t {return sz_;}

    auto begin() -> T* {return p_;}
    auto end()   -> T* {return (p_ + sz_);}

    ~Dynarray() {delete[] p_;}  
};

auto main() ->int 
{

/*  25/09/2020
    auto r = Rectangle<double,float,longdouble...>{2.0, 5.0};
    fmt::print("altura: {}, base: {}, area: {}",r.heigth(),r.width(),r.area());

    // punteros 

    // el puntero siempre ocupa 4 bytes en SO de 32bits 
    // el puntero siempre ocupa 8 bytes en SO de 64bits 

    auto i = int{0};
    int* p = &i; // el & antes de la variable i obtiene la direccion de memoria de i
    *p = 7; // para obtener el valor de la variable i usamos un * antes del puntero

    fmt::print("puntero p: {}\n",fmt::ptr(p));
    fmt::print("valor de i: {}",*p);

    auto s = Student{"Sarah Connor", 9.8,9.7,100};
    Student* p = &s; // puntero al estudiante s

    auto s = new Student{"Sarah Connor", 9.8,9.7,100};

    auto av = (*s).average(); // así funciona pero está anticuado
    av = s->average(); //actualmente se usa así
    fmt::print("Average: {}",av);
*/

/*  29/09/2020
    Employee* p = new Employee[3];
    
    (*p).name="paco";
    (*p).id=1;
    (*(p+1)).name="manolo";
    (*(p+1)).id=2;
    (*(p+2)).name="pepe";
    (*(p+2)).id=3;

    auto e1 = Employee{"A",1};
    auto e2 = Employee{"B",2};
    auto e3 = Employee{"C",3};

    delete[] p; // para eliminarlo manualmente, pero no se hace así

    for (auto i = std::size_t{0};i<p.size();++i){
        fmt::print("Nombre: {}, id: {}\n",p[i].name,p[i].id);
    }
*/
    
    auto p = Dynarray<Employee>{3};
    fmt::print("Constructor por defecto---------------------\n");
    p[0].name="nombre1";
    p[0].id=1;
    p[1].name="nombre2";
    p[1].id=2;
    p[2].name="nombre3";
    p[2].id=3;
    fmt::print("\n\n{}---------------------{}\n\n",p.begin()->name,1);

    fmt::print("Empezamos el bucle--------------------------\n");
    for (auto &emp : p ){ // si uso &emp uso una referencia al objeto guardado en memoria, sino creo una copia desde p y lo guardo en emp
        fmt::print("Nombre: {}, id: {}\n",emp.name,emp.id);
    }
    fmt::print("salimos del bucle---------------------------\n");
    
}