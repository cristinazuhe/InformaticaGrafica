// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// **
// ** Práctica 4  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA4_HPP
#define IG_PRACTICA4_HPP

void P4_DibujarObjetos( ) ; 
void P4_Inicializar(  int argc,char *argv[] ) ;

void P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton );
bool P4_FGE_TeclaNormal( unsigned char tecla, int x_raton, int y_raton );

void P4_PintarEnSuave();
void P4_PintarEnPlano();

void P4_AumentaBeta();
void P4_DisminuirBeta();
void P4_AumentaAlfa();
void P4_DisminuirAlfa();
#endif
