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
        Team2(Character* leader);
        Team2();
        Character* findClosestFighter(const Team &team, const Character *leader) const;
        void attack(Team* other);
        void print();



};
#endif