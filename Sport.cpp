#include "Sport.h"
#include <cstring>
#include <iostream>

bool pvsd[(int)(1e6 + 10)];
std::vector<ss> prtgn;

Deporte::Deporte(std::string nombre, int canchas) : nombre(nombre), cns(canchas) {}
Deporte::Deporte()  {
	nombre="Default";
	cns=2;
}

// Genera los equipos de un deporte distribuidos en grupos
void Deporte::generarEquipos(int grupos) {
    std::random_shuffle(nms.begin(), nms.end());
    eqs.resize(grupos);
    for (int i = 0; i < nms.size(); i++) {
        eqs[i % grupos].push_back(nms[i]);
    }
    for (const auto& grupo : eqs) {
        for (const auto& equipo : grupo) {
            std::cout << equipo << " ";
        }
        std::cout << std::endl;
    }
}

// Genera los partidos dentro de un grupo de equipos
void Deporte::generarPartidosPorGrupo(int grupo) {
    std::memset(pvsd, false, sizeof(pvsd));
    prtgn.clear();
    std::vector<int> aux;
    for (int i = 0; i < eqs[grupo].size(); i++) {
        aux.push_back(i);
    }
    std::sort(aux.begin(), aux.end());
    do {
        bool posible = true;
        for (int i = 0; i + 1 < aux.size(); i += 2) {
            int x = 1 << aux[i];
            x += 1 << aux[i + 1];
            if (pvsd[x] == true) {
                posible = false;
            }
        }
        if (posible) {
            for (int i = 0; i + 1 < aux.size(); i += 2) {
                int x = 1 << aux[i];
                x += 1 << aux[i + 1];
                pvsd[x] = true;
                prtgn.push_back({eqs[grupo][aux[i]], eqs[grupo][aux[i + 1]]});
            }
        }
    } while (std::next_permutation(aux.begin(), aux.end()));
}

// Genera los partidos en las canchas disponibles
void Deporte::generarPartidos() {
    int cantidadPartidos = 0;
    std::vector<std::vector<ss>> partidosPorGrupo;
    partidos.resize(eqs.size());
    std::vector<int> aux2;

    for (int i = 0; i < eqs.size(); i++) {
        aux2.push_back(0);
        generarPartidosPorGrupo(i);
        partidosPorGrupo.push_back(prtgn);
        cantidadPartidos += prtgn.size();
    }

    int it = 0, caac = 0;
    partidos.resize(cns);
    for (int i = 0; i < cantidadPartidos; i++) {
        partidos[caac].push_back(partidosPorGrupo[it][aux2[it]]);
        aux2[it]++;
        caac++;
        caac %= cns;
        it++;
        it %= partidosPorGrupo.size();
        if (aux2[it] >= partidosPorGrupo[it].size()) {
            caac = 0;
            it = 0;
        }
    }
}

// Exporta los horarios generados a un archivo CSV
void Deporte::exportarHorarios() {
    std::ofstream aux(nombre + "_Horarios.csv");
    for (int i = 0; i < partidos[0].size(); i++) {
        if (i == 0) {
            aux << "Canchas, ";
        }
        aux << "Jornada " + std::to_string(i) << ", ,";
    }
    aux << std::endl;
    for (int i = 0; i < partidos.size(); i++) {
        aux << "Cancha " + std::to_string(i) << ", ";
        for (int j = 0; j < partidos[i].size(); j++) {
            aux << partidos[i][j].first << ", vs, " << partidos[i][j].second << ", ";
        }
        aux << std::endl;
    }
}

// Exporta los equipos y su distribución en grupos
void Deporte::exportarGrupos() {
    std::ofstream aux2(nombre + "_Grupos.csv");
    for (int i = 0; i < eqs.size(); i++) {
        aux2 << "Grupo " + std::to_string(i + 1) << ":, ";
        for (int j = 0; j < eqs[i].size(); j++) {
            aux2 << eqs[i][j] << ", ";
        }
        aux2 << std::endl;
    }
}
