#ifndef DEPORTE_H
#define DEPORTE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

typedef std::pair<std::string, std::string> ss;

class Deporte {
public:
    std::string nombre;
    int cns;  // Cantidad de canchas
    std::vector<std::vector<ss>> partidos;
    std::vector<std::vector<std::string>> eqs;  // Equipos en grupos
    std::vector<std::string> nms;  // Lista de nombres de los equipos

    Deporte();

    Deporte(std::string nombre, int canchas);

    // Métodos para manejar equipos y partidos
    void generarEquipos(int grupos);
    void generarPartidosPorGrupo(int grupo);
    void generarPartidos();
    void exportarHorarios();
    void exportarGrupos();
};

#endif
