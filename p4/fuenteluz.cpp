#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   
#include "fuenteluz.hpp"
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>


/*****
*** Constructor de fuente de luz. Crea una luz posicional,
*** con colores por defecto negros para todas las componentes
*****/
FuenteLuz::FuenteLuz( ) {
   posicional=true;
   longi  = 0.0;
   lati   = 0.0;  
   colores[0] = Tupla3f (0.0,0.0,0.0) ;
   colores[1] = Tupla3f (0.0,0.0,0.0) ;
   colores[2] = Tupla3f (0.0,0.0,0.0) ;
   posvec = Tupla4f {0.0,0.0,1.0,0.0};  
}

/*****
*** Modificamos los valores de una fuente de luz.
*****/
void FuenteLuz::ModificarValores(float ini_longi, float ini_lati, Tupla3f p_colores[3], Tupla4f ini_posvec, bool fuenteposicional ) {
   posicional=fuenteposicional;
   longi  = ini_longi;
   lati   = ini_lati;
   colores[0] = p_colores[0] ;
   colores[1] = p_colores[1] ;
   colores[2] = p_colores[2] ; 
   posvec=ini_posvec;
} 

/*****
*** Activamos una fuente de luz. 
*** Activa la fuente de luz que se le pasa como parámetro. 
*** Si la fuente de luz es direccional, tenemos en cuenta longitud y latidud.
*** Asignamos los colores y la posición de la fuente de luz que se activa.
*****/
void FuenteLuz::Activar(int id_luz){
   glEnable(GL_LIGHT0+id_luz);			
   glMatrixMode( GL_MODELVIEW);
   glPushMatrix();
   if(!posicional){
      glRotatef(longi, 0.0,1.0,0.0);
      glRotatef(lati,-1.0,0.0,0.0);
   }
      glLightfv(GL_LIGHT0+id_luz, GL_AMBIENT, &colores[0].coo[0]);
      glLightfv(GL_LIGHT0+id_luz, GL_DIFFUSE, &colores[1].coo[0]);
      glLightfv(GL_LIGHT0+id_luz, GL_SPECULAR, &colores[2].coo[0]);
      glLightfv(GL_LIGHT0+id_luz, GL_POSITION, &posvec.coo[0]);
   glPopMatrix();
}






//**************************************************************************************************************

/*****
*** Constructor de textura. 
*** No disponemos de imagen inicial, luego el puntero de imagen "es nulo".
*** Generación automática de coordenadas de textura.(s proporcional a coordenada X, t proporcional a coordenada Y)
*****/
Textura::Textura(){
   img=NULL;
   mgct=2;    //por defecto cámara
   for (int i=0;i<4 ; i++){
      cs[i]=0.0;
      ct[i]=0.0;
   }
   cs[0]=1.0;
   ct[1]=1.0;
}

/*****
*** Cargamos la textura. 
*** En el puntero a imagen cargamos la imagen que pasamos por parámetro.
*** Creamos un identificador de textura y le asociamos la imagen que cargamos.
*****/
void Textura::CargarTextura( const std::string & nombreArchivoJPG ){
     img = new jpg::Imagen(nombreArchivoJPG); 
     //Creamos identificador de textura
     glGenTextures(1, &identificador_textura);
     //La seleccionamos como la activa para definir sus propiedades
     glBindTexture(GL_TEXTURE_2D, identificador_textura);
     //Cargamos la imagen 
     gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,img->tamX(),img->tamY(),GL_RGB,GL_UNSIGNED_BYTE,img->leerPixels());  
}


/*****
*** Activa el uso de texturas y la textura concreta
*** Configura la generación automática de coordenadas de textura, de acuerdo a los valores de los atributos de la instancia
*****/
void Textura::Activar(){
    glEnable(GL_TEXTURE_2D);
    //selecciona la textura
    glBindTexture(GL_TEXTURE_2D, identificador_textura);
    //Selección de texels
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (mgct != 0){	//si buscamos generación automática de coordenadas de textura
       //activar generación automática de coordenadas de textura
        glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	if (mgct == 1){	//objeto		
		//usamos funciones lineales para la generacion automatica
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		// especificamos los coeficientes de las funciones
		glTexGenfv(GL_S, GL_OBJECT_PLANE, cs);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, ct);
    	}
	else if (mgct == 2){ //camara
		//usamos funciones lineales para la generacion automatica
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		// especificamos los coeficientes de las funciones
		glTexGenfv(GL_S, GL_EYE_PLANE, cs);
		glTexGenfv(GL_T, GL_EYE_PLANE, ct);
	}
    }else {
	//desactivar generación automática de coordenadas de textura
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
    }   
}

/*****
*** Destructor de textura. 
*****/
Textura::~Textura() {
   if ( img != NULL ){  
	   delete img;
       img = NULL ;
   }
}




//*****************************************************************************************
/*****
*** Constructor de material
*** No disponemos de textura inicial, luego el puntero de textura "es nulo".
*** Asignamos valores de color negros.
*****/
Material::Material() {
   text=NULL;
   exponente=0.0;
   color[0]={0.0,0.0,0.0};//emi
   color[1]={0.0,0.0,0.0};//amb
   color[2]={0.0,0.0,0.0};//dif
   color[3]={0.0,0.0,0.0};//esp
}

/*****
*** Creamos textura del material. Asociamos a esa textura la imagen que pasa por parámetro.
*****/
void Material::AsociarTextura( const std::string & nombreArchivoJPG ) {
   text= new Textura() ;
   text->CargarTextura( nombreArchivoJPG ); 
}

/*****
*** Cambiamos el modo de generacion de coordenadas de textura de la textura asociada al material
*****/
void Material::ModoGeneracion(int nuevo_mgct) {
   if(text!=NULL)
      text->mgct=nuevo_mgct;
}

/*****
*** Activamos el material. 
*** Si disponemos de textura, también la activamos.
*****/
void Material::activar(){
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
 
  //activar visualización de sólidos  para caras delanteras y traseras
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   float color_emision[4]={color[0].coo[0],color[0].coo[1],color[0].coo[2],1.0};
   float color_ambiental[4]={color[1].coo[0],color[1].coo[1],color[1].coo[2],1.0};   
   float color_difusa[4]={color[2].coo[0],color[2].coo[1],color[2].coo[2],1.0};  
   float color_especular[4]={color[3].coo[0],color[3].coo[1],color[3].coo[2],1.0};
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color_emision);
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color_ambiental);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_difusa);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color_especular);
   glMaterialf(GL_FRONT, GL_SHININESS, exponente);	
   //ACTIVA LA TEXTURA
   if (text != NULL){
     text->Activar();
   } 
}

/*****
*** El color ambiental del material será el que pasamos por parámetro
*****/
void Material::ModificarAmbiental(Tupla3f nuevocolor){
   color[1].coo[0]=nuevocolor.coo[0];
   color[1].coo[1]=nuevocolor.coo[1];
   color[1].coo[2]=nuevocolor.coo[2];
}

/*****
*** El color difuso del material será el que pasamos por parámetro
*****/
void Material::ModificarDifuso(Tupla3f nuevocolor){
   color[2].coo[0]=nuevocolor.coo[0];
   color[2].coo[1]=nuevocolor.coo[1];
   color[2].coo[2]=nuevocolor.coo[2];
}

/*****
*** El color especular del material será el que pasamos por parámetro
*****/
void Material::ModificarEspecular(Tupla3f nuevocolor){
   color[3].coo[0]=nuevocolor.coo[0];
   color[3].coo[1]=nuevocolor.coo[1];
   color[3].coo[2]=nuevocolor.coo[2];
}

/*****
*** El color de emisión del material será el que pasamos por parámetro
*****/
void Material::ModificarEmision(Tupla3f nuevocolor){
   color[0].coo[0]=nuevocolor.coo[0];
   color[0].coo[1]=nuevocolor.coo[1];
   color[0].coo[2]=nuevocolor.coo[2];
}

/*****
*** El exponente de brillo será el que pasamos por parámetro.
*****/
void Material::ModificarExponente(float nuevoexponente){
   exponente=nuevoexponente;
}

/*****
*** Destructor de material
*****/
Material::~Material() {      
   if ( text != NULL ){  
	  delete text ;
          text = NULL ;
   }
}
