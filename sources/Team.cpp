#include "Team.hpp"
#include <iostream>
#include <cmath>

Team::Team(){}

Team::Team(Character* lead) {
    if (lead == nullptr) {
        throw std::runtime_error("Leader is not initialized");
    }

    if (lead->isTaken()) {
        string name = lead->getName();
        throw std::runtime_error(name + " is already in another team");
    }

    lead->setIsLeader(true);
    lead->setInTeam(true);

    this->lead = lead;
    this->members.push_back(lead);
}

Character* Team::getLeader(){
    return this ->leader;
}

void Team::setLeader(Character *leader){
    this ->leader = leader;
}


void Team::add(Character* fighter) {
    if (fighters.size() == 10) {
        throw std::runtime_error("There are no more places in the group");
    }

    if (fighter->isMember()) {
        throw std::runtime_error("This member is already a member");
    }

    if (fighter->isTaken()) {
        throw std::runtime_error(fighter->getName() + " is already in another team");
    }

    fighter->setIsMember(true);
    fighter->setInTeam(true);

    if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
        fighters.insert(fighters.begin(), fighter);
    } else {
        fighters.push_back(fighter);
    }
}


void Team::attack(Team* enemy) {
    if (enemy == nullptr) {
        throw std::invalid_argument("Enemy team is nullptr");
    }

    if (!leader || !enemy->stillAlive() || !stillAlive()) {
        throw std::runtime_error("Invalid attack: either leader is nullptr or one of the teams is dead");
    }

    Character* closestEnemy = nullptr;
    if (enemy->stillAlive() > 0) {
        closestEnemy = findClosestAliveFighter(*enemy, *this);
    }

    for (Character* fighter : fighters) {
        if (!fighter || !fighter->isAlive()) {
            continue;
        }

        if (closestEnemy && closestEnemy->isAlive()) {
            if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
                if (cowboy->hasBullets()) {
                    cowboy->shoot(closestEnemy);
                } else {
                    cowboy->reload();
                }
            } else if (Ninja* ninja = dynamic_cast<Ninja*>(fighter)) {
                if (ninja->distance(closestEnemy) < 1) {
                    ninja->slash(closestEnemy);
                } else {
                    ninja->move(closestEnemy);
                }
            }
        } else {
            closestEnemy = findClosestAliveFighter(*enemy, *this);

            if (closestEnemy && closestEnemy->isAlive()) {
                if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
                    if (cowboy->hasBullets()) {
                        cowboy->shoot(closestEnemy);
                    } else {
                        cowboy->reload();
                    }
                } else if (Ninja* ninja = dynamic_cast<Ninja*>(fighter)) {
                    if (ninja->distance(closestEnemy) < 1) {
                        ninja->slash(closestEnemy);
                    } else {
                        ninja->move(closestEnemy);
                    }
                }
            }
        }
    }
}


int Team::stillAlive() const {
    return std::count_if(fighters.begin(), fighters.end(), [](Character* fighter) {
        return fighter && fighter->isAlive();
    });
}


void Team::print() const {
    for (const Character* fighter : fighters) {
        if (const Cowboy* cowboy = dynamic_cast<const Cowboy*>(fighter)) {
            cout << cowboy->print() << endl;
        } else if (const Ninja* ninja = dynamic_cast<const Ninja*>(fighter)) {
            cout << ninja->print() << endl;
        }
    }

    cout << "The leader is " << leader->print() << endl;
}
