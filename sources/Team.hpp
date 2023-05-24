#ifndef TEAM_HPP
#define TEAM_HPP

#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>


using namespace std;
namespace ariel{};

class Team {
private:
    Character* lead;
    vector<Character*> players;

public:
    Team();
    Team(Character* lead);
    virtual ~Team();
    vector<Character*>& getFighters();
    Character* getLeader();
    void setLeader(Character *leader);
    void addMember(Character* newMem);
    void add(Character* fighter);
    Character* choose_enemy(Team* enemyTeam);
    void attack(Team* enemy);
    int stillAlive()const;
    void print();

    Team (Team&) = delete; 
    Team (Team&&) noexcept = delete;
    Team& operator = (const Team&) = delete; 
    Team& operator = (Team&&) noexcept = delete;
};

#endif