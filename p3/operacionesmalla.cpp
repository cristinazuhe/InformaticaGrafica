
#include "operacionesmalla.hpp"
#include <GL/glut.h>

#define PI (3.141592653589793)

//********************************************************************************************
void VerMallaEnPuntos( MallaTVT *malla ){
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawArrays( GL_POINTS , 0, (malla->num_vertices)/3);   
}


//********************************************************************************************
void VerMallaEnAlambre( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //GL_POINT, GL_LINE, GL_FILL
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawElements( GL_TRIANGLES , malla->num_caras, GL_UNSIGNED_INT , malla->caras[0].idx );
}


//********************************************************************************************
void VerMallaEnSolido( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
   glDrawElements( GL_TRIANGLES , malla->num_caras, GL_UNSIGNED_INT , malla->caras[0].idx );
}


//********************************************************************************************
void VerMallaEnAjedrez( MallaTVT *malla ){
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int paridad=0;
   for( int i=0; i< (malla->num_caras)/3 ; i++){
      if(paridad==0){
         glColor3f(1.0,0.0,1.0);
         paridad=1;
      }else{
         glColor3f( 0.5, 0.0, 0.5 );
         paridad=0;
      }
      glVertexPointer( 3, GL_FLOAT, 0, malla->vertices[0].coo);
      glDrawElements( GL_TRIANGLES , 3 , GL_UNSIGNED_INT , malla->caras[i].idx );
   }
  }


//********************************************************************************************
//pintamos el sólido con color de las normales de los vertices
void PintarNormalesVertices( MallaTVT *malla )  { 
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int iv;	
   glBegin(GL_TRIANGLES);		
   for(int i = 0; i < malla->caras.size(); i++){
        for(int j = 0; j < 3; j++){
        iv = malla->caras[i].idx[j];
        glColor3f(fabs((malla->normales_ver[2*(iv)+1].coo[X])-(malla->normales_ver[2*(iv)].coo[X])),
                  fabs((malla->normales_ver[2*(iv)+1].coo[Y])-(malla->normales_ver[2*(iv)].coo[Y])),
                  fabs((malla->normales_ver[2*(iv)+1].coo[Z])-(malla->normales_ver[2*(iv)].coo[Z])));
	  
           glVertex3f(malla->vertices[iv].coo[X], malla->vertices[iv].coo[Y], malla->vertices[iv].coo[Z]);            
	}
   }
   glEnd();
}


//********************************************************************************************
//pintamos el sólido con color de las normales de las caras
void PintarNormalesCaras( MallaTVT *malla )  { 
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  //GL_POINT, GL_LINE, GL_FILL
   int iv;	
   glBegin(GL_TRIANGLES);		
   for(int i = 0; i < malla->caras.size(); i++){
        glColor3f(fabs((malla->normales_car[2*(i)+1].coo[X])-(malla->normales_car[2*(i)].coo[X])),
                  fabs((malla->normales_car[2*(i)+1].coo[Y])-(malla->normales_car[2*(i)].coo[Y])),
                  fabs((malla->normales_car[2*(i)+1].coo[Z])-(malla->normales_car[2*(i)].coo[Z]))); 
	for(int j = 0; j < 3; j++){
           iv = malla->caras[i].idx[j];
           glVertex3f(malla->vertices[iv].coo[X], malla->vertices[iv].coo[Y], malla->vertices[iv].coo[Z]);           
	}
   }
   glEnd();
}


//********************************************************************************************
void CrearObjetoRevolucion(MallaTVT *malla , int numero_perfiles){
//si el primero están en el eje lo quitamos de los vértices (posteriormente se añade) 
   if(malla->vertices_ply[0] == 0.0){ 
     for (int i=0; i< malla->vertices_ply.size()-3; i++){
       malla->vertices_ply[i] = malla->vertices_ply[i+3];
     }
     malla->vertices_ply.pop_back();
     malla->vertices_ply.pop_back();
     malla->vertices_ply.pop_back();
   }
   //si el ultimo están en el eje lo quitamos de los vértices (posteriormente se añade) 
   if(malla->vertices_ply[malla->vertices_ply.size()-3 ] == 0.0){ 
     malla->vertices_ply.pop_back();
     malla->vertices_ply.pop_back();
     malla->vertices_ply.pop_back();
   }

   //crear perfiles del sólido
   double n_perfiles=numero_perfiles; //leer el numero de perfiles a realizar
   double angulo = (2*PI)/n_perfiles;  //calculamos el ángulo de rotación 
   //obtenemos el numero de vertices de un perfil
   malla->num_vertices = malla->vertices_ply.size();
   double n_v_perfil=(malla->num_vertices)/3;
   for (int j=0; j< n_perfiles; j++){
       for( int i=0; i< malla->num_vertices ; i=i+3){
           Tupla3f vertice(cos(angulo)*malla->vertices_ply[i]+sin(angulo)*malla->vertices_ply[i+2],
                       malla->vertices_ply[i+1],
                       -sin(angulo)*malla->vertices_ply[i]+cos(angulo)*malla->vertices_ply[i+2]);  //cada 3 float nos dan un vertice
            malla->vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
       }
       angulo=angulo+(2*PI)/n_perfiles;
   }
   malla->num_vertices=(malla->num_vertices)*n_perfiles;


//crear caras del sólido.
   malla->num_caras=(3*((n_v_perfil-1)*(n_perfiles)))*2;
   Tupla3i carad;
   Tupla3i carai;
     for(int k=0; k < n_perfiles-1 ; k++){ 
       for(int i = 0; i < ( n_v_perfil-1) ; i++){  //caras formadas por dos perfiles del sólido
         //cara derecha
         carad.idx[0]=i+(k*n_v_perfil);
         carad.idx[1]=i+n_v_perfil+(k*n_v_perfil);
         carad.idx[2]=i+n_v_perfil + 1+(k*n_v_perfil);
         malla->caras.push_back(carad);
         //cara izquierda
         carai.idx[0]=i+(k*n_v_perfil);
         carai.idx[1]=i+n_v_perfil + 1+(k*n_v_perfil);
         carai.idx[2]=i + 1+(k*n_v_perfil);
         malla->caras.push_back(carai);
       }
      }
     //cerramos el sólido
       for(int i = 0; i < ( n_v_perfil-1) ; i++){  
         //cara derecha
         carad.idx[0]=i + n_perfiles*n_v_perfil - n_v_perfil;
         carad.idx[1]=i;
         carad.idx[2]=i+1;
         malla->caras.push_back(carad);
         //cara izquierda
         carai.idx[0]=i+1;
         carai.idx[1]=i + 1 + n_perfiles*n_v_perfil -n_v_perfil;
         carai.idx[2]=i + n_perfiles*n_v_perfil -n_v_perfil;
         malla->caras.push_back(carai);
        }


  //Creamos la tapa inferior
      //añadimos el vertice para la tapa inferior
      Tupla3f verticei(0.0, malla->vertices_ply[1], malla->vertices_ply[2]);  
      malla->vertices.push_back(verticei);  //en el vector de tuplas metemos los vertices generados  
      malla->num_vertices= (malla->num_vertices)+3;
      //añadimos las caras de la tapa inferior   
      Tupla3i cara;
      malla->num_caras= malla->num_caras+ (n_perfiles*3);
      for(int i=0; i< ( n_perfiles-1); i++){
         cara.idx[0]=(n_v_perfil*n_perfiles);
         cara.idx[1]=n_v_perfil+(i*n_v_perfil);
         cara.idx[2]=i*n_v_perfil;
         malla->caras.push_back(cara);
      }
      cara.idx[0]=(n_v_perfil*n_perfiles);
      cara.idx[1]=0;
      cara.idx[2]=(n_v_perfil*(n_perfiles-1));
      malla->caras.push_back(cara);



      //Creamos la tapa superior
      //añadimos el vertice para la tapa superior
      Tupla3f vertice(0.0, malla->vertices_ply[(n_v_perfil-1)*3 +1], malla->vertices_ply[(n_v_perfil-1)*3 +2]);  
      malla->vertices.push_back(vertice);  //en el vector de tuplas metemos los vertices generados
      malla->num_vertices= (malla->num_vertices)+3;
      //añadimos las caras de la tapa superior  
      malla->num_caras= malla->num_caras+ (n_perfiles*3);
      for(int i=0; i< ( n_perfiles -1); i++){
         cara.idx[0]=(i*n_v_perfil)+n_v_perfil -1; 
         cara.idx[1]=2*n_v_perfil+(i*n_v_perfil)-1;
         cara.idx[2]=(n_v_perfil*n_perfiles) + 1;
         malla->caras.push_back(cara);
      }
      cara.idx[0]=(n_v_perfil*(n_perfiles-1)) + n_v_perfil -1;  
      cara.idx[1]=n_v_perfil-1;
      cara.idx[2]=(n_v_perfil*n_perfiles) +1 ;
      malla->caras.push_back(cara);
}

void CrearNormalesCaras(MallaTVT *mimallav){
       //calcular las normales de las caras
       int indice1, indice2, indice3;
       for( int i=0; i< mimallav->num_caras ; i=i+3){
           indice1=mimallav->caras[(i/3)].idx[0];
           indice2=mimallav->caras[(i/3)].idx[1];
           indice3=mimallav->caras[(i/3)].idx[2];
           Tupla3f aux1(mimallav->vertices[indice1].coo[0]-mimallav->vertices[indice2].coo[0],
                        mimallav->vertices[indice1].coo[1]-mimallav->vertices[indice2].coo[1],
                        mimallav->vertices[indice1].coo[2]-mimallav->vertices[indice2].coo[2]); //vector de vertice 2 a vertice 1
           Tupla3f aux2(mimallav->vertices[indice3].coo[0]-mimallav->vertices[indice2].coo[0],
                        mimallav->vertices[indice3].coo[1]-mimallav->vertices[indice2].coo[1],
                        mimallav->vertices[indice3].coo[2]-mimallav->vertices[indice2].coo[2]); //vector de vertice 2 a vertice 3
           Tupla3f normal(aux2.coo[Y]*aux1.coo[Z] - aux2.coo[Z]*aux1.coo[Y],
                          aux2.coo[Z]*aux1.coo[X] - aux2.coo[X]*aux1.coo[Z],
                          aux2.coo[X]*aux1.coo[Y] - aux2.coo[Y]*aux1.coo[X]); //producto vectorial de los vectores aux1 y aux2
	   //normalizamos el vector normal.
           float deno=sqrt((pow(normal.coo[X],2.0)) + (pow(normal.coo[Y],2.0)) + (pow(normal.coo[Z],2.0)));
           normal.coo[0]=(normal.coo[0])/deno;
           normal.coo[1]=(normal.coo[1])/deno;
           normal.coo[2]=(normal.coo[2])/deno;
           Tupla3f bari((mimallav->vertices[indice1].coo[0] + mimallav->vertices[indice2].coo[0] + mimallav->vertices[indice3].coo[0])/3.0,
                        (mimallav->vertices[indice1].coo[1] + mimallav->vertices[indice2].coo[1] + mimallav->vertices[indice3].coo[1])/3.0,
                        (mimallav->vertices[indice1].coo[2] + mimallav->vertices[indice2].coo[2] + mimallav->vertices[indice3].coo[2])/3.0);
           mimallav->normales_car.push_back(bari);  //en el vector de tuplas metemos los vertices generados
           mimallav->normales_car.push_back(normal+(bari));  //en el vector de tuplas metemos los vertices generados
       }
}
void CrearNormalesVertices(MallaTVT *mimallav){
      //calcular las normales de los vertices 
       int indice1, indice2, indice3; 
       for( int i=0; i< (mimallav->num_vertices)/3; i++){
          Tupla3f inicio(0.0,0.0,0.0);
          mimallav->normales_ver.push_back(mimallav->vertices[i]);
          mimallav->normales_ver.push_back(inicio);  //en este es donde represento la normal
       }
       for( int i=0; i< mimallav->num_caras ; i=i+3){ 
           indice1=mimallav->caras[(i/3)].idx[0];
           indice2=mimallav->caras[(i/3)].idx[1];
           indice3=mimallav->caras[(i/3)].idx[2];
           mimallav->normales_ver[(2*indice1)+1]=(mimallav->normales_ver[(2*indice1)+1]) +
                                                (mimallav->normales_car[2*(i/3)+1]-mimallav->normales_car[2*(i/3)]);
           mimallav->normales_ver[(2*indice2)+1]=(mimallav->normales_ver[(2*indice2)+1]) +
                                                (mimallav->normales_car[2*(i/3)+1]-mimallav->normales_car[2*(i/3)]);
           mimallav->normales_ver[(2*indice3)+1]=(mimallav->normales_ver[(2*indice3)+1]) + 
                                                (mimallav->normales_car[2*(i/3)+1]-mimallav->normales_car[2*(i/3)]);
       }
      //normalizacion
      for( int i=0; i< (mimallav->num_vertices)/3; i++){ 
           float deno=sqrt((pow(mimallav->normales_ver[(2*i)+1].coo[0],2.0)) + 
                           (pow(mimallav->normales_ver[(2*i)+1].coo[1],2.0)) + 
                           (pow(mimallav->normales_ver[(2*i)+1].coo[2],2.0)));
           mimallav->normales_ver[(2*i)+1].coo[0]=(mimallav->normales_ver[(2*i)+1].coo[0])/deno;
           mimallav->normales_ver[(2*i)+1].coo[1]=(mimallav->normales_ver[(2*i)+1].coo[1])/deno;
           mimallav->normales_ver[(2*i)+1].coo[2]=(mimallav->normales_ver[(2*i)+1].coo[2])/deno;
           mimallav->normales_ver[(2*i)+1]=mimallav->normales_ver[(2*i)+1] + mimallav->normales_ver[(2*i)];
       }

}


