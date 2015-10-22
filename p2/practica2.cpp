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
   //si el primero están en el eje lo quitamos de los vértices (posteriormente se añade) 
   if(mimallav.vertices_ply[0] == 0.0){ 
     for (int i=0; i< mimallav.vertices_ply.size()-3; i++){
       mimallav.vertices_ply[i] = mimallav.vertices_ply[i+3];
     }
     mimallav.vertices_ply.pop_back();
     mimallav.vertices_ply.pop_back();
     mimallav.vertices_ply.pop_back();
   }
   //si el ultimo están en el eje lo quitamos de los vértices (posteriormente se añade) 
   if(mimallav.vertices_ply[mimallav.vertices_ply.size()-3 ] == 0.0){ 
     mimallav.vertices_ply.pop_back();
     mimallav.vertices_ply.pop_back();
     mimallav.vertices_ply.pop_back();
   }



   //crear perfiles del sólido
   double n_perfiles=strtod(argv[3],NULL); //leer el numero de perfiles a realizar
   double angulo = (2*PI)/n_perfiles;  //calculamos el ángulo de rotación 
   //obtenemos el numero de vertices de un perfil
   mimallav.num_vertices = mimallav.vertices_ply.size();
   double n_v_perfil=(mimallav.num_vertices)/3;
   for (int j=0; j< n_perfiles; j++){
       for( int i=0; i< mimallav.num_vertices ; i=i+3){
           Tupla3f vertice(cos(angulo)*mimallav.vertices_ply[i]+sin(angulo)*mimallav.vertices_ply[i+2],
                       mimallav.vertices_ply[i+1],
                       -sin(angulo)*mimallav.vertices_ply[i]+cos(angulo)*mimallav.vertices_ply[i+2]);  //cada 3 float nos dan un vertice
            mimallav.vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
       }
       angulo=angulo+(2*PI)/n_perfiles;
   }
   mimallav.num_vertices=(mimallav.num_vertices)*n_perfiles;



   //crear caras del sólido.
   mimallav.num_caras=(3*((n_v_perfil-1)*(n_perfiles)))*2;
   Tupla3i carad;
   Tupla3i carai;
     for(int k=0; k < n_perfiles-1 ; k++){ 
       for(int i = 0; i < ( n_v_perfil-1) ; i++){  //caras formadas por dos perfiles del sólido
         //cara derecha
         carad.idx[0]=i+(k*n_v_perfil);
         carad.idx[1]=i+n_v_perfil+(k*n_v_perfil);
         carad.idx[2]=i+n_v_perfil + 1+(k*n_v_perfil);
         mimallav.caras.push_back(carad);
         //cara izquierda
         carai.idx[0]=i+(k*n_v_perfil);
         carai.idx[1]=i+n_v_perfil + 1+(k*n_v_perfil);
         carai.idx[2]=i + 1+(k*n_v_perfil);
         mimallav.caras.push_back(carai);
       }
      }
     //cerramos el sólido
       for(int i = 0; i < ( n_v_perfil-1) ; i++){  
         //cara derecha
         carad.idx[0]=i + n_perfiles*n_v_perfil - n_v_perfil;
         carad.idx[1]=i;
         carad.idx[2]=i+1;
         mimallav.caras.push_back(carad);
         //cara izquierda
         carai.idx[0]=i+1;
         carai.idx[1]=i + 1 + n_perfiles*n_v_perfil -n_v_perfil;
         carai.idx[2]=i + n_perfiles*n_v_perfil -n_v_perfil;
         mimallav.caras.push_back(carai);
        }



      //Creamos la tapa inferior
      //añadimos el vertice para la tapa inferior
      Tupla3f verticei(0.0, mimallav.vertices_ply[1], mimallav.vertices_ply[2]);  
      mimallav.vertices.push_back(verticei);  //en el vector de tuplas metemos los vertices generados  
      mimallav.num_vertices= (mimallav.num_vertices)+3;
      //añadimos las caras de la tapa inferior   
      Tupla3i cara;
      mimallav.num_caras= mimallav.num_caras+ (n_perfiles*3);
      for(int i=0; i< ( n_perfiles-1); i++){
         cara.idx[0]=(n_v_perfil*n_perfiles);
         cara.idx[1]=n_v_perfil+(i*n_v_perfil);
         cara.idx[2]=i*n_v_perfil;
         mimallav.caras.push_back(cara);
      }
      cara.idx[0]=(n_v_perfil*n_perfiles);
      cara.idx[1]=0;
      cara.idx[2]=(n_v_perfil*(n_perfiles-1));
      mimallav.caras.push_back(cara);



      //Creamos la tapa superior
      //añadimos el vertice para la tapa superior
      Tupla3f vertice(0.0, mimallav.vertices_ply[(n_v_perfil-1)*3 +1], mimallav.vertices_ply[(n_v_perfil-1)*3 +2]);  
      mimallav.vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
      mimallav.num_vertices= (mimallav.num_vertices)+3;
      //añadimos las caras de la tapa superior  
      mimallav.num_caras= mimallav.num_caras+ (n_perfiles*3);
      for(int i=0; i< ( n_perfiles -1); i++){
         cara.idx[0]=(i*n_v_perfil)+n_v_perfil -1; 
         cara.idx[1]=2*n_v_perfil+(i*n_v_perfil)-1;
         cara.idx[2]=(n_v_perfil*n_perfiles) + 1;
         mimallav.caras.push_back(cara);
      }
      cara.idx[0]=(n_v_perfil*(n_perfiles-1)) + n_v_perfil -1;  
      cara.idx[1]=n_v_perfil-1;
      cara.idx[2]=(n_v_perfil*n_perfiles) +1 ;
      mimallav.caras.push_back(cara);



      //calcular las normales de las caras
       int indice1, indice2, indice3;
       for( int i=0; i< mimallav.num_caras ; i=i+3){
           indice1=mimallav.caras[(i/3)].idx[0];
           indice2=mimallav.caras[(i/3)].idx[1];
           indice3=mimallav.caras[(i/3)].idx[2];
           Tupla3f aux1(mimallav.vertices[indice1].coo[0]-mimallav.vertices[indice2].coo[0],
                        mimallav.vertices[indice1].coo[1]-mimallav.vertices[indice2].coo[1],
                        mimallav.vertices[indice1].coo[2]-mimallav.vertices[indice2].coo[2]); //vector de vertice 2 a vertice 1
           Tupla3f aux2(mimallav.vertices[indice3].coo[0]-mimallav.vertices[indice2].coo[0],
                        mimallav.vertices[indice3].coo[1]-mimallav.vertices[indice2].coo[1],
                        mimallav.vertices[indice3].coo[2]-mimallav.vertices[indice2].coo[2]); //vector de vertice 2 a vertice 3
           Tupla3f normal(aux2.coo[Y]*aux1.coo[Z] - aux2.coo[Z]*aux1.coo[Y],
                          aux2.coo[Z]*aux1.coo[X] - aux2.coo[X]*aux1.coo[Z],
                          aux2.coo[X]*aux1.coo[Y] - aux2.coo[Y]*aux1.coo[X]); //producto vectorial de los vectores aux1 y aux2
	   //normalizamos el vector normal.
           float deno=sqrt((pow(normal.coo[X],2.0)) + (pow(normal.coo[Y],2.0)) + (pow(normal.coo[Z],2.0)));
           normal.coo[0]=(normal.coo[0])/deno;
           normal.coo[1]=(normal.coo[1])/deno;
           normal.coo[2]=(normal.coo[2])/deno;
           Tupla3f bari((mimallav.vertices[indice1].coo[0] + mimallav.vertices[indice2].coo[0] + mimallav.vertices[indice3].coo[0])/3.0,
                        (mimallav.vertices[indice1].coo[1] + mimallav.vertices[indice2].coo[1] + mimallav.vertices[indice3].coo[1])/3.0,
                        (mimallav.vertices[indice1].coo[2] + mimallav.vertices[indice2].coo[2] + mimallav.vertices[indice3].coo[2])/3.0);
           mimallav.normales_car.push_back(bari);  //en el vector de tuplas metemos los vertices generados
           mimallav.normales_car.push_back(normal+(bari));  //en el vector de tuplas metemos los vertices generados
       }




       //calcular las normales de los vertices  
       for( int i=0; i< (mimallav.num_vertices)/3; i++){
          Tupla3f inicio(0.0,0.0,0.0);
          mimallav.normales_ver.push_back(mimallav.vertices[i]);
          mimallav.normales_ver.push_back(inicio);  //en este es donde represento la normal
       }
       for( int i=0; i< mimallav.num_caras ; i=i+3){ 
           indice1=mimallav.caras[(i/3)].idx[0];
           indice2=mimallav.caras[(i/3)].idx[1];
           indice3=mimallav.caras[(i/3)].idx[2];
           mimallav.normales_ver[(2*indice1)+1]=(mimallav.normales_ver[(2*indice1)+1]) +
                                                (mimallav.normales_car[2*(i/3)+1]-mimallav.normales_car[2*(i/3)]);
           mimallav.normales_ver[(2*indice2)+1]=(mimallav.normales_ver[(2*indice2)+1]) +
                                                (mimallav.normales_car[2*(i/3)+1]-mimallav.normales_car[2*(i/3)]);
           mimallav.normales_ver[(2*indice3)+1]=(mimallav.normales_ver[(2*indice3)+1]) + 
                                                (mimallav.normales_car[2*(i/3)+1]-mimallav.normales_car[2*(i/3)]);
       }
      //normalizacion
      for( int i=0; i< (mimallav.num_vertices)/3; i++){ 
           float deno=sqrt((pow(mimallav.normales_ver[(2*i)+1].coo[0],2.0)) + 
                           (pow(mimallav.normales_ver[(2*i)+1].coo[1],2.0)) + 
                           (pow(mimallav.normales_ver[(2*i)+1].coo[2],2.0)));
           mimallav.normales_ver[(2*i)+1].coo[0]=(mimallav.normales_ver[(2*i)+1].coo[0])/deno;
           mimallav.normales_ver[(2*i)+1].coo[1]=(mimallav.normales_ver[(2*i)+1].coo[1])/deno;
           mimallav.normales_ver[(2*i)+1].coo[2]=(mimallav.normales_ver[(2*i)+1].coo[2])/deno;
           mimallav.normales_ver[(2*i)+1]=mimallav.normales_ver[(2*i)+1] + mimallav.normales_ver[(2*i)];
       }

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


//pintamos el sólido con color de las normales de los vertices
void P2_PintarNormalesVertices( MallaTVT *malla )  { 
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int iv;	
   glBegin(GL_TRIANGLES);		
   for(int i = 0; i < mimallav.caras.size(); i++){
        for(int j = 0; j < 3; j++){
        iv = mimallav.caras[i].idx[j];
        glColor3f(fabs((mimallav.normales_ver[2*(iv)+1].coo[X])-(mimallav.normales_ver[2*(iv)].coo[X])),
                  fabs((mimallav.normales_ver[2*(iv)+1].coo[Y])-(mimallav.normales_ver[2*(iv)].coo[Y])),
                  fabs((mimallav.normales_ver[2*(iv)+1].coo[Z])-(mimallav.normales_ver[2*(iv)].coo[Z])));
	  
           glVertex3f(mimallav.vertices[iv].coo[X], mimallav.vertices[iv].coo[Y], mimallav.vertices[iv].coo[Z]);            
	}
   }
   glEnd();
}


//pintamos el sólido con color de las normales de las caras
void P2_PintarNormalesCaras( MallaTVT *malla )  { 
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int iv;	
   glBegin(GL_TRIANGLES);		
   for(int i = 0; i < mimallav.caras.size(); i++){
        glColor3f(fabs((mimallav.normales_car[2*(i)+1].coo[X])-(mimallav.normales_car[2*(i)].coo[X])),
                  fabs((mimallav.normales_car[2*(i)+1].coo[Y])-(mimallav.normales_car[2*(i)].coo[Y])),
                  fabs((mimallav.normales_car[2*(i)+1].coo[Z])-(mimallav.normales_car[2*(i)].coo[Z]))); 
	for(int j = 0; j < 3; j++){
           iv = mimallav.caras[i].idx[j];
           glVertex3f(mimallav.vertices[iv].coo[X], mimallav.vertices[iv].coo[Y], mimallav.vertices[iv].coo[Z]);           
	}
   }
   glEnd();
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
      P2_PintarNormalesVertices( &mimallav ) ;
    else if(orden2==5) 
      P2_PintarNormalesCaras( &mimallav ) ;
   
   if(activonormalcaras){
   //pintamos las normales de las caras
   glColor3f(1.0,0.0,0.0);
   glVertexPointer( 3, GL_FLOAT, 0, mimallav.normales_car[0].coo);
   glDrawArrays( GL_LINES , 0, (mimallav.num_caras/3)*2); //por cada cara tenemos dos vértices que nos dan la normal (el vertice baricentro y el vertice normal)
  }
 
   if(activonormalvertices){
   //normales de los vertices;
   glColor3f(0.0,1.0,0.0);
   glVertexPointer( 3, GL_FLOAT, 0, mimallav.normales_ver[0].coo);
   glDrawArrays( GL_LINES , 0, ((mimallav.num_vertices)/3)*2); 
   }

}
