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

string red = "\033[31m";
string yellow = "\033[33m";
string reset = "\033[0m";

void mostrarMenu() {


    cout <<red <<R"(
 
███╗░░░███╗░█████╗░░█████╗░███╗░░██╗███████╗██╗░░░░░██╗██╗░░██╗
████╗░████║██╔══██╗██╔══██╗████╗░██║██╔════╝██║░░░░░██║╚██╗██╔╝
██╔████╔██║██║░░██║██║░░██║██╔██╗██║█████╗░░██║░░░░░██║░╚███╔╝░
██║╚██╔╝██║██║░░██║██║░░██║██║╚████║██╔══╝░░██║░░░░░██║░██╔██╗░
██║░╚═╝░██║╚█████╔╝╚█████╔╝██║░╚███║██║░░░░░███████╗██║██╔╝╚██╗
╚═╝░░░░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚══╝╚═╝░░░░░╚══════╝╚═╝╚═╝░░╚═╝  
                                                                                                                
)"<<reset << '\n' << endl;
    cout << "Bienvenido a \"Moonflix\", la plataforma de streaming mas grande de la historia..." << endl;
    cout << "Ofrecemos los siguientes servicios, selecciona uno: " << endl;
    cout << "\nMenu:\n";
    cout << "1. Cargar archivo de datos\n";
    cout << "2. Mostrar videos con calificacion o genero\n";
    cout << "3. Mostrar episodios con calificacion\n";
    cout << "4. Mostrar peliculas con calificacion\n";
    cout << "5. Calificar un video\n";
    cout << "0. Salir\n";
    cout << "Generos disponibles : Drama, Sci - fi, Mystery, Action, Crime, Animation, Comedy, Fantasy, Romance, History" << endl;
    cout << "Ingrese una opcion: ";
}

int main(){
    vector<Video*> videos;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            cout << "Cargando archivo de datos...\n";
            ifstream archivo("/workspaces/Moonflix/Datos.txt");
            if (!archivo.is_open()) {
                cout << "Error al abrir el archivo de datos.\n";
                break;
            }

            string linea;
            while (getline(archivo, linea)) {
                
                if (linea.empty() || linea[0] == '#' || (linea.size() > 1 && linea[0] == '/' && linea[1] == '/')) {
                    continue; 
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
                        
                        if (linea.empty() || linea[0] == '#' || (linea.size() > 1 && linea[0] == '/' && linea[1] == '/')) {
                            continue; 
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

            
            transform(filtro.begin(), filtro.end(), filtro.begin(), ::tolower);
            filtro.erase(remove_if(filtro.begin(), filtro.end(), ::isspace), filtro.end());

            for (Video* video : videos) {
                
                string generoVideo = video->getGenero();
                transform(generoVideo.begin(), generoVideo.end(), generoVideo.begin(), ::tolower);
                generoVideo.erase(remove_if(generoVideo.begin(), generoVideo.end(), ::isspace), generoVideo.end());

                if (generoVideo == filtro || to_string(static_cast<int>(video->getCalificacion())) == filtro) {
                    video->mostrar();
                }
            }
            break;
        }
        case 3: {
            cout << "Ingrese la calificacion (entre 1 y 5): ";
            double calificacion;
            cin >> calificacion;
            cin.ignore();
            bool seriesEncontradas = false;

            for (auto& video : videos) {
                Serie* serie = dynamic_cast<Serie*>(video);
                if (serie && abs(serie->getCalificacion() - calificacion) < 0.1) {
                    serie->mostrar();
                    seriesEncontradas = true;
                }
            }

            if (!seriesEncontradas) {
                cout << "No se encontraron series con la calificacion aproximada de " << calificacion << ".\n";
            }
            break;
        }
        case 4: {
            cout << "Ingrese la calificacion (entre 1 y 5): ";
    double calif;
    cin >> calif;
    cin.ignore();
    bool peliculasEncontradas = false;

    for (auto& video : videos) {
        Pelicula* pelicula = dynamic_cast<Pelicula*>(video);
        if (pelicula) {
            // Imprime para depurar la calificación de la película
            cout << "Pelicula: '" << pelicula->getNombre() << "': " << pelicula->getCalificacion() << endl;

            if (abs(pelicula->getCalificacion() - calif) < 0.01) {
                pelicula->mostrar();
                peliculasEncontradas = true;
            }
        }
    }

    if (!peliculasEncontradas) {
        cout << "Mostrando calificaciones similares... " << calif << ".\n";
    }
    break;
        }
        case 5: {
            cout << "Ingrese el nombre del video a calificar: ";
            string nombreVideo;
            getline(cin, nombreVideo);
            transform(nombreVideo.begin(), nombreVideo.end(), nombreVideo.begin(), ::tolower);
            nombreVideo.erase(remove_if(nombreVideo.begin(), nombreVideo.end(), ::isspace), nombreVideo.end());
            cout << "Ingrese la nueva calificacion: ";
            double nuevaCalificacion;
            cin >> nuevaCalificacion;
            cin.ignore();
            bool videoEncontrado = false;
            for (auto& video : videos) {
                string nombreActual = video->getNombre();
                transform(nombreActual.begin(), nombreActual.end(), nombreActual.begin(), ::tolower);
                nombreActual.erase(remove_if(nombreActual.begin(), nombreActual.end(), ::isspace), nombreActual.end());
                if (nombreActual == nombreVideo) {
                    double calificacionActual = video->getCalificacion();
                    double calificacionPromediada = (calificacionActual + nuevaCalificacion) / 2;
                    video->calificar(calificacionPromediada);
                    cout << "Video calificado exitosamente con un nuevo promedio de " << calificacionPromediada << ".\n";
                    videoEncontrado = true;
                }
            }
            if (!videoEncontrado) {
                cout << "No se encontró un video con ese nombre.\n";
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
