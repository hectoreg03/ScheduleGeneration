#include<bits/stdc++.h>
#include "Tournament.h"
using namespace std;
typedef pair<int,int> ii;
typedef pair<string,string> ss;


int generarTorneo(int numberTeams, int numberGroups, vector<int> fieldBySport) {
    Tournament torneo(4);  // 4 deportes
    torneo.generateTournament(numberTeams, numberGroups, fieldBySport);

    return 0;
}
