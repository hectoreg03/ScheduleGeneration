#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<string,string> ss;

// Definimos una estructura para manejar los deportes
struct Deporte {
    string nombre;
    vector<vector<ss>> partidos;
    vector<vector<string>> eqs;
    vector<string> nms;
};

vector<Deporte> deportes(4); // 4 deportes

// Función para generar los equipos de un deporte
void geneq(int grupos, Deporte &deporte) {
    random_shuffle(deporte.nms.begin(), deporte.nms.end());
    deporte.eqs.resize(grupos);
    for(int i = 0; i < deporte.nms.size(); i++) {
        deporte.eqs[i % grupos].push_back(deporte.nms[i]);
    }
    for(int i = 0; i < deporte.eqs.size(); i++) {
        for(int j = 0; j < deporte.eqs[i].size(); j++) {
            cout << deporte.eqs[i][j] << " ";
        }
        cout << endl;
    }
}

bool pvsd[(int)(1e6 + 10)];
vector<ss> prtgn;

// Función para generar partidos dentro de un grupo de equipos
void genpartg(int it, Deporte &deporte) {
    memset(pvsd, false, sizeof(pvsd));
    prtgn.clear();
    vector<int> aux;
    for(int i = 0; i < deporte.eqs[it].size(); i++) {
        aux.push_back(i);
    }
    sort(aux.begin(), aux.end());
    do {
        bool ps = true;
        for(int i = 0; i + 1 < aux.size(); i += 2) {
            int x = 1 << aux[i];
            x += 1 << aux[i + 1];
            if(pvsd[x] == true) {
                ps = false;
            }
        }
        if(ps) {
            for(int i = 0; i + 1 < aux.size(); i += 2) {
                int x = 1 << aux[i];
                x += 1 << aux[i + 1];
                pvsd[x] = true;
                prtgn.push_back({deporte.eqs[it][aux[i]], deporte.eqs[it][aux[i + 1]]});
            }
        }
    } while(next_permutation(aux.begin(), aux.end()));
}

// Función para generar los horarios para los partidos en diferentes canchas
void genpart(int canchas, Deporte &deporte) {
    int cantidadPartidos = 0;
    vector<vector<ss>> partidosPorGrupo;
    deporte.partidos.resize(deporte.eqs.size());
    vector<int> aux2;
    for(int i = 0; i < deporte.eqs.size(); i++) {
        aux2.push_back(0);
        genpartg(i, deporte);
        partidosPorGrupo.push_back(prtgn);
        cantidadPartidos += prtgn.size();
    }

    int it = 0, caac = 0;
    deporte.partidos.resize(canchas);
    for(int i = 0; i < cantidadPartidos; i++) {
        deporte.partidos[caac].push_back(partidosPorGrupo[it][aux2[it]]);
        aux2[it]++;
        caac++;
        caac %= canchas;
        it++;
        it %= partidosPorGrupo.size();
        if(aux2[it] >= partidosPorGrupo[it].size()) {
            caac = 0;
            it = 0;
        }
    }
}

int main2() {
    int n = 24; // Número de equipos
    int cns = 4, caG = 3; // Canchas y grupos
    cout << "Ingresa la cantidad de equipos o jugadores por deporte:" << endl;
    cin >> n;
    cout << "Ingresa la cantidad de grupos por deporte:" << endl;
    cin >> caG;
    cout << "Ingresa la cantidad de canchas por deporte:" << endl;
    cin >> cns;

    vector<string> deportesNombres = {"Fútbol", "Básquetbol", "Voleibol", "Tenis"};
    for(int d = 0; d < 4; d++) {
        deportes[d].nombre = deportesNombres[d];
        cout << "Generando equipos y partidos para " << deportes[d].nombre << "..." << endl;

        // Agregamos los equipos
        for(int i = 0; i < n; i++) {
            deportes[d].nms.push_back("Equipo" + to_string(i) + " " + deportes[d].nombre);
        }

        // Generamos equipos y partidos
        geneq(caG, deportes[d]);
        genpart(cns, deportes[d]);

        // Exportamos horarios
        ofstream aux(deportes[d].nombre + "_Horarios.csv");
        for(int i = 0; i < deportes[d].partidos[0].size(); i++) {
            if(i == 0) {
                aux << "Canchas, ";
                cout << "Cancha, ";
            }
            aux << "," << "Jornada " + (to_string(i)) << ", ,";
            cout << "Jornada " + (to_string(i)) << ", ";
        }
        aux << endl;
        cout << endl;
        for(int i = 0; i < deportes[d].partidos.size(); i++) {
            aux << "Cancha " + (to_string(i)) << ", ";
            cout << "Cancha " + (to_string(i)) << ", ";
            for(int j = 0; j < deportes[d].partidos[i].size(); j++) {
                aux << deportes[d].partidos[i][j].first << ", vs, " << deportes[d].partidos[i][j].second << ", ";
                cout << deportes[d].partidos[i][j].first << " vs " << deportes[d].partidos[i][j].second << " ";
            }
            aux << endl;
            cout << endl;
        }

        // Exportamos grupos
        ofstream aux2(deportes[d].nombre + "_Grupos.csv");
        for(int i = 0; i < deportes[d].eqs.size(); i++) {
            aux2 << "Grupo " + (to_string(i + 1)) << ":, ";
            for(int j = 0; j < deportes[d].eqs[i].size(); j++) {
                aux2 << deportes[d].eqs[i][j] << ", ";
                cout << deportes[d].eqs[i][j] << ", ";
            }
            aux2 << endl;
            cout << endl;
        }
    }

    return 0;
}
