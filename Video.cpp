#include "Video.h"
#include <iostream>
#include <string>
#include <vector>

Video::Video(std::string id, std::string nombre, double duracion, std::string genero, double calificacion) : id(id), nombre(nombre), duracion(duracion), genero(genero), calificacion(calificacion) {}

std::string Video::getGenero() const {
	return genero;
}

double Video::getCalificacion() const {
	return calificacion;
}

std::string Video::getNombre() const {
	return nombre;
}

void Video::calificar(double nuevaCalificacion) {
	calificacion = nuevaCalificacion;
}


