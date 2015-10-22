// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 4 (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include <GL/freeglut_ext.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica4.hpp"
#include "operacionesmalla.hpp"
#include "fuenteluz.hpp"
#include "grafoescena.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>
#include "jpg_imagen.hpp"
#include "lata.hpp"
#include "peones.hpp"

FuenteLuz fuentedireccional;
FuenteLuz fuenteposicional;

LataCocaCola miobjetolata;
Peon1 mipeon1;
Peon2 mipeon2;
Peon3 mipeon3;

bool enplano=false;

void P4_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){}

bool P4_FGE_TeclaNormal(unsigned char tecla, int x_raton, int y_raton ){
  bool cambio = true ;
  switch (toupper(tecla))  {
         case 'S' :  //pintar en suave
           P4_PintarEnSuave();
           cambio=true;
         break ;
         case 'P' :  //pintar en plano
           P4_PintarEnPlano();
           cambio=true;
         break ;
         case 'A' :  //aumenta logitud
           P4_AumentaBeta();
           cambio=true;
         break ;
         case 'Z' :  //disminuye longitud
           P4_DisminuirBeta();
           cambio=true;
         break ;
         case 'X' :  //aumenta latitud
           P4_AumentaAlfa();
           cambio=true;
         break ;
         case 'C' :  //disminuye latitud
           P4_DisminuirAlfa();
           cambio=true;
         break ;
     }
  using namespace std ;
  return cambio;
}
float longitud=0.0;
float latitud=0.0;

void P4_AumentaBeta(){
  if(longitud==360.0)
     longitud=longitud-360.0;
  longitud++;
}
void P4_DisminuirBeta(){
  if(longitud==0.0)
     longitud=longitud+360.0;
  longitud--;
}
void P4_AumentaAlfa(){
  if(latitud==360.0)
     latitud=latitud-360.0;
  latitud++;
}
void P4_DisminuirAlfa(){
  if(latitud==0.0)
     latitud=latitud+360.0;
  latitud--;
}

void P4_PintarEnSuave(){
  enplano=false;
}

void P4_PintarEnPlano(){
   enplano=true;
}

   Tupla3f d_colores[3];
   Tupla3f p_colores[3];
   Tupla4f posvecd;
   Tupla4f posvecp;

void P4_Inicializar( int argc,char *argv[] ){
  //fuente de luz direccional
   d_colores[0] = Tupla3f (1.0,1.0,1.0) ;
   d_colores[1] = Tupla3f (1.0,1.0,1.0) ;
   d_colores[2] = Tupla3f (0.3,0.3,0.3) ;
   posvecd = Tupla4f {100.0,-100.0,50.0,0.0}; 

  //fuente de luz posicional
   p_colores[0] = Tupla3f (0.0,0.0,0.0) ;
   p_colores[1] = Tupla3f (0.9,0.9,0.9) ;
   p_colores[2] = Tupla3f (1.0,0.3,0.3) ;
   posvecp = Tupla4f {-30.0,50.0,-1.0,0.0};  
   fuenteposicional.ModificarValores(0.0,0.0,p_colores, posvecp, true);  //true--> posicional
   fuenteposicional.Activar(1);

   miobjetolata.CargarTexturaLata();  //asocia la textura y define los valores de los materiales(cuerpo y tapas)
   mipeon1.CargarTexturaPeon1();
}

void P4_DibujarObjetos( ) {
glEnableClientState( GL_VERTEX_ARRAY );
 
   fuentedireccional.ModificarValores(longitud,latitud,d_colores, posvecd, false);  //false--> direccional
   fuentedireccional.Activar(0);

if(enplano){
   miobjetolata.VerLataEnPlano();
   glDisable(GL_TEXTURE_2D);
   mipeon1.VerPeon1EnPlano();
   glDisable(GL_TEXTURE_2D);
   mipeon2.VerPeon2EnPlano();
   glDisable(GL_TEXTURE_2D);
   mipeon3.VerPeon3EnPlano();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
}else{
   miobjetolata.VerLataEnSuave();
   glDisable(GL_TEXTURE_2D);
   mipeon1.VerPeon1EnSuave();
   glDisable(GL_TEXTURE_2D);
   mipeon2.VerPeon2EnSuave();
   glDisable(GL_TEXTURE_2D);
   mipeon3.VerPeon3EnSuave();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
}
}
