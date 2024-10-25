#ifndef TORNEO_H
#define TORNEO_H

#include "Sport.h"
#include <vector>

class Tournament {
public:
    std::vector<Deporte> deportes;

    Tournament(int numberOfSports);

    void generateTournament(int numberTeams, int numberGroups, std::vector<int> fieldBySport);
};

#endif
