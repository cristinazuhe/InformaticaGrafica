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
#include "grafoescena.hpp"

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
