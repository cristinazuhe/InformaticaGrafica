// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************


#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include <vector>
struct MallaTVT{
   int num_vertices;
   int num_caras;
   std::vector<float> vertices_ply ;   // coordenadas de vértices obtenidas del ply
   std::vector<int>   caras_ply ;      // índices de vértices de triángulos obtenidas del ply
   std::vector<Tupla3f> vertices;      // vector de tuplas3f para almacenar los vertices del ply
   std::vector<Tupla3i> caras;         // vector de tuplas3i para almacenar las caras del ply

   std::vector<Tupla3f> normales_car;      // vector de tuplas3f para almacenar las normales de las caras
   std::vector<Tupla3f> normales_ver;      // vector de tuplas3f para almacenar las normales de los vertices

};

void P1_DibujarObjetos() ; 
void P1_Inicializar(  int argc,char *argv[] ) ;
void P1_ModificarOrdenAAjedrez( );
void P1_ModificarOrdenASolido( );
void P1_ModificarOrdenAAlambre( );
void P1_ModificarOrdenAPuntos ( );
void VerMallaEnAlambre(  MallaTVT *malla );
void VerMallaEnSolido( MallaTVT *malla );
void VerMallaEnAjedrez( MallaTVT *malla );
void VerMallaEnPuntos( MallaTVT *malla );
 

#endif
