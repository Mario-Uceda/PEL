#include <iostream>
#include <fmt/format.h>
#include <list>
#include <vector>
#include <string>

#include "terminal.hpp"


using namespace std;

struct Node_base {
    Node_base* prev; //Nodo previo
    Node_base* next; //Nodo proximo

    void hook(Node_base* p) noexcept{ //Ubicar este nodo antes de p
        this->prev = p->prev;
        this->next = p;
        p->prev->next = this;
        p->prev = this;
    };

    void unhook() noexcept{ //Desubicar este nodo
        this->prev->next = this->next;
        this->next->prev = this->prev;
        this->next = this;
        this->prev = this;
    };

    void swap(Node_base* p) noexcept{ //Cambiar orden de los dos nodos
        this->next = p->next;
        p->prev = this->prev;
        this->prev = p;
        p->next = this;
    };
};

template <typename T>
class List { //Lista doblemente enlazada
    
    struct Node : Node_base{
        T dat;
        Node(T data) : dat{data} {}
    };
    
    Node_base dnb_; // nodo base de control
    //dnb_.prev (nodo_base*) dirección en memoria del último nodo
    //dnb_.next (nodo_base*) dirección en memoria del primer nodo
        
    public:
        List() //Constructor por defecto: crea una lista inicialmente vacía
            : dnb_{&dnb_, &dnb_} { }
        
        ~List(){
            clear();
        }

        void push_back(T value) {
            Node* p = new Node (value);
            p->hook(&dnb_);
        }

        void clear(){
            Node_base* current = dnb_.next;
            while(current!=dnb_){
                auto temp = current;
                current= current->next;
                delete static_cast<Node*>(temp);
            }
            dnb_.hook(&dnb_);
        }
        
        auto const size () -> size_t {
            Node_base* current = dnb_.next;
            auto contador = 0;
            while(current!=dnb_){
                current= current->next;
                ++contador;
            }
            return contador;
        }
};





auto main() -> int 
{
    auto lista = list<int>{1,2,3,4,5,6};
    lista.push_front(0);
    lista.push_back(7);
    auto iter = lista.begin();
    iter++;
    ++iter;
    lista.insert(iter,7);
    for(auto const n : lista){
        fmt::print("{}\n",n);
    }
}
