#ifndef TEAM2_HPP
#define TEAM2_HPP

#include <iostream>
#include <vector>

#include "Team.hpp"


using namespace std;
namespace ariel{};

class Team2 : public Team{

    private:
        

    public:
        Team2(Character* lead);
        Team2();
        Character* choose_enemy(Team* enemyTeam);
        void attack(Team* enemy);
        void print();




};
#endif