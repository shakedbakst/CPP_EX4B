#include "Team2.hpp"
#include "Team.hpp"
#include <iostream>
#include <limits>

Team2::Team2(Character* leader) : Team(leader) {
    if (leader->TeamMember()) {
        string name = leader->getName();
        throw std::runtime_error(name + " is already in another team");
    }
    this->setLeader(leader);
    this->addToMembers(leader);
    leader->setTeamMember();
}

Team2::Team2() : Team() {}

void Team2::attack(Team* other) {
    if (other == nullptr) {
        throw std::invalid_argument("No team was given to attack");
    }
    if (other->stillAlive() == 0) {
        throw std::runtime_error("All teammates are already dead");
    }
    if (!this->getLeader()->isAlive()) {
        this->setLeader(findClosestAliveFighter(*this, getLeader()));
    }
    if (other->stillAlive() == 0) {
        return;
    }
    Character* toAttack = findClosestAliveFighter(*other, getLeader());
    for (Character* fighter : this->getFighters()) {
        if (other->stillAlive() == 0) {
            break;
        }
        if (!toAttack->isAlive()) {
            toAttack = findClosestAliveFighter(*other, getLeader());
        }

        if (fighter->getType() == "Ninja" && fighter->isAlive()) {
            Ninja* ninja = dynamic_cast<Ninja*>(fighter);
            if (ninja->distance(toAttack) <= 1) {
                ninja->slash(toAttack);
            } else {
                ninja->move(toAttack);
            }
        }

        if (fighter->getType() == "Cowboy" && fighter->isAlive()) {
            Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter);
            if (cowboy->hasboolets()) {
                cowboy->shoot(toAttack);
            } else {
                cowboy->reload();
            }
        }
    }
}

Character* Team2::findClosestAliveFighter(const Team& team, const Character* leader) const {
    double minDistance = std::numeric_limits<double>::max();
    Character* closestAlive = nullptr;
    for (Character* member : team.getFighters()) {
        if (member->isAlive()) {
            if (leader->distance(member) < minDistance) {
                minDistance = leader->distance(member);
                closestAlive = member;
            }
        }
    }
    return closestAlive;
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
