// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 2 (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica2.hpp"
#include "practica1.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>
#define PI (3.141592653589793)
// ---------------------------------------------------------------------
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.


MallaTVT mimallav;
void P2_Inicializar( int argc,char *argv[] )
{
   if( argc!=4){
      exit(-1);
   }
   //leemos el ply e introducimos los vertices en la malla.
   ply::read_vertices( argv[2], mimallav.vertices_ply );  //leemos el archivo ply

   double n_perfiles=strtod(argv[3],NULL); //leer el numero de perfiles a realizar
   CrearObjetoRevolucion( &mimallav , n_perfiles );
   CrearNormalesCaras( &mimallav);
   CrearNormalesVertices( &mimallav);

}


bool activonormalcaras=false;    //para representar las normales de las caras
bool activonormalvertices=false; //para represnetar las normales de los vertices
int orden2=9;	                 //para indicar el modo de dibujo 
void P2_ModificarOrdenAAlambre( ) { orden2=0;}         //0-->alambre
void P2_ModificarOrdenAAjedrez( ) { orden2=1;}         //1-->ajedrez
void P2_ModificarOrdenASolido( )  { orden2=2;}         //2-->solido
void P2_ModificarOrdenAPuntos( )  { orden2=3;}         //3-->puntos
void P2_ModificarPintarNormalesVertices() {orden2=4;}  //4-->normalesvertices
void P2_ModificarPintarNormalesCaras()    {orden2=5;}  //5-->normalescaras

void P2_ActivoNormalCaras()    {    //para representar las normales de las caras
   if(activonormalcaras)
       activonormalcaras=false;
   else
       activonormalcaras=true;
}
void P2_ActivoNormalVertices()    { //para represnetar las normales de los vertices
   if(activonormalvertices)
       activonormalvertices=false;
   else
       activonormalvertices=true;
}



void P2_DibujarObjetos( ) 
{
   
   glEnableClientState( GL_VERTEX_ARRAY );
    if(orden2==0)
      VerMallaEnAlambre( &mimallav );
    else if(orden2==2)
      VerMallaEnSolido( &mimallav );
    else if(orden2==1)
      VerMallaEnAjedrez( &mimallav );
    else if(orden2==3)
      VerMallaEnPuntos( &mimallav );
    else if(orden2==4) 
      PintarNormalesVertices( &mimallav ) ;
    else if(orden2==5) 
      PintarNormalesCaras( &mimallav ) ;
   
   if(activonormalcaras){
   //pintamos las normales de las caras
   glColor3f(1.0,0.0,0.0);
   glVertexPointer( 3, GL_FLOAT, 0, mimallav.normales_car[0].coo);
   glDrawArrays( GL_LINES , 0, (mimallav.num_caras/3)*2); //por cada cara tenemos dos vértices que nos dan la normal (el vertice baricentro y el vertice normal)
  }
 
   if(activonormalvertices){
   //normales de los vertices;
   glPointSize(5.0);
   glColor3f(0.0,1.0,0.0);
   glVertexPointer( 3, GL_FLOAT, 0, mimallav.normales_ver[0].coo);
   glDrawArrays( GL_LINES , 0, ((mimallav.num_vertices)/3)*2); 
   }

}
