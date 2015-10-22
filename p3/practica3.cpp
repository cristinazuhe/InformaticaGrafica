// *********************************************************************
// **
// ** Informática Gráfica, curso 2014-15
// ** 
// ** Práctica 3 (implementación)
// **
// *********************************************************************


#include <GL/glut.h>

#include <GL/freeglut_ext.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica3.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>

#define verde 0
#define negro 1
#define marron 2

/** Definicion de los colores usados.**/
float color[3][3]={{0.3,1.0,0.3},{0.0,0.0,0.0},{0.6,0.4,0.2}};

float gral_rotacion=0.0;
float gral_escalado=1.0;
float gral_traslacion=0.0;

MallaTVT mallacesta;
MallaTVT mallaglobo;
MallaTVT mallatierra;

NodoGE minodo;
NodoGE minodoglobo;
NodoGE minodocuerda1;
NodoGE minodocuerda2;
NodoGE minodocuerda3;
NodoGE minodocuerda4;

ParMatriz4f m_escalado; //para el escalado del globo
ParMatriz4f m_r_gcc;    //para la rotacion del globo, cuerdas y cesta
ParMatriz4f m_t_cc;     //para la traslacion de cuerdas y cesta
   
Matriz4f m_t_globo;
Matriz4f m_r_cuerdas;
Matriz4f m_t_c1;
Matriz4f m_t_c2;
Matriz4f m_t_c3;
Matriz4f m_t_c4;
int orden3=4;	                 //para indicar el modo de dibujo 
void P3_ModificarOrdenAAlambre( ) { orden3=0;}         //0-->alambre
void P3_ModificarOrdenAAjedrez( ) { orden3=1;}         //1-->ajedrez
void P3_ModificarOrdenASolido( )  { orden3=2;}         //2-->solido
void P3_ModificarOrdenAPuntos( )  { orden3=3;}         //3-->puntos
void P3_ModificarOrdenANormal( )  { orden3=4;}         //4-->vemos la escena normal

void P3_FGE_TeclaEspecial( int tecla, int x_raton, int y_raton ){}

bool P3_FGE_TeclaNormal(unsigned char tecla, int x_raton, int y_raton ){
  bool cambio = true ;
  switch (tecla)  {
         case 'Z' :  //aumenta primer grado
           P3_AumentaPrimero();
           cambio=true;
         break ;
         case 'z' :  //reduce primer grado
           P3_ReducirPrimero();
           cambio=true;
         break ;
         case 'X' :  //aumenta segundo grado
           P3_AumentarSegundo();
           cambio=true;
         break ;
         case 'x' :  //reduce segundo grado
           P3_ReducirSegundo();
           cambio=true;
         break ;
         case 'C' :  //aumenta tercer grado
           P3_AumentarTercero();
           cambio=true;
         break ;
         case 'c' :  //reduce tercer grado
           P3_ReducirTercero();
           cambio=true;
         break ;
         case 'l' :  //en alambre
           P3_ModificarOrdenAAlambre( );
         break ;
         case 'a' :  //en ajedrez
           P3_ModificarOrdenAAjedrez( );
         break ;
         case 's' :  //en solido
           P3_ModificarOrdenASolido( );
         break ;
         case 'p' :  //puntos
           P3_ModificarOrdenAPuntos( );
         break ;
         case 'n' :  //puntos
           P3_ModificarOrdenANormal( );
         break ;
     }
  using namespace std ;
  return cambio;
}
void P3_AumentarTercero(){
  if(gral_rotacion==360.0)
     gral_rotacion=gral_rotacion-360.0;
  minodo.entrada[1].ptr_pars_matriz->angulo=gral_rotacion+1.0; //ira desde 0.0 a -1.0 valor por teclado
  gral_rotacion++;
}
void P3_ReducirTercero(){
  if(gral_rotacion==360.0)
     gral_rotacion=gral_rotacion-360.0;
  minodo.entrada[1].ptr_pars_matriz->angulo=gral_rotacion-1.0; //ira desde 0.0 a -1.0 valor por teclado
  gral_rotacion--;
}

void P3_AumentarSegundo(){
 if(gral_escalado<1.25){
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[0]=gral_escalado+0.025; //ira desde 0.0 a -1.0 valor por teclado
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[1]=gral_escalado+0.025; //ira desde 0.0 a -1.0 valor por teclado
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[2]=gral_escalado+0.025; //ira desde 0.0 a -1.0 valor por teclado
     gral_escalado=gral_escalado+0.025;
   }
}
void P3_ReducirSegundo(){
 if(gral_escalado>1.0){
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[0]=gral_escalado-0.025; //ira desde 0.0 a -1.0 valor por teclado
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[1]=gral_escalado-0.025; //ira desde 0.0 a -1.0 valor por teclado
     minodoglobo.entrada[0].ptr_pars_matriz->vec[1].coo[2]=gral_escalado-0.025; //ira desde 0.0 a -1.0 valor por teclado
     gral_escalado=gral_escalado-0.025;
   }
}
void P3_AumentaPrimero(){
   if(gral_traslacion>-1.0){
     minodo.entrada[4].ptr_pars_matriz->vec[2].coo[1]=gral_traslacion-0.05; //ira desde 0.0 a -1.0 valor por teclado
     gral_traslacion=gral_traslacion-0.05;
   }
}
void P3_ReducirPrimero(){
   if(gral_traslacion<0.0){
     minodo.entrada[4].ptr_pars_matriz->vec[2].coo[1]=gral_traslacion+0.05; //ira desde 0.0 a -1.0 valor por teclado
     gral_traslacion=gral_traslacion+0.05;
   }
}

   

void P3_DibujarObjetoSentillo(int n ){
 if(n==0){ //cuerda
   glutSolidCylinder(0.04,2.0, 10, 10); 
 }else if (n==1){ //tierra
   glColor3fv(color[verde]);
   CrearObjetoRevolucion( &mallatierra ,20 );
   if(orden3==0){
      VerMallaEnAlambre( &mallatierra );
   }else if(orden3==1){
      VerMallaEnAjedrez( &mallatierra );
   }else if(orden3==3){
      VerMallaEnPuntos( &mallatierra );
   }else if(orden3==4 || orden3==2){ 
      VerMallaEnSolido( &mallatierra);
   }
 }else if(n==2){ //globo
   CrearObjetoRevolucion( &mallaglobo , 10 );
   if(orden3==0){
      VerMallaEnAlambre( &mallaglobo );
   }else if(orden3==2){
      VerMallaEnSolido( &mallaglobo );
   }else if(orden3==3){
      VerMallaEnPuntos( &mallaglobo );
   }else if(orden3==4 || orden3==1){ 
      VerMallaEnAjedrez( &mallaglobo);
   }
 }else if(n==3){ //cesta
   CrearObjetoRevolucion( &mallacesta , 4 );
   if(orden3==0){
      VerMallaEnAlambre( &mallacesta );
   }else if(orden3==1){
      VerMallaEnAjedrez( &mallacesta );
   }else if(orden3==2){
      VerMallaEnSolido( &mallacesta );
   }else if(orden3==3){
      VerMallaEnPuntos( &mallacesta );
   }else if(orden3==4){
      glColor3fv(color[negro]);
      VerMallaEnAlambre( &mallacesta );
      glColor3fv(color[marron]);
      VerMallaEnSolido( &mallacesta );
   }
 }
}

void P3_ComponerTrans( ParMatriz4f *ptr_pars_matriz){
  switch( ptr_pars_matriz -> tipo){
        case 0:  //rotacion
           glRotatef(  ptr_pars_matriz -> angulo, ptr_pars_matriz->vec[0].coo[0],ptr_pars_matriz->vec[0].coo[1],ptr_pars_matriz->vec[0].coo[2] );
        break;
        case 1:  //escalado
           glScalef(ptr_pars_matriz->vec[1].coo[0],ptr_pars_matriz->vec[1].coo[1],ptr_pars_matriz->vec[1].coo[2] );
        break;
        case 2:  //translacion
          glTranslatef(ptr_pars_matriz->vec[2].coo[0],ptr_pars_matriz->vec[2].coo[1],ptr_pars_matriz->vec[2].coo[2] );
        break; 
  }

}

void P3_NGE_Visualizar (NodoGE *nodo){
   glPushMatrix();
   for( unsigned i=0; i < nodo->entrada.size() ; i++){
      switch (nodo->entrada[i].tipo){
         case 0:  //sub-arbol
           P3_NGE_Visualizar (nodo->entrada[i].ptr_subesc);
         break;
         case 1:  //trasformacion
           glMultMatrixf(&nodo->entrada[i].ptr_matriz->coef[0][0]);  
         break;
         case 2:  //parametros
            P3_ComponerTrans(nodo->entrada[i].ptr_pars_matriz);
         break; 
         case 3:  //objeto_simple
           P3_DibujarObjetoSentillo(nodo->entrada[i].num_obj_sim);
         break;   
      }
   }
   glPopMatrix();
}


void P3_Inicializar( int argc,char *argv[] ){
   ply::read_vertices( "tierra.ply", mallatierra.vertices_ply );  //leemos el archivo ply
   ply::read_vertices( "globo.ply", mallaglobo.vertices_ply );  //leemos el archivo ply
   ply::read_vertices( "cesta.ply", mallacesta.vertices_ply );  //leemos el archivo ply

//tierra
   EntradaNGE e_tierra;
   e_tierra.tipo=3;
   e_tierra.num_obj_sim=1;
   minodo.entrada.push_back(e_tierra);

//rotacion globo, cuerdas, cesta
   EntradaNGE e_rot_gcc;  
   e_rot_gcc.tipo=2;
   m_r_gcc.tipo=0;
   m_r_gcc.vec[0].coo[0]=0.0;  
   m_r_gcc.vec[0].coo[1]=1.0;
   m_r_gcc.vec[0].coo[2]=0.0;
   m_r_gcc.angulo=gral_rotacion;  //ira desde 0 a 360 valor por teclado
   e_rot_gcc.ptr_pars_matriz=&m_r_gcc;
   minodo.entrada.push_back(e_rot_gcc);

//traslacion globo, cuerdas, cesta 
   EntradaNGE e_tra_gcc;
   e_tra_gcc.tipo=1;
   m_t_globo=matriz_traslacion(0.0, 0.0, 8.0);
   e_tra_gcc.ptr_matriz=&m_t_globo;
   minodo.entrada.push_back(e_tra_gcc);

//subescena del sesgado y el globo 
   EntradaNGE e_sub_globo;
   e_sub_globo.tipo=0;
   e_sub_globo.ptr_subesc=&minodoglobo;
   minodo.entrada.push_back(e_sub_globo);
//sesgado  
   EntradaNGE e_escalado;
   e_escalado.tipo=2;
   m_escalado.tipo=1;
   m_escalado.vec[1].coo[0]=gral_escalado;  //ira desde 1.0 hasta 1.25 valor por teclado
   m_escalado.vec[1].coo[1]=gral_escalado;  //ira desde 1.0 hasta 1.25 valor por teclado
   m_escalado.vec[1].coo[2]=gral_escalado;  //ira desde 1.0 hasta 1.25 valor por teclado
   e_escalado.ptr_pars_matriz=&m_escalado;
   minodoglobo.entrada.push_back(e_escalado);
//globo
   EntradaNGE e_globo;
   e_globo.tipo=3;
   e_globo.num_obj_sim=2;
   minodoglobo.entrada.push_back(e_globo);


//traslacion cuerdas, cesta 
   EntradaNGE e_tras_cc; 
   e_tras_cc.tipo=2;
   m_t_cc.tipo=2;
   m_t_cc.vec[2].coo[0]=0.0;  
   m_t_cc.vec[2].coo[1]=gral_traslacion;  //ira desde 0.0 a -1.0 valor por teclado
   m_t_cc.vec[2].coo[2]=0.0;
   e_tras_cc.ptr_pars_matriz=&m_t_cc;
   minodo.entrada.push_back(e_tras_cc);


//cesta
   EntradaNGE e_cesta;
   e_cesta.tipo=3;
   e_cesta.num_obj_sim=3;
   minodo.entrada.push_back(e_cesta);

//rotacion cuerdas 
   EntradaNGE e_rot_cuerdas;
   e_rot_cuerdas.tipo=1;
   m_r_cuerdas=matriz_rotacion(90.0,1.0,0.0,0.0);
   e_rot_cuerdas.ptr_matriz=&m_r_cuerdas;
   minodo.entrada.push_back(e_rot_cuerdas);

//subescena de la cuerda1 y su traslacion
   EntradaNGE e_sub_cuerda1;
   e_sub_cuerda1.tipo=0;
   e_sub_cuerda1.ptr_subesc=&minodocuerda1;
   minodo.entrada.push_back(e_sub_cuerda1);
//traslacion  cuerda1
   EntradaNGE e_tra_c1;
   e_tra_c1.tipo=1;
   m_t_c1=matriz_traslacion(-0.9,0.0,0.0);
   e_tra_c1.ptr_matriz=&m_t_c1;
   minodocuerda1.entrada.push_back(e_tra_c1);
//cuerda1
   EntradaNGE e_cuerda1;
   e_cuerda1.tipo=3;
   e_cuerda1.num_obj_sim=0;  //0--> cuerda
   minodocuerda1.entrada.push_back(e_cuerda1);

//subescena de la cuerda2 y su traslacion
   EntradaNGE e_sub_cuerda2;
   e_sub_cuerda2.tipo=0;
   e_sub_cuerda2.ptr_subesc=&minodocuerda2;
   minodo.entrada.push_back(e_sub_cuerda2);
//traslacion  cuerda2
   EntradaNGE e_tra_c2;
   e_tra_c2.tipo=1;
   m_t_c2=matriz_traslacion(0.9,0.0,0.0);
   e_tra_c2.ptr_matriz=&m_t_c2;
   minodocuerda2.entrada.push_back(e_tra_c2);
//cuerda2
   EntradaNGE e_cuerda2;
   e_cuerda2.tipo=3;
   e_cuerda2.num_obj_sim=0;  //0--> cuerda
   minodocuerda2.entrada.push_back(e_cuerda2);

//subescena de la cuerda3 y su traslacion
   EntradaNGE e_sub_cuerda3;
   e_sub_cuerda3.tipo=0;
   e_sub_cuerda3.ptr_subesc=&minodocuerda3;
   minodo.entrada.push_back(e_sub_cuerda3);
//traslacion  cuerda3
   EntradaNGE e_tra_c3;
   e_tra_c3.tipo=1;
   m_t_c3=matriz_traslacion(0.0,-0.9,0.0);
   e_tra_c3.ptr_matriz=&m_t_c3;
   minodocuerda3.entrada.push_back(e_tra_c3);
//cuerda3
   EntradaNGE e_cuerda3;
   e_cuerda3.tipo=3;
   e_cuerda3.num_obj_sim=0;  //0--> cuerda
   minodocuerda3.entrada.push_back(e_cuerda3);


//subescena de la cuerda4 y su traslacion
   EntradaNGE e_sub_cuerda4;
   e_sub_cuerda4.tipo=0;
   e_sub_cuerda4.ptr_subesc=&minodocuerda4;
   minodo.entrada.push_back(e_sub_cuerda4);
//traslacion  cuerda4
   EntradaNGE e_tra_c4;
   e_tra_c4.tipo=1;
   m_t_c4=matriz_traslacion(0.0,0.9,0.0);
   e_tra_c4.ptr_matriz=&m_t_c4;
   minodocuerda4.entrada.push_back(e_tra_c4);
//cuerda4
   EntradaNGE e_cuerda4;
   e_cuerda4.tipo=3;
   e_cuerda4.num_obj_sim=0;  //0--> cuerda
   minodocuerda4.entrada.push_back(e_cuerda4);
}


void P3_DibujarObjetos( ) {
   glEnableClientState( GL_VERTEX_ARRAY );
   P3_NGE_Visualizar (&minodo);
}
