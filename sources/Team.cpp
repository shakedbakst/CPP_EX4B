#include "Team.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;


Team::Team() {}

Team::Team(Character* leader) {
    if (leader->TeamMember()) {
        string name = leader->getName();
        throw std::runtime_error(name + " is already in another team");
    }
    this->leader = leader;
    this->players.push_back(leader);
    leader->setTeamMember();
}

void Team::add(Character* newChr) {
    if (this->players.size() == 10) {
        throw std::runtime_error("Team is full, can't add more mates");
    }
    if (newChr->TeamMember()) {
        string name = newChr->getName();
        throw std::runtime_error(name + " is already in another team");
    }
    this->players.push_back(newChr);
    newChr->setTeamMember();
}

void Team::setLeader(Character* leader) {
    this->leader = leader;
}

Character* Team::getLeader() {
    return this->leader;
}

void Team::attack(Team* other) {
    if (other == nullptr) {
        throw std::invalid_argument("No team was given to attack");
    }
    if (other->stillAlive() == 0) {
        throw std::runtime_error("All teammates are already dead");
    }
    if (!this->leader->isAlive()) {
        this->leader = findClosestAliveFighter(*this, this->leader);
    }
    if (other->stillAlive() == 0) {
        return;
    }
    Character* toAttack = findClosestAliveFighter(*other, this->leader);
    for (Character* fighter : this->getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }
        if (!toAttack->isAlive()) {
            toAttack = findClosestAliveFighter(*other, this->leader);
        }
        if (fighter->getType() == "Cowboy" && fighter->isAlive()) {
            Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter);
            if (cowboy->hasBullets()) {
                cowboy->shoot(toAttack);
            } else {
                cowboy->reload();
            }
        }
    }
    for (Character* fighter : this->getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }
        if (!toAttack->isAlive()) {
            toAttack = findClosestAliveFighter(*other, this->leader);
        }
        if (fighter->getType() == "Ninja" && fighter->isAlive()) {
            Ninja* ninja = dynamic_cast<Ninja*>(fighter);
            if (ninja->distance(toAttack) <= 1) {
                ninja->slash(toAttack);
            } else {
                ninja->move(toAttack);
            }
        }
    }
}

Character* Team::findClosestAliveFighter(const Team& team, const Character* leader) const {
    double minDistance = std::numeric_limits<double>::max();
    Character* closestAlive = nullptr;
    for (Character* member : team.players) {
        if (member->isAlive()) {
            if (leader->distance(member) < minDistance) {
                minDistance = leader->distance(member);
                closestAlive = member;
            }
        }
    }
    return closestAlive;
}

int Team::stillAlive() {
    int count = 0;
    for (Character* member : players) {
        if (member->isAlive()) {
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
