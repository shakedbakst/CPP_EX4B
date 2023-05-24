#include "Team.hpp"
#include <iostream>
#include <limits>

using namespace std;


Team::Team() {}

Team::Team(Character* leader) {
    if (leader->TeamMember()) {
        std::string name = leader->getName();
        throw runtime_error(name + " is already a team member");
    }

    this->leader = leader;
    this->players.push_back(leader);
    leader->setTeamMember();
}



void Team::add(Character* warrior) {
    constexpr int MAX_CAPACITY = 10;

    if (players.size() == MAX_CAPACITY) {
        throw runtime_error("Error- Cannot add another warrior");
    }

    if (warrior->TeamMember()) {
        throw runtime_error("Error- This warrior is already a team member.");
    }

   
    players.push_back(warrior);
    warrior->setTeamMember();
    
}


void Team::setLeader(Character* leader) {
    this->leader = leader;
}

Character* Team::getLeader() {
    return this->leader;
}

Character* Team::findClosestFighter(const Team& team, const Character* leader) const {
    double minDistance = std::numeric_limits<double>::max();
    Character* closestAlive = nullptr;
    for (Character* member : team.players) {
        if (member->isAlive()) {
            double distance = leader->distance(member);
            if (distance < minDistance) {
                minDistance = distance;
                closestAlive = member;
            }
        }
    }
    return closestAlive;
}

void Team::attack(Team* other) {
    if (other == nullptr) {
        throw std::invalid_argument("Error!");
    }

    if (other->stillAlive() == 0) {
        throw std::runtime_error("Error- teames dead");
    }

    if (!leader->isAlive()) {
        leader = findClosestFighter(*this, leader);
    }

    if (other->stillAlive() == 0) {
        return;
    }

    Character* toAttack = findClosestFighter(*other, leader);

    for (Character* fighter : getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }

        if (!toAttack->isAlive()) {
            toAttack = findClosestFighter(*other, leader);
        }

        if (fighter->getType() == "Cowboy" && fighter->isAlive()) {
            Cowboy* cboy = dynamic_cast<Cowboy*>(fighter);
            if (cboy && cboy->hasboolets()) {
                cboy->shoot(toAttack);
            } else if (cboy) {
                cboy->reload();
            }
        }
    }

    for (Character* fighter : getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }

        if (!toAttack->isAlive()) {
            toAttack = findClosestFighter(*other, leader);
        }

        if (fighter->getType() == "Ninja" && fighter->isAlive()) {
            Ninja* nja = dynamic_cast<Ninja*>(fighter);
            if (nja && nja->distance(toAttack) <= 1) {
                nja->slash(toAttack);
            } else if (nja) {
                nja->move(toAttack);
            }
        }
    }
}




int Team::stillAlive() const{
    int count = 0;
    for (Character* member : players) {
        if (member!=nullptr && member->isAlive()) {
            count++;
        }
    }
    return count;
}

void Team::print() {
    for (Character* member : players) {
        if (member->getType() == "Cowboy") {
            cout << member->print() << endl;
        }
    }
    for (Character* member : players) {
        if (member->getType() == "Ninja") {
            cout << member->print() << endl;
        }
    }
    cout << "The leader is " << this->leader->print() << endl;
}

void Team :: addToMembers(Character* newChar){
    this ->players.push_back(newChar);
}
