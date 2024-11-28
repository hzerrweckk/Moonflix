#include "Pelicula.h"
#include <iostream>

Pelicula::Pelicula(std::string id, std::string nombre, double duracion, std::string genero, double calificacion)
    : Video(id, nombre, duracion, genero, calificacion) {}

void Pelicula::mostrar() {
    std::cout << "Pelicula: " << nombre << " | Genero: " << genero << " | Duracion: " << duracion << " mins | Calificacion: " << calificacion << std::endl;
}

void Pelicula::mostrar(bool detalle) {
    if (detalle) {
        std::cout << "Pelicula: " << nombre << "Genero: " << genero << "Duracion : " << duracion << " mins Calificacion : " << calificacion << std::endl;
    }
    else {
        mostrar();
    }
}