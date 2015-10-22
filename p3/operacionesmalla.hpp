#ifndef OPERACIONESMALLA_HPP
#define OPERACIONESMALLA_HPP

#include <vector>
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i

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


void VerMallaEnPuntos( MallaTVT *malla );
void VerMallaEnAlambre(  MallaTVT *malla );
void VerMallaEnSolido( MallaTVT *malla );
void VerMallaEnAjedrez( MallaTVT *malla );
void PintarNormalesVertices( MallaTVT *malla );
void PintarNormalesCaras( MallaTVT *malla );
void CrearObjetoRevolucion(MallaTVT *malla , int numero_perfiles);
void CrearNormalesCaras(MallaTVT *mimallav);
void CrearNormalesVertices(MallaTVT *mimallav);

#endif
