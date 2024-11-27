#include <iostream>
#include "Video.h"
#include "Pelicula.h"
#include "Serie.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


void mostrarMenu() {
        string red = "\033[31m";
    string yellow = "\033[33m";
    string reset = "\033[0m";

    cout <<red <<R"(
 
███╗░░░███╗░█████╗░░█████╗░███╗░░██╗███████╗██╗░░░░░██╗██╗░░██╗
████╗░████║██╔══██╗██╔══██╗████╗░██║██╔════╝██║░░░░░██║╚██╗██╔╝
██╔████╔██║██║░░██║██║░░██║██╔██╗██║█████╗░░██║░░░░░██║░╚███╔╝░
██║╚██╔╝██║██║░░██║██║░░██║██║╚████║██╔══╝░░██║░░░░░██║░██╔██╗░
██║░╚═╝░██║╚█████╔╝╚█████╔╝██║░╚███║██║░░░░░███████╗██║██╔╝╚██╗
╚═╝░░░░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚══╝╚═╝░░░░░╚══════╝╚═╝╚═╝░░╚═╝  
                                                                                                                
)"<<reset << '\n' << endl;
    cout << "Welcome to \"Moonflix\", the largest video streaming platform in history." << endl;
    cout << "We offer the following services, please select one: " << endl;
    cout << "\nMenu:\n";
    cout << "1. Cargar archivo de datos\n";
    cout << "2. Mostrar videos con calificacion o genero\n";
    cout << "3. Mostrar episodios con calificacion\n";
    cout << "4. Mostrar peliculas con calificacion\n";
    cout << "5. Calificar un video\n";
    cout << "0. Salir\n";
    cout << "Generos disponibles : Drama, Sci - fi, Mystery" << endl;
    cout << "Ingrese una opcion: ";
}

int main(){
    vector<Video*> videos;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Ignorar el salto de línea después de la opción ingresada

        switch (opcion) {
        case 1: {
            cout << "Cargando archivo de datos...\n";
            ifstream archivo("datos.txt");
            if (!archivo.is_open()) {
                cout << "Error al abrir el archivo de datos.\n";
                break;
            }

            string linea;
            while (getline(archivo, linea)) {
                // Ignorar comentarios (líneas que comienzan con # o //)
                if (linea.empty() || linea[0] == '#' || (linea.size() > 1 && linea[0] == '/' && linea[1] == '/')) {
                    continue; // Saltar a la siguiente línea
                }

                stringstream ss(linea);
                string tipo;
                getline(ss, tipo, ';');
                if (tipo == "pelicula") {
                    string id, nombre, genero;
                    double duracion, calificacion;

                    getline(ss, id, ';');
                    getline(ss, nombre, ';');
                    ss >> duracion;
                    ss.ignore();
                    getline(ss, genero, ';');
                    ss >> calificacion;

                    videos.push_back(new Pelicula(id, nombre, duracion, genero, calificacion));
                }
                else if (tipo == "serie") {
                    string id, nombre, genero;
                    double duracion, calificacion;

                    getline(ss, id, ';');
                    getline(ss, nombre, ';');
                    ss >> duracion;
                    ss.ignore();
                    getline(ss, genero, ';');
                    ss >> calificacion;

                    Serie* serie = new Serie(id, nombre, duracion, genero, calificacion);
                    videos.push_back(serie);
                    while (getline(archivo, linea)) {
                        // Ignorar comentarios en los episodios también
                        if (linea.empty() || linea[0] == '#' || (linea.size() > 1 && linea[0] == '/' && linea[1] == '/')) {
                            continue; // Saltar a la siguiente línea
                        }

                        stringstream ssEpisodio(linea);
                        string subTipo;
                        getline(ssEpisodio, subTipo, ';');

                        if (subTipo == "episodio") {
                            string titulo;
                            int temporada;
                            double calificacionEpisodio;

                            getline(ssEpisodio, titulo, ';');
                            ssEpisodio >> temporada;
                            ssEpisodio.ignore();
                            ssEpisodio >> calificacionEpisodio;

                            serie->agregarEpisodio(titulo, temporada, calificacionEpisodio);
                        }
                        else {
                            // Si no es un episodio, retrocedemos la posición de lectura para la siguiente iteración
                            archivo.seekg(-(static_cast<std::streamoff>(linea.size()) + 1), ios::cur);
                            break;
                        }
                    }
                }
            }

            archivo.close();
            cout << "Archivo cargado exitosamente.\n";
            break;
        }
        case 2: {
            // Mostrar videos de un cierto genero o calificacion
            cout << yellow << R"(

██╗░░░██╗██╗██████╗░███████╗░█████╗░  ██╗░░░░░██╗░██████╗████████╗
██║░░░██║██║██╔══██╗██╔════╝██╔══██╗  ██║░░░░░██║██╔════╝╚══██╔══╝
╚██╗░██╔╝██║██║░░██║█████╗░░██║░░██║  ██║░░░░░██║╚█████╗░░░░██║░░░
░╚████╔╝░██║██║░░██║██╔══╝░░██║░░██║  ██║░░░░░██║░╚═══██╗░░░██║░░░
░░╚██╔╝░░██║██████╔╝███████╗╚█████╔╝  ███████╗██║██████╔╝░░░██║░░░
░░░╚═╝░░░╚═╝╚═════╝░╚══════╝░╚════╝░  ╚══════╝╚═╝╚═════╝░░░░╚═╝░░░
        )" << reset << endl;
            cout << "Ingrese genero o calificacion para filtrar: ";
            string filtro;
            getline(cin, filtro);

            // Convertir filtro a minúsculas para comparar géneros de forma insensible a mayúsculas
            transform(filtro.begin(), filtro.end(), filtro.begin(), ::tolower);

            for (Video* video : videos) {
                // Obtener el género en minúsculas para hacer una comparación insensible a mayúsculas
                string generoVideo = video->getGenero();
                transform(generoVideo.begin(), generoVideo.end(), generoVideo.begin(), ::tolower);

                if (generoVideo == filtro || to_string(static_cast<int>(video->getCalificacion())) == filtro) {
                    video->mostrar();
                }
            }
            break;
        }
        case 3: {
            cout << "Ingrese el nombre de la serie y la calificacion: ";
            string nombreSerie;
            double calificacion;
            getline(cin, nombreSerie);
            cin >> calificacion;
            cin.ignore();
            for (auto& video : videos) {
                Serie* serie = dynamic_cast<Serie*>(video);
                if (serie && serie->getNombre() == nombreSerie) {
                    serie->mostrarEpisodiosConCalificacion(calificacion);
                }
            }
            break;
        }
        case 4: {
            cout << "Ingrese la calificacion: ";
            double calif;
            cin >> calif;
            cin.ignore();
            for (auto& video : videos) {
                Pelicula* pelicula = dynamic_cast<Pelicula*>(video);
                if (pelicula && pelicula->getCalificacion() == calif) {
                    pelicula->mostrar();
                }
            }
            break;
        }
        case 5: {
            cout << "Ingrese el nombre del video a calificar: ";
            string nombreVideo;
            getline(cin, nombreVideo);
            cout << "Ingrese la nueva calificacion: ";
            double nuevaCalificacion;
            cin >> nuevaCalificacion;
            cin.ignore();
            for (auto& video : videos) {
                if (video->getNombre() == nombreVideo) {
                    video->calificar(nuevaCalificacion);
                    cout << "Video calificado exitosamente.\n";
                }
            }
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }

    } while (opcion != 0);

    for (auto& video : videos) {
        delete video;
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
