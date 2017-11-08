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

int treeLength = 0; //Largo del árbol.
int counter = 0; //Contador usado en la función recorrerArbol_Inorden - roamTree_Inorden.

OBT* createElement(int elementHeight, char spanishWord[], char englishWord[], char definition){
   AVL* element = (AVL*)malloc(sizeof(AVL));
   element->elementHeight = elementHeight;
   strcpy(element->spanishWord, spanishWord);
   strcpy(element->englishWord, englishWord);
   strcpy(element->definition, definition);
   element->rightSonSpanishWord = NULL;
   element->leftSonSpanishWord = NULL;
   element->rightSonEnglishWord= NULL;
   element->leftSonEnglishWord = NULL;
   return element ;
}

void addElement(AVL* newElement ,AVL** root){
	if(*root == NULL){ //En caso de ya estár inicializada con un primer nodo
		*root = newElement;
		treeLength = 1;
		return;
	}
	else{
		OBT* currentElement = *root;
      OBT* auxElement = *root; //Auxiliar siempre irá en la posición anterior de current.
      while(currentElement != NULL){ //Avanzará hasta que currentElement apunte a NULL,
         auxElement = currentElement; //lo que dejará a auxElement en la posición anterior,
         if(newElement->elementNumber < currentElement->elementNumber){ // que es la posición requerida.
            currentElement = currentElement->leftSon;
         }
         else{
            currentElement = currentElement->rightSon;
         }
      }
      if(newElement->elementNumber < auxElement->elementNumber){
         auxElement->leftSon = newElement;
         treeLength++;
         return;
      }
      else{
         auxElement->rightSon = newElement;
         treeLength++;
         return;
      }
   }
}




int main(int argc, char const *argv[]){

   return 0;
}
