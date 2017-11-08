#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct AdelsonVelskiiLandis{
   int alturaElemento;
   char palabraEspanhol[24];
   char palabraIngles[46];
   char definicion[501];
   struct AdelsonVelskiiLandis* hijoDerechoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraEspanhol;
   struct AdelsonVelskiiLandis* hijoDerechoPalabraIngles;
   struct AdelsonVelskiiLandis* hijoIzquierdoPalabraIngles;
}AVL;

int largoArbol = 0; //Largo del árbol.
int contador = 0; //Contador usado en la función recorrerArbol_Inorden - roamTree_Inorden.

AVL* crearElemento(int alturaElemento, char palabraEspanhol[], char palabraIngles[], char definicion[]){
   AVL* elemento = (AVL*)malloc(sizeof(AVL));
   elemento->alturaElemento = alturaElemento;
   strcpy(elemento->palabraEspanhol, palabraEspanhol);
   strcpy(elemento->palabraIngles, palabraIngles);
   strcpy(elemento->definicion, definicion);
   elemento->hijoDerechoPalabraEspanhol = NULL;
   elemento->hijoIzquierdoPalabraEspanhol = NULL;
   elemento->hijoDerechoPalabraIngles = NULL;
   elemento->hijoIzquierdoPalabraIngles = NULL;
   return elemento;
}

/*void agregarElemento(AVL* nuevoElemento ,AVL** raiz){
	if(*raiz == NULL){ //En caso de ya estár inicializada con un primer nodo
		*raiz = nuevoElemento;
		largoArbol = 1;
		return;
	}
	else{
		AVL* elementoActual = *raiz;
      AVL* elementoAuxiliar = *raiz; //Auxiliar siempre irá en la posición anterior de current.
      while(elementoActual != NULL){ //Avanzará hasta que elementoActual apunte a NULL,
         elementoAuxiliar = elementoActual; //lo que dejará a elementoAuxiliar en la posición anterior,
         if(nuevoElemento->numeroElemento < elementoActual->numeroElemento){ // que es la posición requerida.
            elementoActual = elementoActual->hijoIzquierdo;
         }
         else{
            elementoActual = elementoActual->hijoDerecho;
         }
      }
      if(nuevoElemento->numeroElemento < elementoAuxiliar->numeroElemento){
         elementoAuxiliar->hijoIzquierdo = nuevoElemento;
         alturaElemento++;
         return;
      }
      else{
         elementoAuxiliar->hijoDerecho = nuevoElemento;
         alturaElemento++;
         return;
      }
   }
}*/

int main(int argc, char const *argv[]){
   int i = 0;
   char PalabraEspanhol[24] = "Chimbarongou";
   char PalabraIngles[46] = "Chim";
   while(PalabraEspanhol[i] != '\0' || PalabraIngles[i] != '\0' ) {
      if(PalabraEspanhol[i] != PalabraIngles[i]){
         if(PalabraEspanhol[i] < PalabraIngles[i]){
            printf("El orden alfabético sería: %s , %s\n", PalabraEspanhol, PalabraIngles);
            break;
         }
         else{
            printf("El orden alfabético sería: %s , %s\n", PalabraIngles, PalabraEspanhol);
            break;
         }
      }
      i++;
   }
   return 0;
}
