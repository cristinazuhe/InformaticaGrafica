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
// coordenadas de los vértices del cubo:

const unsigned num_verts_cubo = 8 ;
int orden=4;

GLfloat coords_verts_cubo[num_verts_cubo][3] = 
   {  { -0.5, -0.5, +0.5 } ,
      { +0.5, -0.5, +0.5 } ,
      { +0.5, +0.5, +0.5 } ,
      { -0.5, +0.5, +0.5 } ,
      { -0.5, -0.5, -0.5 } ,
      { +0.5, -0.5, -0.5 } ,
      { +0.5, +0.5, -0.5 } ,
      { -0.5, +0.5, -0.5 }
   };
   
// ---------------------------------------------------------------------
//  dibujar vértices del cubo en modo inmediato con begin/end

void DibujarCuboPuntos()
{
   glColor3f( 0.10, 0.15, 0.40 );
   glPointSize(4);

   glBegin(GL_POINTS);
   for ( unsigned i= 0 ; i < num_verts_cubo ; i++ )
      glVertex3fv( &( coords_verts_cubo[i][0] ) );
   glEnd();

   
}

// ---------------------------------------------------------------------
// Función para implementar en la práctica 1 para inicialización.
// Se llama una vez al inicio, cuando ya se ha creado la ventana e 
// incializado OpenGL. El PLY se debe cargar aquí.


std::vector<float> vertices_ply ;   // coordenadas de vértices obtenidas del ply
std::vector<int>   caras_ply ;      // índices de vértices de triángulos obtenidas del ply
std::vector<Tupla3f> vertices;      // vector de tuplas3f para almacenar los vertices del ply
std::vector<Tupla3i> caras;         // vector de tuplas3i para almacenar las caras del ply
std::vector<Tupla3i> caras_pares;   // vector de tuplas 3i para almacenar las caras pares del ply
std::vector<Tupla3i> caras_impares; // vector de tuplas 3i para almacenar las caras impares del ply

void P1_Inicializar( int argc,char *argv[] )
{
   if( argc!=2){
      exit(-1);
   }
   ply::read( argv[1], vertices_ply, caras_ply );  //leemos el archivo ply

   //obtenemos los vertices en un vector de tuplas3f
   int num_vertices = vertices_ply.size();
 
   for( int i=0; i< num_vertices ; i=i+3){
       Tupla3f vertice(vertices_ply[i],vertices_ply[i+1],vertices_ply[i+2]);  //cada 3 float nos dan un vertice
       vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
   }


   //obtenemos las caras en un vector de tuplas3i
    int num_caras = caras_ply.size();
    for( int i=0; i< num_caras ; i=i+3){
       Tupla3i cara;
       cara.idx[0]=caras_ply[i];
       cara.idx[1]=caras_ply[i+1];
       cara.idx[2]=caras_ply[i+2];
       caras.push_back(cara);
   }

   //metemos las caras pares en el vector caras_pares y las impares en caras_impares
   int paridad=0;
   int nume_caras=caras.size();
   for( int i=0; i< nume_caras ; i++){
      if(paridad==0){
         caras_pares.push_back(caras[i]);
         paridad=1;
      }else{
         caras_impares.push_back(caras[i]);
         paridad=0;
      }
   }

}



void P1_ModificarOrdenAAlambre( ){ orden=0;}
void P1_ModificarOrdenAAjedrez( ) { orden=1;}
void P1_ModificarOrdenASolido( ) {  orden=2;}
void P1_ModificarOrdenAPuntos( ) {  orden=4;}
// -------------------------------------------------------------------
// Función a implementar en la práctia 1  para dibujar los objetos

void P1_DibujarObjetos() 
{
   
   glEnableClientState( GL_VERTEX_ARRAY );  
   //pintamos los vertices
   glVertexPointer( 3, GL_FLOAT, 0, vertices[0].coo);
   glDrawArrays( GL_POINTS , 0, (vertices_ply.size())/3);   
   
   if(orden!=4){
   //pintamos las caras   
    if(orden==0)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //GL_POINT, GL_LINE, GL_FILL
    else if(orden==1 || orden==2)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
    
    glColor3f( 0.0, 0.0, 0.0 );
    glVertexPointer( 3, GL_FLOAT, 0, vertices[0].coo);
    glDrawElements( GL_TRIANGLES , (caras_ply.size())/2, GL_UNSIGNED_INT , caras_pares[0].idx );

    if(orden==1)
        glColor3f( 1.0, 1.0, 1.0 );
    glVertexPointer( 3, GL_FLOAT, 0, vertices[0].coo);
    glDrawElements( GL_TRIANGLES , (caras_ply.size())/2, GL_UNSIGNED_INT , caras_impares[0].idx );  
   }

}
