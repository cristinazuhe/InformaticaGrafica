#ifndef LATA_HPP
#define LATA_HPP
#include "fuenteluz.hpp"
#include "operacionesmalla.hpp"

// Clase LataCocaCola
class LataCocaCola : public Material {
   public:
   MallaTVT mallalatacuerpo;
   MallaTVT mallalatainf;
   MallaTVT mallalatasup;
   Material materiallata;
   Material materialtapas;
   public:
   LataCocaCola();
   void CargarTexturaLata();
   void VerLataEnPlano();
   void VerLataEnSuave();
} ;


#endif

