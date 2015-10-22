#include <GL/glut.h>

#include <GL/freeglut_ext.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "practica3.hpp"
#include "practica4.hpp"
#include "grafoescena.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>

void NGE_Visualizar (NodoGE *nodo){
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
         case 3:  //objeto_simple
           P3_DibujarObjetoSentillo(nodo->entrada[i].num_obj_sim);
         break;  
      }
   }
   glPopMatrix();
}


void ComponerTrans( ParMatriz4f *ptr_pars_matriz){
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
