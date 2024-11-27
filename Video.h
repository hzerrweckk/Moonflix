#pragma once
#include <iostream>
#include <string>
#include <vector>

class Video {
protected:
	std::string id;
	std::string nombre;
	double duracion;
	std::string genero;
	double calificacion;
public:
	Video(std::string id, std::string nombre, double duracion, std::string genero, double calificacion);
	virtual void mostrar() = 0;
	std::string getGenero() const;
	double getCalificacion() const;
	std::string getNombre() const;
	void calificar(double nuevaCalificacion);
	virtual ~Video() = default;
};