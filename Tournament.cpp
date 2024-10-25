#include "Tournament.h"

Tournament::Tournament(int numberOfSports) {
    deportes.resize(numberOfSports);
}

// Genera un torneo para todos los deportes
void Tournament::generateTournament(int numberTeams, int numberGroups, std::vector<int> fieldBySport) {
    std::vector<std::string> deportesNombres = {"Fútbol", "Básquetbol", "Voleibol", "Tenis"};

    for (int d = 0; d < deportes.size(); d++) {
        deportes[d] = Deporte(deportesNombres[d], fieldBySport[d]);

        // Agregamos los equipos
        for (int i = 0; i < numberTeams; i++) {
            deportes[d].nms.push_back("Equipo" + std::to_string(i) + " " + deportes[d].nombre);
        }

        // Generamos equipos y partidos
        deportes[d].generarEquipos(numberGroups);
        deportes[d].generarPartidos();

        // Exportamos los datos
        deportes[d].exportarHorarios();
        deportes[d].exportarGrupos();
    }
}
