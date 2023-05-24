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
        Character* leader;
        vector<Character*> players;

    public:
        Team();
        Team(Character* leader);
        void add(Character* newChr);
        void setLeader(Character *leader);
        Character* getLeader();
        Character* findClosestFighter(const Team &team, const Character *leader) const;
        void attack(Team* other);
        int stillAlive();
        void print();
        void addToMembers(Character* newChar);

        Team (Team&) = delete; 
        Team (Team&&) noexcept = delete;
        Team& operator = (const Team&) = delete; 
        Team& operator = (Team&&) noexcept = delete;
        

        std::vector <Character*> getFighters() const{
            return players;
        }

        virtual ~Team(){
        for(size_t i=0 ; i<players.size() ;i++){
            delete players.at(i);
            }
        }
        
    
};

#endif