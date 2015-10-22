// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 1  (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica1.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.

   MallaTVT mimalla;

void P1_Inicializar( int argc,char *argv[] ){
   if( argc!=4){
      exit(-1);
   }
   ply::read( argv[1], mimalla.vertices_ply, mimalla.caras_ply );  //leemos el archivo ply

   //obtenemos los vertices en un vector de tuplas3f
   mimalla.num_vertices = mimalla.vertices_ply.size();
   for( int i=0; i< mimalla.num_vertices ; i=i+3){
     Tupla3f vertice(mimalla.vertices_ply[i],mimalla.vertices_ply[i+1],mimalla.vertices_ply[i+2]);  //cada 3 float nos dan un vertice
     mimalla.vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
   }


   //obtenemos las caras en un vector de tuplas3i
    mimalla.num_caras = mimalla.caras_ply.size();
    for( int i=0; i< mimalla.num_caras ; i=i+3){
       Tupla3i cara;
       cara.idx[0]=mimalla.caras_ply[i];
       cara.idx[1]=mimalla.caras_ply[i+1];
       cara.idx[2]=mimalla.caras_ply[i+2];
       mimalla.caras.push_back(cara);
   }
}

void VerMallaEnPuntos( MallaTVT *malla ){
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawArrays( GL_POINTS , 0, (malla->num_vertices)/3);   
}
void VerMallaEnAlambre( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //GL_POINT, GL_LINE, GL_FILL
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawElements( GL_TRIANGLES , malla->num_caras, GL_UNSIGNED_INT , malla->caras[0].idx );
}
void VerMallaEnSolido( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawElements( GL_TRIANGLES , malla->num_caras, GL_UNSIGNED_INT , malla->caras[0].idx );
}
void VerMallaEnAjedrez( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int paridad=0;
   for( int i=0; i< (malla->num_caras)/3 ; i++){
      if(paridad==0){
         glColor3f( 1.0, 0.0, 1.0 );
         paridad=1;
      }else{
         glColor3f( 0.5, 0.0, 0.5 );
         paridad=0;
      }
      glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
      glDrawElements( GL_TRIANGLES , 3 , GL_UNSIGNED_INT , malla->caras[i].idx );
   }
  }

int orden=3;
void P1_ModificarOrdenAAlambre( ) { orden=0;}
void P1_ModificarOrdenAAjedrez( ) { orden=1;}
void P1_ModificarOrdenASolido( )  { orden=2;}
void P1_ModificarOrdenAPuntos( )  { orden=3;}
// -------------------------------------------------------------------
// Función a implementar en la práctia 1  para dibujar los objetos

void P1_DibujarObjetos() {
   glEnableClientState( GL_VERTEX_ARRAY );  
    
    if(orden==0)
      VerMallaEnAlambre( &mimalla );
    else if(orden==2)
      VerMallaEnSolido( &mimalla );
    else if(orden==1)
      VerMallaEnAjedrez( &mimalla );
    else if(orden==3)
      VerMallaEnPuntos( &mimalla );

}
