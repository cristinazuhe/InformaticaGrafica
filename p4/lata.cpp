
#include <GL/glut.h>
#include "error-ogl.hpp"
#include "tuplas.hpp"   
#include <vector>
#include "file_ply_stl.hpp"
#include <iostream>
#include <math.h>
#include "fuenteluz.hpp"
#include "lata.hpp"
#include "operacionesmalla.hpp"
#include "grafoescena.hpp"
#include "jpg_imagen.hpp"
using namespace std;

LataCocaCola::LataCocaCola(){
 ply::read_vertices( "lata-pcue.ply", mallalatacuerpo.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion2( &mallalatacuerpo , 15.0, false);
 CrearNormalesCaras(&mallalatacuerpo);
 CrearNormalesVertices(&mallalatacuerpo);

 ply::read_vertices( "lata-pinf.ply", mallalatainf.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion2( &mallalatainf , 15.0,true );
 CrearNormalesCaras(&mallalatainf);
 CrearNormalesVertices(&mallalatainf);

 ply::read_vertices( "lata-psup.ply", mallalatasup.vertices_ply );  //leemos el archivo ply
 CrearObjetoRevolucion2( &mallalatasup , 15.0,false );
 CrearNormalesCaras(&mallalatasup);
 CrearNormalesVertices(&mallalatasup);
}

void LataCocaCola::CargarTexturaLata(){
   materiallata.AsociarTextura("text-lata-1.jpg");
   materiallata.ModoGeneracion(0);
   materialtapas.text == NULL;

   Tupla3f n_c_especular(1.0,1.0,1.0);
   materiallata.ModificarEspecular(n_c_especular);
   materialtapas.ModificarEspecular(n_c_especular);
   Tupla3f n_c_emision(0.0,0.0,0.0);
   materiallata.ModificarEmision(n_c_emision);
   materialtapas.ModificarEmision(n_c_emision);
   Tupla3f n_difuso(1.0,1.0,1.0);
   materiallata.ModificarDifuso(n_difuso);
   materialtapas.ModificarDifuso(n_difuso);
   materiallata.ModificarExponente(1.5);
}

void LataCocaCola::VerLataEnPlano(){
    materialtapas.activar();
    VerISPlano( &mallalatainf);   
    VerISPlano( &mallalatasup);
    materiallata.activar();
    VerISPlano( &mallalatacuerpo);
}
void LataCocaCola::VerLataEnSuave(){
    materialtapas.activar();
    VerISSuave( &mallalatainf);   
    VerISSuave( &mallalatasup);
    materiallata.activar();
    VerISSuave( &mallalatacuerpo);
}
