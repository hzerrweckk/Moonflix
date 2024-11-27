#ifndef PELICULA_H
#define PELICULA_H
#include "Video.h"

class Pelicula : public Video {
public:
	Pelicula(std::string id, std::string nombre, double duracion, std::string genero, double calificacion);
	void mostrar() override;
	void mostrar(bool detalle);
};
#endif