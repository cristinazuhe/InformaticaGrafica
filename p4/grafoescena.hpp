#ifndef IG_GRAFOESCENA_HPP
#define IG_GRAFOESCENA_HPP

#include "operacionesmalla.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "matriz.hpp"

struct ParMatriz4f{
   unsigned int tipo;  //0--> rotacion, 1-->escalado, 2-->traslacion
   Tupla3f vec[3];
   float angulo;
};
struct NodoGE;
struct EntradaNGE{
   unsigned int tipo;
   union{
      NodoGE * ptr_subesc;
      Matriz4f * ptr_matriz;
      ParMatriz4f * ptr_pars_matriz;
      unsigned int num_obj_sim;
   };
};

struct NodoGE{
   std::vector<EntradaNGE> entrada;
};

void NGE_Visualizar (NodoGE *nodo);
void ComponerTrans( ParMatriz4f *ptr_pars_matriz);


#endif
