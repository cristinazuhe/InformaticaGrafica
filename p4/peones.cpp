
#include <GL/glut.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>
#include "fuenteluz.hpp"
#include "peones.hpp"
#include "operacionesmalla.hpp"
#include "grafoescena.hpp"
#include "jpg_imagen.hpp"

using namespace std;
//*************************************************************************************
Peon1::Peon1(){
 ply::read_vertices( "perfil.ply", mallapeon1.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion( &mallapeon1 , 10.0 );
 CrearNormalesCaras(&mallapeon1);
 CrearNormalesVertices(&mallapeon1);

 //sesgado de los peones
 EntradaNGE e_escalado_peones;
 e_escalado_peones.tipo=2;
 m_escalado_peones.tipo=1;
 m_escalado_peones.vec[1].coo[0]=0.2;  
 m_escalado_peones.vec[1].coo[1]=0.2;  
 m_escalado_peones.vec[1].coo[2]=0.2;  
 e_escalado_peones.ptr_pars_matriz=&m_escalado_peones;
 minodopeon1.entrada.push_back(e_escalado_peones);
 //traslacion del peon1  
 EntradaNGE e_traslacion1;
 e_traslacion1.tipo=1;
 m_t_peon1=matriz_traslacion(0.0, 1.40, 3.0);
 e_traslacion1.ptr_matriz=&m_t_peon1;
 minodopeon1.entrada.push_back(e_traslacion1);
 //peon1
 EntradaNGE e_peon1;
 e_peon1.tipo=4;   
 minodopeon1.entrada.push_back(e_peon1);
}

void Peon1::CargarTexturaPeon1(){
   materialpeon1.AsociarTextura("text-madera.jpg");
   materialpeon1.ModoGeneracion(1);

   Tupla3f n_c_especular(1.0,1.0,1.0);
   materialpeon1.ModificarEspecular(n_c_especular);
   Tupla3f n_c_emision(0.0,0.0,0.0);
   materialpeon1.ModificarEmision(n_c_emision);
   Tupla3f n_difuso(1.0,1.0,1.0);
   materialpeon1.ModificarDifuso(n_difuso);
   materialpeon1.ModificarExponente(0.8);
}
void Peon1::P4_NGE_VisualizarPlano (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon1.activar();
           VerISPlano( &mallapeon1 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon1::VerPeon1EnPlano(){ 
    P4_NGE_VisualizarPlano (&minodopeon1);
}

void Peon1::P4_NGE_VisualizarSuave (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon1.activar();
           VerISSuave( &mallapeon1 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon1::VerPeon1EnSuave(){ 
    P4_NGE_VisualizarSuave (&minodopeon1);
}


//********************************************************************************************
Peon2::Peon2(){
 ply::read_vertices( "perfil.ply", mallapeon2.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion( &mallapeon2 , 10.0 );
 CrearNormalesCaras(&mallapeon2);
 CrearNormalesVertices(&mallapeon2);

 //sesgado de los peones
 EntradaNGE e_escalado_peones;
 e_escalado_peones.tipo=2;
 m_escalado_peones.tipo=1;
 m_escalado_peones.vec[1].coo[0]=0.2;  
 m_escalado_peones.vec[1].coo[1]=0.2;  
 m_escalado_peones.vec[1].coo[2]=0.2;  
 e_escalado_peones.ptr_pars_matriz=&m_escalado_peones;
 minodopeon2.entrada.push_back(e_escalado_peones);
 //traslacion del peon2  
 EntradaNGE e_traslacion2;
 e_traslacion2.tipo=1;
 m_t_peon2=matriz_traslacion(-3.0, 1.40, 3.0);
 e_traslacion2.ptr_matriz=&m_t_peon2;
 minodopeon2.entrada.push_back(e_traslacion2);
 //peon2
 EntradaNGE e_peon2;
 e_peon2.tipo=4;   
 minodopeon2.entrada.push_back(e_peon2);

 //difuso, color blanco, sin brillos
 Tupla3f n_c_difuso(0.5,0.5,0.5);
 materialpeon2.ModificarDifuso(n_c_difuso);
 Tupla3f n_c_especular(0.0,0.0,0.0);
 materialpeon2.ModificarEspecular(n_c_especular);
 Tupla3f n_c_emision(0.5,0.5,0.5);
 materialpeon2.ModificarEmision(n_c_emision);
 materialpeon2.ModificarExponente(128.0);
}

void Peon2::Peon2_NGE_VisualizarSuave (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon2.activar();
           VerISSuave( &mallapeon2 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon2::VerPeon2EnSuave(){ 
    Peon2_NGE_VisualizarSuave (&minodopeon2);
}

void Peon2::Peon2_NGE_VisualizarPlano (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon2.activar();
           VerISPlano( &mallapeon2 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon2::VerPeon2EnPlano(){ 
    Peon2_NGE_VisualizarPlano (&minodopeon2);
}


//********************************************************************************************
Peon3::Peon3(){
 ply::read_vertices( "perfil.ply", mallapeon3.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion( &mallapeon3 , 10.0 );
 CrearNormalesCaras(&mallapeon3);
 CrearNormalesVertices(&mallapeon3);

 //sesgado de los peones
 EntradaNGE e_escalado_peones;
 e_escalado_peones.tipo=2;
 m_escalado_peones.tipo=1;
 m_escalado_peones.vec[1].coo[0]=0.2;  
 m_escalado_peones.vec[1].coo[1]=0.2;  
 m_escalado_peones.vec[1].coo[2]=0.2;  
 e_escalado_peones.ptr_pars_matriz=&m_escalado_peones;
 minodopeon3.entrada.push_back(e_escalado_peones);
 //traslacion del peon3  
 EntradaNGE e_traslacion3;
 e_traslacion3.tipo=1;
 m_t_peon3=matriz_traslacion(3.0, 1.40, 3.0);
 e_traslacion3.ptr_matriz=&m_t_peon3;
 minodopeon3.entrada.push_back(e_traslacion3);
 //peon3
 EntradaNGE e_peon3;
 e_peon3.tipo=4;   
 minodopeon3.entrada.push_back(e_peon3);

 //bajo difuso, alto especular
 Tupla3f n_c_especular(1.0,1.0,1.0);
 materialpeon3.ModificarEspecular(n_c_especular);
 Tupla3f n_c_emision(0.0,0.0,0.0);
 materialpeon3.ModificarEmision(n_c_emision);
 Tupla3f n_difuso(0.2,0.2,0.2);
 materialpeon3.ModificarDifuso(n_difuso);
 materialpeon3.ModificarExponente(0.8);
}

void Peon3::Peon3_NGE_VisualizarSuave (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon3.activar();
           VerISSuave( &mallapeon3 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon3::VerPeon3EnSuave(){ 
    Peon3_NGE_VisualizarSuave (&minodopeon3);
}

void Peon3::Peon3_NGE_VisualizarPlano (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
           ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 4:
           materialpeon3.activar();
           VerISPlano( &mallapeon3 );
         break;   
      }
   }
   glPopMatrix();
}
void Peon3::VerPeon3EnPlano(){ 
    Peon3_NGE_VisualizarPlano (&minodopeon3);
}
