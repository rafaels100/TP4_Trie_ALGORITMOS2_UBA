#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#define NUM_CHARS 256

#include <string>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        Nodo() : definicion(nullptr) {
            for (int i = 0; i < NUM_CHARS; i++) {
                siguientes.push_back(nullptr);
            }
        }
    };

    Nodo* raiz;
    int _size;

    //ayudante del insertar
    void insert_aux(Nodo* raiz, const string& clave, const T& significado);

    //copiar nodos
    void copiarNodos(Nodo* nodo_c, const Nodo* nodo_o);

    //ayudante del destructor
    void destr_rec(Nodo* nodo);

    //ayudante del erase
    Nodo* erase_rec(Nodo* nodo, char* text, bool deleted);
    bool node_has_children(Nodo* nodo);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
