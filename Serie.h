#ifndef SERIE_H
#define SERIE_H
#include "Video.h"
#include <vector>

class Episodio {
public:
	std::string titulo;
	int temporada;
	double calificacion;
	Episodio(std::string titulo, int temporada, double calificacion);
};

class Serie : public Video {
private:
	std::vector<Episodio> episodios;
public:
	Serie(std::string id, std::string nombre, double duracion, std::string genero, double calificacion);
	void agregarEpisodio(std::string titulo, int temportada, double calficacion);
	void mostrar() override;
	void mostrarEpisodiosConCalificacion(double calif);

};

#endif