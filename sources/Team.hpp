#ifndef TEAM_HPP
#define TEAM_HPP

#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"

#include <iostream>
#include <vector>


using namespace std;
namespace ariel{};

class Team {
private:
    Character* lead;
    std::vector<Character*> players;

public:
    Team();
    Team(Character* lead);
    Character* getLeader();
    void setLeader(Character *leader);
    void add(Character* fighter);
    void attack(Team* enemy);
    int stillAlive()const;
    void print()const;
};

#endif