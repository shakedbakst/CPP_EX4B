#include "Team2.hpp"
#include <iostream>
#include <limits>

Team2::Team2(Character* leader) {
    if (leader->TeamMember()) {
        std::string name = leader->getName();
        throw runtime_error(name + " is already a team member");
    }

    this->setLeader(leader);
    this->addToMembers(leader);
    leader->setTeamMember();
}

Team2::Team2() : Team() {}

Character* Team2::findClosestFighter(const Team& team, const Character* leader) const {
    double minDistance = std::numeric_limits<double>::max();
    Character* closestAlive = nullptr;
    for (Character* member : team.getFighters()) {
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

void  Team2 :: attack(Team* other){
    if (other == nullptr) {
        throw std::invalid_argument("Error!");
    }

    if (other->stillAlive() == 0) {
        throw std::runtime_error("Error- teames dead");
    }

    if (!(this->getLeader()->isAlive())) {
        this->setLeader(findClosestFighter(*this, getLeader()));
    }

    if (other->stillAlive() == 0) {
        return;
    }

    Character* toAttack = findClosestFighter(*other, getLeader());

    for (Character* fighter : getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }

        if (!toAttack->isAlive()) {
            toAttack = findClosestFighter(*other, getLeader());
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
            toAttack = findClosestFighter(*other, getLeader());
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

void Team2::print() {
    for (Character* member : this->getFighters()) {
        if (member->getType() == "Cowboy") {
            cout << member->print() << endl;
        }
        if (member->getType() == "Ninja") {
            cout << member->print() << endl;
        }
    }

    cout << "The leader is " << this->getLeader()->print() << endl;
}
