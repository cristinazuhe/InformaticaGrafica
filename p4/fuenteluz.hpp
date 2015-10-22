#ifndef IG_FUENTELUZ_HPP
#define IG_FUENTELUZ_HPP
#include "jpg_imagen.hpp"


//***************************************************************************************************************************
// clase fuenteluz.
class FuenteLuz{
   private: 
   float longi,lati;  		//angulos de rotacion
   Tupla3f colores[3]; 		//0--> ambiental, 1-->difuso, 2--> especular
   Tupla4f posvec;            
   bool posicional;
  
   public:
   FuenteLuz() ; 
   void ModificarValores(float ini_longi, float ini_lati, Tupla3f p_colores[3],Tupla4f ini_posvec,bool fuenteposicional ) ; 
   void Activar(int id_luz) ; 
} ;


//***************************************************************************************************************************
//clase textura
class Textura{
   public: 
   GLuint identificador_textura;
   jpg::Imagen *img;              //puntero a imagen
   unsigned mgct;                 //0--> desactivado, 1-->objeto, 2->camara
   GLfloat cs[4],ct[4]; 
  
   public:
   Textura();
   // carga una imagen de textura e inicializa los atributos de la textura a valores por defecto.
   void CargarTextura( const std::string & nombreArchivoJPG ) ; 
   //activa la textura
   void Activar( ) ; 
   // libera la memoria dinámica usada por la textura, si hay alguna
   ~Textura() ;
};


//***************************************************************************************************************************
//clase material
class Material {
   public: 
   Textura * text ;         
   float exponente;
   Tupla3f color[4];  //0-->emision , 1--> ambiental , 2-> difusa, 3-->especular
   public:
   Material() ;     
   ~Material() ; 
   void AsociarTextura( const std::string & nombreArchivoJPG ) ;
   void activar() ;
   void ModificarAmbiental(Tupla3f nuevocolor);
   void ModificarDifuso(Tupla3f nuevocolor);
   void ModificarEspecular(Tupla3f nuevocolor);
   void ModificarEmision(Tupla3f nuevocolor);
   void ModificarExponente(float nuevoexponente);
   void ModoGeneracion(int nuevo_mgct);
} ;
#endif
