#ifndef PEONES_HPP
#define PEONES_HPP
#include "fuenteluz.hpp"
#include "operacionesmalla.hpp"
#include "grafoescena.hpp"

// Clase peon1
class Peon1: public Material {
   protected:
   MallaTVT mallapeon1;
   NodoGE minodopeon1;
   Matriz4f m_t_peon1;            //para la traslacion del peon
   ParMatriz4f m_escalado_peones; //para el escalado de los peones
   Material materialpeon1;
   public:
   Peon1();
   void P4_NGE_VisualizarPlano (NodoGE *nodo);
   void P4_NGE_VisualizarSuave (NodoGE *nodo);
   void VerPeon1EnPlano();
   void VerPeon1EnSuave();
   void CargarTexturaPeon1();
} ;

//clase peon2
class Peon2 {
   protected:
   MallaTVT mallapeon2;
   NodoGE minodopeon2;
   Matriz4f m_t_peon2;
   ParMatriz4f m_escalado_peones; //para el escalado de los peones
   Material materialpeon2;
   public:
   Peon2();
   void Peon2_NGE_VisualizarSuave(NodoGE *nodo);
   void Peon2_NGE_VisualizarPlano(NodoGE *nodo);
   void VerPeon2EnPlano();
   void VerPeon2EnSuave();
} ;

//clase peon3
class Peon3 {
   protected:
   MallaTVT mallapeon3;
   NodoGE minodopeon3;
   Matriz4f m_t_peon3;
   ParMatriz4f m_escalado_peones; //para el escalado de los peones
   Material materialpeon3;
   public:
   Peon3();
   void Peon3_NGE_VisualizarSuave(NodoGE *nodo);
   void Peon3_NGE_VisualizarPlano(NodoGE *nodo);
   void VerPeon3EnPlano();
   void VerPeon3EnSuave();
} ;


#endif

