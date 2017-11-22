//Enunciado:
/*Traductor
Las diferencias entre los distintos idiomas siempre han conllevado un sesgo en las comunicaciones de las
diferentes culturas. Las personas, ante este impedimento de no poder transmitir ideas de forma que se
comprendan fácilmente, intentan capacitarse para poder dominar otros idiomas. Este aprendizaje
muchas veces es complicado dado a la cantidad de lenguajes existentes, por lo que se da prioridad a los
idiomas más utilizados o más relevantes según el área de interés del individuo.
Al estar estudiando un nuevo idioma, es inevitable hacer comparaciones con los idiomas ya conocidos,
buscando patrones en la sintaxis y equivalencias entre las palabras. Pero debido a que esto implica un
arduo trabajo de memorización de vocabulario no siempre es simple. Es por esto que los traductores
suelen ser una herramienta de apoyo en estos puntos, entregando una traducción que las personas
pueden ver en un lenguaje conocido.
En este laboratorio se busca implementar un traductor entre dos idiomas.
Para esto se requiere la utilización de la estructura de datos árbol para agilizar la búsqueda de una traducción.
Se debe considerar que los nodos deben tener la siguiente información:
   •Palabra en español.
   •Palabra en otro idioma.
   •Significado de la palabra en español.
   •Significado de la palabra en otro idioma.
   •Puntero español a nodo izquierdo.
   •Puntero español a nodo derecho.
   •Puntero otro idioma a nodo izquierdo.
   •Puntero otro idioma a nodo derecho.
Donde los punteros indican los hijos de un cierto nodo, para este árbol en particular se requiere que los
nodos se encuentren ordenados alfabéticamente, los “Punteros español” indican cómo se encuentra ordenado el
árbol según las palabras en español, mientras que los “Punteros otro idioma” indican cómo se encuentra ordenado
el árbol en ese  idioma. Es decir, se debe implementar un único árbol, pero que será equivalente a dos árboles
ordenados alfabéticamente en sus respectivos idiomas.
Por ejemplo, al insertar en el árbol las palabras Azul/Blue, Rojo/Red y Verde/Green en ese orden, da como
resultado el árbol desde la perspectiva del español. (Imagenes de Ejemplo en el enunciado).

Para  este  laboratoio  se  requiere  que  implemente  un  programa  que  reciba  un  archivo  de  texto  llamado
“Diccionario.in” y que genere un árbol AVL a partir de este. El programa debe permitir:
Consultar por una palabra junto su idioma y entregar su traducción.
Consultar por el significado de una palabra.
Entregar la información de todo el árbol en orden alfabético en español o inglés
(según indique el usuario) en una archivo llamado “Palabras.out”. Entregando la siguiente información por cada nodo:
Palabra_en_español Palabra_en_Otro (Hijo_izquierdo_en_español, Hijo_derecho_en_español) –
(Hijo_izquierdo_en_Otro, Hijo_derecho_en_inglés)

Fecha de entrega: 26/11/2017 hasta las 23:30 hrs
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct AdelsonVelskiiLandis{
   char palabraEspanhol[51];
   char palabraOtro[51];
   char definicionEspanhol[501];
   struct AdelsonVelskiiLandis* hijoDerechoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoDerechoPalabraOtro;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraOtro;
}AVL;

AVL* raizEspanhol = NULL;
AVL* raizOtro = NULL;
int largoArbol = 0; //Largo del árbol.
int contador = 0; //Contador usado en la función recorrerArbol_Inorden - roamTree_Inorden.

AVL* crearElemento(char palabraEspanhol[], char palabraOtro[], char definicionEspanhol[]){
   AVL* elemento = (AVL*)malloc(sizeof(AVL));
   strcpy(elemento->palabraEspanhol, palabraEspanhol);
   strcpy(elemento->palabraOtro, palabraOtro);
   strcpy(elemento->definicionEspanhol, definicionEspanhol);
   elemento->hijoDerechoPalabraEspanhol = NULL;
   elemento->hijoIzquierdoPalabraEspanhol = NULL;
   elemento->hijoDerechoPalabraOtro = NULL;
   elemento->hijoIzquierdoPalabraOtro = NULL;
   return elemento;
}

int compararPalabras(char P1[], char P2[]){
   int i;
   i = 0;
   if(P1 != NULL && P2 != NULL){
       while(P1[i] != '\0' && P2[i] != '\0' ) {
           if(P1[i] != P2[i]){
               if(P1[i] < P2[i]){
                   return 1; //P1 va primero alfabéticamente (o mayor).
               }
               else{
                   return -1; //P2 va primero alfabéticamente (o mayor).
               }
           }
           i++;
       }
       return -2; //Error.
   }
   return -3; //Error.
}

AVL* hijoDerechoPalabraEspanhol(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoDerechoPalabraEspanhol;
}

AVL* hijoDerechoPalabraOtro(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoDerechoPalabraOtro;

}

AVL* hijoIzquierdoPalabraEspanhol(AVL* elemento){
   if(elemento == NULL){
      return NULL;
   }
   return elemento->hijoIzquierdoPalabraEspanhol;
}

AVL* hijoIzquierdoPalabraOtro(AVL* elemento){
  if(elemento == NULL){
    return NULL;
  }
  return elemento->hijoIzquierdoPalabraOtro;
}

AVL* rotarDerechaEspanhol(AVL* elementoRotar){
      AVL* nuevaRaiz = hijoIzquierdoPalabraEspanhol(elementoRotar);
      elementoRotar->hijoIzquierdoPalabraEspanhol = hijoDerechoPalabraEspanhol(nuevaRaiz);
      nuevaRaiz->hijoDerechoPalabraEspanhol = elementoRotar;
      return nuevaRaiz;
}

AVL* rotarIzquierdaEspanhol(AVL* elementoRotar){
   AVL* nuevaRaiz = hijoDerechoPalabraEspanhol(elementoRotar);
   elementoRotar->hijoDerechoPalabraEspanhol = hijoIzquierdoPalabraEspanhol(nuevaRaiz);
   nuevaRaiz->hijoIzquierdoPalabraEspanhol = elementoRotar;
   return nuevaRaiz;
}

AVL* rotarDerechaOtro(AVL* elementoRotar){
      AVL* nuevaRaiz = hijoIzquierdoPalabraOtro(elementoRotar);
      elementoRotar->hijoIzquierdoPalabraOtro = hijoDerechoPalabraOtro(nuevaRaiz);
      nuevaRaiz->hijoDerechoPalabraOtro = elementoRotar;
      return nuevaRaiz;
}

AVL* rotarIzquierdaOtro(AVL* elementoRotar){
      AVL* nuevaRaiz = hijoDerechoPalabraOtro(elementoRotar);
      elementoRotar->hijoDerechoPalabraOtro = hijoIzquierdoPalabraOtro(nuevaRaiz);
      nuevaRaiz->hijoIzquierdoPalabraOtro = elementoRotar;
      return nuevaRaiz;
}

int alturaElementoEspanhol(AVL* elemento){
   int alturaDerecha, alturaIzquierda;
   if(elemento == NULL){
      return 0;
   }
   if(hijoDerechoPalabraEspanhol(elemento) == NULL && hijoIzquierdoPalabraEspanhol(elemento) == NULL){
      return 1;
   }
   alturaDerecha = alturaElementoEspanhol(hijoDerechoPalabraEspanhol(elemento));
   alturaIzquierda = alturaElementoEspanhol(hijoIzquierdoPalabraEspanhol(elemento));
   if(alturaIzquierda > alturaDerecha){
      return 1 + alturaIzquierda;
   }
   return 1 + alturaDerecha;
}

int alturaElementoOtro(AVL* elemento){
   int alturaDerecha, alturaIzquierda;
   if(elemento == NULL){
      return 0;
   }
   if(hijoDerechoPalabraOtro(elemento) == NULL && hijoIzquierdoPalabraOtro(elemento) == NULL){
      return 1;
   }
   alturaDerecha = alturaElementoOtro(hijoDerechoPalabraOtro(elemento));
   alturaIzquierda = alturaElementoOtro(hijoIzquierdoPalabraOtro(elemento));
   if(alturaIzquierda > alturaDerecha){
      return 1 + alturaIzquierda;
   }
   return 1 + alturaDerecha;
}

int diferenciaAlturasEspanhol(AVL* elemento){
   return alturaElementoEspanhol(hijoIzquierdoPalabraEspanhol(elemento)) - alturaElementoEspanhol(hijoDerechoPalabraEspanhol(elemento));
}

int diferenciaAlturasOtro(AVL* elemento){
   return alturaElementoOtro(hijoIzquierdoPalabraOtro(elemento)) - alturaElementoOtro(hijoDerechoPalabraOtro(elemento));
}

AVL* equilibrarRamaEspanhol(AVL* elementoEquilibrar){
   int diferenciaEspanhol;
   diferenciaEspanhol = diferenciaAlturasEspanhol(elementoEquilibrar);
   if(diferenciaEspanhol == 2){
      if(diferenciaAlturasEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar)) < 0){
         elementoEquilibrar->hijoIzquierdoPalabraEspanhol = rotarIzquierdaEspanhol(hijoIzquierdoPalabraEspanhol(elementoEquilibrar));
      }
      return rotarDerechaEspanhol(elementoEquilibrar);
   }
   if(diferenciaEspanhol == -2){
      if(diferenciaAlturasEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar)) > 0){
         elementoEquilibrar->hijoDerechoPalabraEspanhol = rotarDerechaEspanhol(hijoDerechoPalabraEspanhol(elementoEquilibrar));
      }

      return rotarIzquierdaEspanhol(elementoEquilibrar);
   }
   return elementoEquilibrar;
}

AVL* equilibrarRamaOtro(AVL* elementoEquilibrar){
   int diferenciaOtro;
   diferenciaOtro = diferenciaAlturasOtro(elementoEquilibrar);
   if(diferenciaOtro == 2){
      if(diferenciaAlturasOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar)) < 0){
         elementoEquilibrar->hijoIzquierdoPalabraOtro = rotarIzquierdaOtro(hijoIzquierdoPalabraOtro(elementoEquilibrar));
      }
      return rotarDerechaOtro(elementoEquilibrar);
   }
   if(diferenciaOtro == -2){
      if(diferenciaAlturasOtro(hijoDerechoPalabraOtro(elementoEquilibrar)) > 0){
         elementoEquilibrar->hijoDerechoPalabraOtro = rotarDerechaOtro(hijoDerechoPalabraOtro(elementoEquilibrar));
      }
      return rotarIzquierdaOtro(elementoEquilibrar);
   }
   return elementoEquilibrar;
}

AVL* agregarElementoEspanhol(AVL* nuevoElemento ,AVL** raizEspanhol) {
   int comparacionEspanhol;
   AVL* elementoActualEspanhol = *raizEspanhol;
   AVL* elementoAnteriorEspanhol = *raizEspanhol; //Auxiliar siempre irá en la posición anterior de actual.
   while(elementoActualEspanhol != NULL){ //Avanzará hasta que elementoActual apunte a NULL.
      comparacionEspanhol = compararPalabras(nuevoElemento->palabraEspanhol, elementoActualEspanhol->palabraEspanhol);
      elementoAnteriorEspanhol = elementoActualEspanhol; //lo que dejará a elementoAuxiliar en la posición anterior.
      if(comparacionEspanhol == 1){
         elementoActualEspanhol = elementoActualEspanhol->hijoIzquierdoPalabraEspanhol;
      }
      else{
         elementoActualEspanhol = elementoActualEspanhol->hijoDerechoPalabraEspanhol;
      }
   }
   if(comparacionEspanhol == 1){
      elementoAnteriorEspanhol->hijoIzquierdoPalabraEspanhol = nuevoElemento;
      largoArbol++;
   }
   else{
      elementoAnteriorEspanhol->hijoDerechoPalabraEspanhol = nuevoElemento;
      largoArbol++;
   }
   return equilibrarRamaEspanhol(*raizEspanhol);
}

AVL* agregarElementoOtro(AVL* nuevoElemento ,AVL** raizOtro){
   int comparacionOtro;
   AVL* elementoActualOtro = *raizOtro;
   AVL* elementoAnteriorOtro = *raizOtro; //Auxiliar siempre irá en la posición anterior de actual.
   while(elementoActualOtro != NULL){ //Avanzará hasta que elementoActual apunte a NULL,
      comparacionOtro = compararPalabras(nuevoElemento->palabraOtro, elementoActualOtro->palabraOtro);
      elementoAnteriorOtro = elementoActualOtro; //lo que dejará a elementoAuxiliar en la posición anterior,
      if(comparacionOtro == 1){
         elementoActualOtro = elementoActualOtro->hijoIzquierdoPalabraOtro;
      }
      else{
         elementoActualOtro = elementoActualOtro->hijoDerechoPalabraOtro;
      }
   }
   if(comparacionOtro == 1){
      elementoAnteriorOtro->hijoIzquierdoPalabraOtro = nuevoElemento;
      largoArbol++;
   }
   else{
      elementoAnteriorOtro->hijoDerechoPalabraOtro = nuevoElemento;
      largoArbol++;
   }
   return equilibrarRamaOtro(*raizOtro);
}
void agregarElemento(AVL* nuevoElemento ,AVL** raizEspanhol, AVL** raizOtro){
   if(*raizEspanhol == NULL){ //En caso de ya estár inicializada con un primer nodo
 		*raizEspanhol = nuevoElemento;
      *raizOtro = nuevoElemento;
 		largoArbol = 1;
 		return;
 	}
   *raizEspanhol = agregarElementoEspanhol(nuevoElemento, raizEspanhol);
   *raizOtro = agregarElementoOtro(nuevoElemento, raizOtro);
   return;
}

void mostrarArbol_PreordenEspanhol(AVL** raizEspanhol){
   if(*raizEspanhol != NULL){
      printf("[ %s ]",(*raizEspanhol)->palabraEspanhol);
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         mostrarArbol_PreordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol));
      }
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         mostrarArbol_PreordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol ));
      }
   }
}

void mostrarArbol_PreordenOtro(AVL** raizOtro){
   if(*raizOtro != NULL){
      printf("[ %s ]",(*raizOtro)->palabraOtro);
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         mostrarArbol_PreordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro));
      }
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         mostrarArbol_PreordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro));
      }
   }
}

void mostrarArbol_Preorden(AVL** raizEspanhol, AVL** raizOtro) {
   printf("\nLas palabras en Español en preorden son: ");
   mostrarArbol_PreordenEspanhol(raizEspanhol);
   printf("\nLas palabras en Otro en preorden son: ");
   mostrarArbol_PreordenOtro(raizOtro);
   printf("\n\n");
   return;
}

void mostrarArbol_InordenEspanhol(AVL** raizEspanhol){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         mostrarArbol_InordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol));
      }
      printf("[ %s ]",(*raizEspanhol)->palabraEspanhol);
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         mostrarArbol_InordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol ));
      }
   }
}

void mostrarArbol_InordenOtro(AVL** raizOtro){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         mostrarArbol_InordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro));
      }
      printf("[ %s ]",(*raizOtro)->palabraOtro);
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         mostrarArbol_InordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro));
      }
   }
}

void mostrarArbol_Inorden(AVL** raizEspanhol, AVL** raizOtro) {
   printf("\nLas palabras en Español en inorden son: ");
   mostrarArbol_InordenEspanhol(raizEspanhol);
   printf("\nLas palabras en Otro en inorden son: ");
   mostrarArbol_InordenOtro(raizOtro);
   printf("\n\n");
   return;
}

void mostrarArbol_PostordenEspanhol(AVL** raizEspanhol){
   if(*raizEspanhol != NULL){
      if((*raizEspanhol)->hijoIzquierdoPalabraEspanhol != NULL){
         mostrarArbol_PostordenEspanhol(&((*raizEspanhol)->hijoIzquierdoPalabraEspanhol));
      }
      if((*raizEspanhol)->hijoDerechoPalabraEspanhol != NULL){
         mostrarArbol_PostordenEspanhol(&((*raizEspanhol)->hijoDerechoPalabraEspanhol ));
      }
      printf("[ %s ]",(*raizEspanhol)->palabraEspanhol);
   }
}

void mostrarArbol_PostordenOtro(AVL** raizOtro){
   if(*raizOtro != NULL){
      if((*raizOtro)->hijoIzquierdoPalabraOtro != NULL){
         mostrarArbol_PostordenOtro(&((*raizOtro)->hijoIzquierdoPalabraOtro));
      }
      if((*raizOtro)->hijoDerechoPalabraOtro != NULL){
         mostrarArbol_PostordenOtro(&((*raizOtro)->hijoDerechoPalabraOtro));
      }
      printf("[ %s ]",(*raizOtro)->palabraOtro);
   }
}

void mostrarArbol_Postorden(AVL** raizEspanhol, AVL** raizOtro) {
   printf("\nLas palabras en Español en postorden son: ");
   mostrarArbol_PostordenEspanhol(raizEspanhol);
   printf("\nLas palabras en Otro en postorden son: ");
   mostrarArbol_PostordenOtro(raizOtro);
   printf("\n\n");
   return;
}

int comparacionCompleta(char P1[], char P2[]){
   int i;
   i = 0;
   if(P1 != NULL && P2 != NULL){
        while(P1[i] != '\0' && P2[i] != '\0' ) {
            if(P1[i] != P2[i]){
                if(P1[i] < P2[i]){
                    return 1; //P1 va primero alfabéticamente (o mayor).
                }
                if(P1[i] > P2[i]){
                    return -1; //P2 va primero alfabéticamente (o mayor).
                }
            }
            i++;
        }
        return 0; //Las palabras son iguales.
    }
    return -2;
}

AVL* buscarElemento(char palabraObjetivo[], AVL** raizEspanhol, AVL** raizOtro){ //Busca el primer elemento que coincida con el número objetivo.
   if(comparacionCompleta((*raizEspanhol)->palabraEspanhol, palabraObjetivo) == 0){
      return (*raizEspanhol);
   }
   if(comparacionCompleta((*raizOtro)->palabraOtro, palabraObjetivo) == 0){
      return (*raizOtro);
   }
   else{
      //Buscar en palabras en español.
      AVL* elementoActualEspanhol = *raizEspanhol;
      if(elementoActualEspanhol->palabraEspanhol != NULL){
          while(comparacionCompleta(elementoActualEspanhol->palabraEspanhol, palabraObjetivo) != 0 && elementoActualEspanhol != NULL){
              if(compararPalabras(palabraObjetivo, elementoActualEspanhol->palabraEspanhol) == 1){
                  elementoActualEspanhol = elementoActualEspanhol->hijoIzquierdoPalabraEspanhol;
              }
              else{
                  elementoActualEspanhol = elementoActualEspanhol->hijoDerechoPalabraEspanhol;
              }
          }
      }
      if(elementoActualEspanhol == NULL){
         //Buscar en palabras en inglés. Si se ha rotado es posible que no funcione.
         AVL* elementoActualOtro = *raizOtro;
         if(elementoActualOtro->palabraOtro != NULL){
             while(comparacionCompleta(elementoActualOtro->palabraOtro, palabraObjetivo) != 0 && elementoActualOtro != NULL){
                 if(compararPalabras(palabraObjetivo, elementoActualOtro->palabraOtro) == 1){
                     elementoActualOtro = elementoActualOtro->hijoIzquierdoPalabraOtro;
                 }
                 else{
                     elementoActualOtro = elementoActualOtro->hijoDerechoPalabraOtro;
                 }
             }
         }
         if(elementoActualOtro == NULL){
            printf("No se encuentra la palabra buscada\n");
         }
         else{
            return elementoActualOtro;
         }
      }
      else{
         return elementoActualEspanhol;
      }
   }
}

void leerArchivo(){
    char palabraEspanhol[51], palabraOtro[51], definicionEspanhol[501];
    FILE *archivoObjetivo = NULL;
    archivoObjetivo = fopen("Diccionario.in","r");
    while(!feof(archivoObjetivo)){
          fscanf(archivoObjetivo,"%s%s",palabraEspanhol, palabraOtro);
          fscanf(archivoObjetivo," %[^\n]", definicionEspanhol);
          if(!feof(archivoObjetivo)){
             AVL* elemento = crearElemento(palabraEspanhol, palabraOtro, definicionEspanhol);
             agregarElemento(elemento, &raizEspanhol, &raizOtro);
          }
       }
    fclose(archivoObjetivo);
    return;
}

int main(int argc, char const *argv[]){
    printf("\n");
    leerArchivo();
    AVL* elementoBuscado1 = buscarElemento("Azul", &raizEspanhol, &raizOtro);
    printf("Palabra buscada es: Azul\n");
    printf("La palabra en español es: %s , en otro es: %s y su definición es: %s\n\n", elementoBuscado1->palabraEspanhol, elementoBuscado1->palabraOtro, elementoBuscado1->definicionEspanhol);
    AVL* elementoBuscado2 = buscarElemento("Orange", &raizEspanhol, &raizOtro);
    printf("Palabra buscada es: Orange\n");
    printf("La palabra en español es: %s , en otro es: %s y su definición es: %s\n", elementoBuscado2->palabraEspanhol, elementoBuscado2->palabraOtro, elementoBuscado2->definicionEspanhol);
    mostrarArbol_Preorden(&raizEspanhol, &raizOtro);
    mostrarArbol_Inorden(&raizEspanhol, &raizOtro);
    mostrarArbol_Postorden(&raizEspanhol, &raizOtro);
    printf("\n");
   return 0;
}
