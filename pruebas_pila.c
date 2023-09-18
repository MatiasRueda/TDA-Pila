#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

//Verifico que la pila se halla creado correctamente
static void prueba_crear_pila(void) {
    pila_t *pila = pila_crear();
    print_test("Comprueba que se crea la pila", pila != NULL);
    pila_destruir(pila);
}

//Chequeo que se cumpla el invariante de la pila
static void prueba_apilar_desapilar(void) {
    pila_t *pila = pila_crear();
    int numero;
    int numero2;
    void* direccion = &numero;
    void* direccion2 = &numero2;
    print_test("Apilo una primera direccion",pila_apilar(pila,direccion));
    print_test("Verifico el tope",pila_ver_tope(pila) == &numero);
    print_test("Apilo otra segunda direccion distinta",pila_apilar(pila,direccion2));
    print_test("Verifico el tope",pila_ver_tope(pila) == direccion2);
    print_test("Verificio que la segundo que desapilo es la segunda direccion",pila_desapilar(pila) == direccion2);
    print_test("Verificio que lo tercero que desapilo es la primera direccion",pila_desapilar(pila) == direccion);
    pila_destruir(pila);
}

//Apilo y desapilo muchos elementemos
static void prueba_volumen(void) {
    pila_t *pila = pila_crear(); 
    int tam = 100000;
    int** orden_valores = malloc(sizeof(int*) * tam);
    bool ok = true;
    int i = 0;
    for (i = 0; i < tam; i++) {
        int* valor = malloc(sizeof(int));
        orden_valores[i] = valor;
        ok &= pila_apilar(pila,valor);
        ok &= (pila_ver_tope(pila) == valor);
    }
    print_test("Se pudo apilar los 100000 elementos correctamente",ok);
    ok = true;
    i = tam-1;
    while (!pila_esta_vacia(pila)) {
        int* guardado = pila_ver_tope(pila);
        ok &= (guardado == orden_valores[i]);
        ok &= (pila_ver_tope(pila) == pila_desapilar(pila));
        free(guardado);
        i--;
    }
    free(orden_valores);
    print_test("Se pudo desapilar los 100000 elementos correctamente",ok);
    print_test("Comprobando que la pila este vacia", pila_esta_vacia(pila));
    print_test("Verificando que NO se pueda desapilar en una pila vacia en la cual se encolo y se desencolo", pila_desapilar(pila) == NULL);
    print_test("Verificando que NO se pueda ver el tope en una pila vacia en la cual se encolo y se desencolo", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}


//Condición de borde: las acciones de desapilar y ver_tope en una pila recién creada son inválidas.
static void prueba_pila_vacia_desapilar_y_ver_tope(void) {
    pila_t *pila = pila_crear();
    print_test("Probando que NO se pueda desapilar en una pila recien creada",pila_desapilar(pila) == NULL);
    print_test("Probando que NO se pueda ver tope en una pila recien creada",pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}

//Condición de borde: la acción de esta_vacía en una pila recién creada es verdadero.
static void prueba_pila_vacia_esta_vacia(void) {
    pila_t *pila = pila_crear();
    print_test("Pruebo si la accion esta_vacia en un pila recien creada es true", pila_esta_vacia(pila));   
    pila_destruir(pila);
}

//Condición de borde: las acciones de desapilar y ver_tope en una pila a la que se le apiló y desapiló hasta estar vacía son inválidas.
static void prueba_comportamiento_pila(void) {
    pila_t *pila = pila_crear();
    int numero ;
    int* direc1 = &numero;
    print_test("Apilo una primera direccion",pila_apilar(pila,direc1));
    print_test("Desapilo esa direccion",pila_desapilar(pila) == direc1);
    print_test("Cheque de que la pila este vacia",pila_esta_vacia(pila));
    print_test("Probando que NO se pueda desapilar en una pila en la cual se apilo y desapilo",pila_desapilar(pila) == NULL);
    print_test("Probando que NO se pueda ver tope en una pila en la cual se apilo y desapilo",pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}

// Pruebas con NULL
static void prueba_con_NULL(void){
    pila_t *pila = pila_crear();
    print_test("Apilo NULL",pila_apilar(pila,NULL));
    print_test("Verifico que la pila dejo de estar vacia",!pila_esta_vacia(pila));
    print_test("Verifico que el tope sea NULL",pila_ver_tope(pila) == NULL);
    print_test("Verifico que lo primero que desapilo es NULL",pila_desapilar(pila) == NULL);
    print_test("Vuelvo a verificar que la pila este vacia",pila_esta_vacia(pila));
    pila_destruir(pila);
}


//Condición de borde: comprobar que al desapilar hasta que está vacía hace que la pila se comporte como recién creada.
static void prueba_comportamiento_pila_desapilada(void) {
    pila_t* pila = pila_crear();
    int numero;
    int* direc1 = &numero; 
    print_test("Apilo una direccion",pila_apilar(pila,direc1));
    print_test("Desapilo esa direccion",pila_desapilar(pila) == direc1);
    print_test("Verifico que la pila este vacia", pila_esta_vacia(pila));
    print_test("Verifico que NO se pueda ver el tope", pila_ver_tope(pila) == NULL);
    print_test("Verifico que NO se pueda desapilar",pila_desapilar(pila) == NULL);
    print_test("Apilo otra vez la direccion",pila_apilar(pila,direc1));
    print_test("Desapilo otra vez esa direccion",pila_desapilar(pila) == direc1);
    print_test("Y verfico que quede vacia la pila nuevamente",pila_esta_vacia(pila));
    pila_destruir(pila);
}


void pruebas_pila_estudiante() {
    prueba_crear_pila();
    prueba_apilar_desapilar();
    prueba_volumen();
    prueba_pila_vacia_desapilar_y_ver_tope();
    prueba_pila_vacia_esta_vacia();
    prueba_comportamiento_pila();
    prueba_con_NULL();
    prueba_comportamiento_pila_desapilada();
    // ...
}
/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
