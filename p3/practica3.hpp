// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 3  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA3_HPP
#define IG_PRACTICA3_HPP
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

void P3_AumentarTercero();
void P3_ReducirTercero();
void P3_AumentarSegundo();
void P3_ReducirSegundo();
void P3_ReducirPrimero();
void P3_AumentaPrimero();

void P3_DibujarObjetos( ) ; 
void P3_Inicializar(  int argc,char *argv[] ) ;
void P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton );
bool P3_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton );
void P3_DibujarObjetoSentillo(int n );
void P3_NGE_Visualizar (NodoGE *nodo);
void P3_ComponerTrans( ParMatriz4f *ptr_pars_matriz);

void P3_ModificarOrdenAAjedrez( );
void P3_ModificarOrdenASolido( );
void P3_ModificarOrdenAAlambre( );
void P3_ModificarOrdenAPuntos ( );
void P3_ModificarOrdenANormal( );
#endif
