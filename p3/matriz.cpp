#include <GL/glut.h>

#include <GL/freeglut_ext.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   // Tupla3f, Tupla4f, Tupla3i
#include "matriz.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>

#define PI (3.141592653589793)

//********************************************************************************************
Matriz4f matriz_ide(){
Matriz4f matriz_ide;

for(int i=0; i<4; i++){
   for(int j=0; j<4 ; j++){
      if(i!=j){
        matriz_ide.coef[i][j]=0.0;
      }else{
        matriz_ide.coef[i][j]=1.0;
      }
   }
}
return matriz_ide; 
} 

//********************************************************************************************
Matriz4f matriz_rotacion(const float ang_gra, const float ex, const float ey, const float ez){
Matriz4f matriz_rota;
double angulo = (ang_gra*PI)/180.0;  
float c=cos(angulo);
float s=sin(angulo);
float hx= (1-c)*ex;
float hy= (1-c)*ey;
float hz= (1-c)*ez;

matriz_rota.coef[0][0]=(hx*ex + c);
matriz_rota.coef[1][0]=(hx*ey - s*ez);
matriz_rota.coef[2][0]=(hx*ez + s*ey);
matriz_rota.coef[3][0]=0.0;

matriz_rota.coef[0][1]=(hy*ex + s*ez);
matriz_rota.coef[1][1]=(hy*ey + c);
matriz_rota.coef[2][1]=(hy*ez - s*ex);
matriz_rota.coef[3][1]=0.0;

matriz_rota.coef[0][2]=(hz*ex - s*ey);
matriz_rota.coef[1][2]=(hz*ey + s*ex);
matriz_rota.coef[2][2]=(hz*ez + c);
matriz_rota.coef[3][2]=0.0;

matriz_rota.coef[0][3]=0.0;
matriz_rota.coef[1][3]=0.0;
matriz_rota.coef[2][3]=0.0;
matriz_rota.coef[3][3]=1.0;

return matriz_rota; 
}

//********************************************************************************************
Matriz4f matriz_escalado(const float sx, const float sy, const float sz){
Matriz4f matriz_esca;

matriz_esca.coef[0][0]=sx;
matriz_esca.coef[1][1]=sy;
matriz_esca.coef[2][2]=sz;
matriz_esca.coef[3][3]=1.0;

for(int i=0; i<4; i++){
   for(int j=0; j<4 ; j++){
      if(i!=j){
        matriz_esca.coef[i][j]=0.0;
      }
   }
}

return matriz_esca; 
}

//********************************************************************************************
Matriz4f matriz_traslacion(const float dx, const float dy, const float dz){
Matriz4f matriz_tras=matriz_ide();

matriz_tras.coef[3][0]=dx;
matriz_tras.coef[3][1]=dy;
matriz_tras.coef[3][2]=dz;

return matriz_tras; 
}

//********************************************************************************************
Matriz4f matriz_multiplicacion(const Matriz4f & izq, const Matriz4f & der){
Matriz4f matriz_multi;

for(int i=0; i<4; i++){
   for(int j=0; j<4 ; j++){
        matriz_multi.coef[i][j]=0.0;
           for(int k=0; k<4 ; k++){
                matriz_multi.coef[i][j]=matriz_multi.coef[i][j]+ izq.coef[k][i]*der.coef[j][k];
           }
   }
}

return matriz_multi; 
}
