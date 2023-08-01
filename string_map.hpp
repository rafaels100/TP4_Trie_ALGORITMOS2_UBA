template <typename T>
string_map<T>::string_map(){
    // COMPLETAR
    //inicialmente la raiz apunta al nullptr
    raiz = nullptr;
    //y tenemos 0 definiciones
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
    if (d.raiz == nullptr) {
        //si el trie del que quiero copiar esta vacio, inicializo el trie copia
        //normalmente
        raiz = nullptr;
        //y tenemos 0 definiciones
        _size = 0;
        return *this;
    }
    if(raiz == nullptr){
        //si el trie sobre el que voy a copiar los elementos del
        //trie aCopiar esta vacio, simplemente creo nuevos nodos para este trie
        raiz = new Nodo();
        copiarNodos(raiz, d.raiz);
    }else{
        //si no esta vacio, debo asegurarme de eliminar todos los nodos que puede
        //llegar a tener mi trie, que le quiero asignar los nodos de aCopiar.
        //Para ello me ayudo del ayudante del destructor
        destr_rec(raiz);
        //ahora el trie quedo vacio, y todos los nodos 'interiores' fueron liberados
        //sin embargo, la raiz sigue estando reservada para mi, aun no la libere.
        //Me quedo con la raiz, pues esta vacia, y me corresponde volver a llenarla
        //con la informacion de aCopiar
        copiarNodos(raiz, d.raiz);
    }
    return *this;
}

template <typename T>
void string_map<T>::copiarNodos(Nodo* nodo_c, const Nodo* nodo_o){
    //si el nodo original esta definido, debo crear una nueva
    //variable en el heap para esa definicion en el nodo copia

    if (nodo_o->definicion != nullptr) {
        //creo una nueva variable en el heap con el contenido de la clave original
        nodo_c->definicion = new T(*(nodo_o->definicion));
        //sumo una nueva definicion al trie copia
        _size++;
    }


    for(int i = 0; i < NUM_CHARS; i++){
        if((nodo_o->siguientes)[i]){
            //significa que hay algo que debo copiar en mi nodo copia
            //creo un nuevo nodo y apunto a esa direccion de memoria en mi nodo copia,
            //en la iesima posicion
            (nodo_c->siguientes)[i] = new Nodo();
            //entro por este camino en el nodo original recursivamente, llevando
            //tambien al nuevo nodo que acabo de crear en el nodo copia, cosa de que si
            //encuentro algo llendo por el camino i en el nodo original, pueda guardarlo
            //en el camino i del nodo copia
            copiarNodos((nodo_c->siguientes)[i], (nodo_o->siguientes)[i]);
        }
    }
    return;
}

template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
    if (raiz == nullptr){
        return;
    }else{
        destr_rec(raiz);
        delete raiz;
        raiz = nullptr; //no es necesario, pero por buenas costumbres
    }
}

template <typename T>
void string_map<T>::destr_rec(Nodo* nodo){
    //si encuentro un nodo terminal, disminuyo en 1 la cantidad de nodos terminales
    if (nodo->definicion){
        _size--;
    }
    for(int i = 0; i < NUM_CHARS; i++){
        if (nodo->siguientes[i]){
            destr_rec(nodo->siguientes[i]);
            //libero la definicion del heap
            delete nodo->siguientes[i]->definicion;
            //la apunto al null, pues ya no tengo permiso para acceder a esa direccion de memoria
            nodo->siguientes[i]->definicion = nullptr;
            //libero ahora al vector de siguientes en el heap
            delete nodo->siguientes[i];
            //apunto al null, pues ya no tengo permiso para acceder a esa direccion de memoria
            nodo->siguientes[i] = nullptr;
        }
    }
    return;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    // COMPLETAR
    if (raiz == nullptr){
        //si el trie esta vacio, no vamos a encontrar nada
        return 0;
    }
    int length = clave.length();
    Nodo* tmp = raiz;
    //busco letra por letra, a ver si el camino a esa palabra esta definido
    for(int i = 0; i < length; i++){
        //si ocurre que uno de los caminos no esta definido, ya puedo decir que esa
        //palabra no forma parte de mi trie
        if(tmp->siguientes[clave[i]] == nullptr){
            return 0; //devuelvo false
        }
        //si si existe el camino, sigo el camino de ese puntero
        tmp = tmp->siguientes[clave[i]];
        //y continuo buscando la siguiente letra por este nuevo array de punteros
    }
    //si todos los caminos estaban definidos, me fijo si este prefijo es terminal
    //en caso de serlo, esa palabra esta en mi trie. En caso de que no, significa
    //que si bien el prefijo esta, la palabra no, pues es necesaria para construir
    //otras palabras que si estan en mi trie.
    //Ej: Busco cocina, pero la palabra que esta es cocinar. Es decir, el prefijo
    //cocina existe en mi trie, pero no es terminal, por lo que dicha palabra no esta

    return bool(tmp->definicion);
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR

    /*
    if(not count(clave)){
        cout << "Se ingreso una clave no valida. Terminando programa" << endl;
        //exit(0);
        return ;
    }
     */

    //es basicamente el buscar, pero ahora sabemos que va a encontrar algo, y en vez de
    //devolver 1, devolvemos lo que sea que haya en ese significado
    //int length = strlen(clave.c_str()); //es necesario convertir la string a const char*
    int length = clave.length();
    Nodo* tmp = raiz;
    //busco letra por letra, a ver si el camino a esa palabra esta definido
    for(int i = 0; i < length; i++){
        //si ocurre que uno de los caminos no esta definido, ya puedo decir que esa
        //palabra no forma parte de mi trie

        /*
        if(tmp->siguientes[clave[i]] == nullptr){
          return nullptr; //no lo encontro
          ESTO NO FUNCIONA porque debo devolver un T, y sale por referencia
        }
        */

        //si si existe el camino, sigo el camino de ese puntero
        tmp = tmp->siguientes[clave[i]];
        //y continuo buscando la siguiente letra por este nuevo array de punteros
    }
    //si todos los caminos estaban definidos, me fijo si este prefijo es terminal
    //en caso de serlo, esa palabra esta en mi trie. En caso de que no, significa
    //que si bien el prefijo esta, la palabra no, pues es necesaria para construir
    //otras palabras que si estan en mi trie.
    //Ej: Busco cocina, pero la palabra que esta es cocinar. Es decir, el prefijo
    //cocina existe en mi trie, pero no es terminal, por lo que dicha palabra no esta
    return *(tmp->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR

    /*
    if(not count(clave)){
        cout << "Se ingreso una clave no valida. Terminando programa" << endl;
        //exit(0);
        return nullptr;
    }
     */

    //es basicamente el buscar, pero ahora sabemos que va a encontrar algo, y en vez de
    //devolver 1, devolvemos lo que sea que haya en ese significado
    //int length = strlen(clave.c_str()); //es necesario convertir la string a const char*
    int length = clave.length();
    Nodo* tmp = raiz;
    //busco letra por letra, a ver si el camino a esa palabra esta definido
    for(int i = 0; i < length; i++){
        //si ocurre que uno de los caminos no esta definido, ya puedo decir que esa
        //palabra no forma parte de mi trie

        /*
        if(tmp->siguientes[clave[i]] == nullptr){
          return nullptr; //no lo encontro
          ESTO NO FUNCIONA porque debo devolver un T, y sale por referencia
        }
        */

        //si si existe el camino, sigo el camino de ese puntero
        tmp = tmp->siguientes[clave[i]];
        //y continuo buscando la siguiente letra por este nuevo array de punteros
    }
    //si todos los caminos estaban definidos, me fijo si este prefijo es terminal
    //en caso de serlo, esa palabra esta en mi trie. En caso de que no, significa
    //que si bien el prefijo esta, la palabra no, pues es necesaria para construir
    //otras palabras que si estan en mi trie.
    //Ej: Busco cocina, pero la palabra que esta es cocinar. Es decir, el prefijo
    //cocina existe en mi trie, pero no es terminal, por lo que dicha palabra no esta
    return *(tmp->definicion);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& par){
    // COMPLETAR
    if(raiz == nullptr){
        //creo un nuevo nodo que sera la raiz
        raiz = new Nodo();
        //inserto usando la funcion auxiliar
        insert_aux(raiz, par.first, par.second);
    }else{
        //inserto a partir de la raiz
        insert_aux(raiz, par.first, par.second);
    }
}

template <typename T>
void string_map<T>::insert_aux(Nodo* raiz, const string& clave, const T& significado){
    /*
    segun Mateo, es necesario que el significado este en el heap. Cuando hicimos el vector, para
    crear cosas nuevas en el heap dinamicamente solo creabamos un nodo que iba a tener un valor asociado.
    Ahora tenemos dos 'objetos' en el nodo: el vector de caminos y el propio signficado. Si cambiamos uno,
    el otro puede no verse afectado, por eso necesitamos que vivan en lugares separados en el heap.
    T* def = new T(significado);
    raiz->definicion = def;
    */

    /*
    Asi seria trabajando con cosas del stack
    T def = T(significado); //creo en el stack
    raiz->definicion = &def; //me guardo la direccion a esa variable estatica
    */
    //cout << "clave: " << clave << " significado: " << *(raiz->definicion) << endl;

    //creo una variable auxiliar para ir recorriendo los nodos
    Nodo* tmp = raiz;

    int largo_str = clave.size();
    for(int i = 0; i < largo_str; i++){
        if ((tmp->siguientes)[clave[i]] == nullptr) {
            //si no esta definido el camino para esta letra, creo un nuevo nodo que lo contemple
            (tmp->siguientes)[clave[i]] = new Nodo();
            //cout << "entro y creo un nodo a " << clave[i] << typeid(clave[i]).name() << endl;
        }
        //ya sea que el camino estaba creado o no, ahora estamos seguros que si lo esta.
        //cambio la raiz para mirar en los siguientes posibles caminos, recien
        //creados (vacios) o no, siguiendo el camino de la iesima letra en el texto
        tmp = (tmp->siguientes)[clave[i]];

    }
    if (tmp->definicion != nullptr){
        //si la palabra ya estaba en el trie, llegamos a un nodo terminal con algo definido.
        //no insertamos nada, pues la palabra ya estaba alli.
        cout << "Esta clave ya esta definida. Hay que cambiar el significado" << endl;
        *(tmp->definicion) = significado;
        return;
    }else{
        //si el nodo terminal tenia false, significa que nunca antes habiamos llegado a
        //dicho nodo por el camino indicado por la string. Definimos
        T* def = new T(significado);
        tmp->definicion = def;
        //aumentamos la cantidad de palabras definidas en el trie
        _size++;
        return;
    }
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
    //si el trie esta vacio, no hay nada que borrar. No hacemos nada y salimos con false
    if (raiz == nullptr) {
        cout << "Trie vacio" << endl;
        return;
    }

    //si hay algo en el arbol, ahora queremos cambiar, de ser necesario, a que nodo
    //apunta la raiz del trie
    //convierto a la string a array de caracteres, para manejar mas alegremente los punteros
    char arr[clave.length() + 1];
    strcpy(arr, clave.c_str());
    raiz = erase_rec(raiz, arr, false);
    //el resultado del exito o no del borrado surge de las operaciones en deletestr_rec
    return;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::erase_rec(Nodo* nodo, char* text, bool deleted){
    //si el nodo apunta al null, llegue al caso base, devuelvo al puntero como esta
    if (nodo == nullptr) return nodo;
    //como voy 'mirando hacia adelante' en el texto (mas adelante lo paso como +1),
    //para ver si el nodo es terminal en cierta letra, debo desreferenciar  moviendo
    //el puntero hacia atrars con un -1
    //cout << *(text-1) << " " << node->terminal << endl;
    //si al acceder al texto veo que hay un 0 (el fin de una cadena de texto),
    //significa que ya me movi lo suficiente a traves de la cadena de texto
    //como para llegar al final de la misma
    if(*text == '\0'){
        //si el nodo al que llego es terminal, significa que la palabra esta en mi trie
        if (nodo->definicion){
            //cambio el nodo y ahora ya no es terminal, eliminando efectivamente la
            //palabra del trie
            //debo liberar ese espacio de memoria
            delete nodo->definicion;
            //y luego apuntar al null, pues ya no tengo derecho a ese espacio de memoria
            nodo->definicion = nullptr;
            //llevo registro de que el borrado fue exitoso
            deleted = true;
            //disminuyo en 1 la cantidad de definiciones en el trie
            _size--;
            //si el nodo terminal no tiene hijos
            if(node_has_children(nodo) == false){
                //puedo liberarlo, pues significa que no era continuacion de otras palabras
                delete nodo;
                //ahora apunta al null, no mas a este espacio de memoria que acabo de liberar
                nodo = nullptr;
            }
        }
        //devuelvo el puntero a nodo, ya sea que solo modifique el bool del terminal,
        //o que directamente elimine el nodo pues no solo era terminal sino que no tenia
        //hijos
        return nodo;
    }
    //accedo al primer elemento del array de caracteres que es texto.
    //seteo al puntero a nodo correspondiente a esa letra en mi arrays de hijos,
    //llamando recursivamente a la funcion

    //al hacer texto+1, estoy moviendo el puntero del array de caracteres en un byte
    //hacia la derecha, por lo que ahora el comienzo de la string va a estar corrido,
    //por eso puedo acceder a la nueva letra a buscar con el text[0], cada vez
    //que entro a la funcion recursivamente
    (nodo->siguientes)[text[0]] = erase_rec(nodo->siguientes[text[0]], text+1, deleted);
    //modifico el puntero a nodo en el lugar de la letra actual, haciendo que o bien ahora
    //no sea terminal, o bien directamente apunte al null, o dejandolo como esta, si resulta
    //que era parte del camino para llegar a una palabra usada.

    //si el borrado fue exitoso y encuentro que uno de los nodos de la recursion no tiene hijos
    //y que no es nodo terminal, entonces no aporta nada a mi trie, quedo desfasado. Debo
    //liberar esa direccion de memoria y apuntar ese puntero al null
    if (deleted && node_has_children(nodo) == false && nodo->definicion) {
        delete nodo;
        nodo = nullptr;
    }
    return nodo;
}

template <typename T>
bool string_map<T>::node_has_children(Nodo* nodo){
    if(nodo == nullptr) return false;

    for(int i = 0; i < NUM_CHARS; i++){
        if((nodo->siguientes)[i] != nullptr){
            return true;
        }
    }
    return false;
}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
    return (_size == 0);
}