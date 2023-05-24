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
        Character* leader;
        vector<Character*> players;

    public:
        //void addToMembers(Character* newChar);

        void setLeader(Character *leader);

        Character* getLeader();

        std::vector <Character*> getFighters() const{
            return players;
        }

        Character* findClosestAliveFighter(const Team &team, const Character *leader) const;


        Team (Team&) = delete; 
        Team (Team&&) noexcept = delete;
        Team& operator = (const Team&) = delete; 
        Team& operator = (Team&&) noexcept = delete;

        Team(Character* leader);

        Team();
        
        virtual ~Team(){
        for(size_t i=0 ; i<players.size() ;i++){
            delete players.at(i);
            }
        }
    
        void add(Character* newChr);

        void attack(Team* other);

        int stillAlive();

        void print();
    
};

#endif