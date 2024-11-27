#include "Serie.h"
#include <iostream>

Episodio::Episodio(std::string titulo, int temporada, double calificacion) : titulo(titulo), temporada(temporada), calificacion(calificacion) {}

Serie::Serie(std::string id, std::string nombre, double duracion, std::string genero, double calificacion)
    : Video(id, nombre, duracion, genero, calificacion) {}

void Serie::agregarEpisodio(std::string titulo, int temporada, double calificacion) {
    episodios.push_back(Episodio(titulo, temporada, calificacion));
}

void Serie::mostrar() {
    std::cout << "Serie: " << nombre << " | Genero: " << genero << " | Duracion promedio: " << duracion << " mins | Calificacion promedio: " << calificacion << std::endl;
    for (auto& episodio : episodios) {
        std::cout << "  Episodio: " << episodio.titulo << " | Temporada: " << episodio.temporada << " | Calificacion: " << episodio.calificacion << std::endl;
    }
}

void Serie::mostrarEpisodiosConCalificacion(double calif) {
    for (auto& episodio : episodios) {
        if (episodio.calificacion == calif) {
            std::cout << "  Episodio: " << episodio.titulo << " | Temporada: " << episodio.temporada << " | Calificacion: " << episodio.calificacion << std::endl;
        }
    }
}
