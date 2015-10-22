#ifndef IG_MATRIZ_HPP
#define IG_MATRIZ_HPP



struct Matriz4f{
   float coef[4][4];
};

Matriz4f matriz_ide();
Matriz4f matriz_rotacion(const float ang_gra, const float ex, const float ey, const float ez);
Matriz4f matriz_escalado(const float sx, const float sy, const float sz);
Matriz4f matriz_traslacion(const float dx, const float dy, const float dz);
Matriz4f matriz_multiplicacion(const Matriz4f & izq, const Matriz4f & der);
#endif

