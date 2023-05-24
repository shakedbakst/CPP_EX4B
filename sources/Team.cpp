#include "Team.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <numeric>

using namespace ariel;
using namespace std;

Team::Team(){}

Team::Team(Character* lead) {
    if (lead == nullptr) {
        throw std::runtime_error("Leader is not initialized");
    }

    if (lead->TeamLeader()) {
        throw std::runtime_error(" is already in another team");
    }

    this->lead = lead;
    players.reserve(10);
    players.push_back(lead);
    lead->setTeamMember();
}

Team::~Team() {
    while (!players.empty()) {
        delete players.back();
        players.pop_back();
    }
}

vector<Character*>& Team::getFighters(){
    return players;
}

Character* Team::getLeader(){
    return this ->lead;
}

void Team::setLeader(Character *leader){
    this ->lead = leader;
}

void Team::addMember(Character* newMem){
    this ->players.push_back(newMem);
}


void Team::add(Character* fighter) {
    if (fighter->TeamMember()) {
        throw std::runtime_error("This fighter is already a team member");
    }

    if (players.size() >= 10) {
        throw std::runtime_error("The group is full. cannot add another fighter.");
    }

    fighter->setTeamMember();
    players.push_back(fighter);
}

Character* Team::choose_enemy(Team* enemyTeam) {
    std::vector<Character*> aliveEnemies;
    for (Character* enemy : enemyTeam->players) {
        if (enemy != nullptr && enemy->isAlive()) {
            aliveEnemies.push_back(enemy);
        }
    }
    
    if (aliveEnemies.empty()) {
        return nullptr;
    }
    
    Character* closestEnemy = aliveEnemies[0];
    double minDistance = lead->distance(closestEnemy);
    
    for (Character* enemy : aliveEnemies) {
        double distance = lead->distance(enemy);
        if (distance < minDistance) {
            minDistance = distance;
            closestEnemy = enemy;
        }
    }
    
    return closestEnemy;
}

void Team::attack(Team* enemy) {
    if (enemy == nullptr || lead == nullptr) {
        throw std::invalid_argument("Enemy/leader is nullptr");
    }
    
    if (enemy->stillAlive() == 0 || this->stillAlive() == 0) {
        throw std::runtime_error("Attacking a dead team");
    }
    
    // Check if the leader is alive, find another one if they are dead
    if (!lead->isAlive()) {
        double minDistance = std::numeric_limits<double>::max();
        Character* newLeader = nullptr;
        
        for (Character* newLeaderCandidate : players) {
            if (newLeaderCandidate != nullptr && newLeaderCandidate->isAlive()) {
                double distance = newLeaderCandidate->distance(lead);
                if (distance < minDistance) {
                    minDistance = distance;
                    newLeader = newLeaderCandidate;
                }
            }
        }
        
        setLeader(newLeader);
    }
    
    Character* closestEnemy = choose_enemy(enemy);
    
    for (Character* fighter : players) {
        if (fighter != nullptr && fighter->isAlive()) {
            if (closestEnemy != nullptr && closestEnemy->isAlive()) {
                if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
                    if (cowboy && cowboy->hasBullets()) {
                        cowboy->shoot(closestEnemy);
                    } else {
                        cowboy->reload();
                    }
                }
                
                if (Ninja* ninja = dynamic_cast<Ninja*>(fighter)) {
                    if (ninja->distance(closestEnemy) < 1) {
                        ninja->slash(closestEnemy);
                    } else {
                        ninja->move(closestEnemy);
                    }
                }
            } else {
                closestEnemy = choose_enemy(enemy);
                
                if (closestEnemy != nullptr && closestEnemy->isAlive()) {
                    if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
                        if (cowboy && cowboy->hasBullets()) {
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
}

/*Character* Team::chooseClosestAliveEnemy(Team* enemy) {
    Character* closestEnemy = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Character* enemyFighter : enemy->players) {
        if (enemyFighter != nullptr && enemy->isAlive()) {
            double dist = lead->getLocation().distance(enemyFighter->getLocation());
            if (dist < minDistance) {
                minDistance = dist;
                closestEnemy = enemyFighter;
            }
        }
    }

    return closestEnemy;
}



void Team::attack(Team* enemy) {
    if (!enemy || !lead) {
        throw std::invalid_argument("Error! null team/leader");
    }

    if (enemy->stillAlive() == 0 || this->stillAlive() == 0) {
        throw std::runtime_error("All the enemy team are dead");
    }

    Character* closestEnemy = chooseClosestAliveEnemy(enemy);

    for (Character* fighter : players) {
        if (fighter && fighter->isAlive()) {
            if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter)) {
                if (cowboy->hasBullets() && closestEnemy) {
                    cowboy->shoot(closestEnemy);
                } else {
                    cowboy->reload();
                }
            } else if (Ninja* ninja = dynamic_cast<Ninja*>(fighter)) {
                if (closestEnemy && ninja->distance(closestEnemy) < 1) {
                    ninja->slash(closestEnemy);
                } else {
                    ninja->move(closestEnemy);
                }
            }
        }
    }
}*/



int Team::stillAlive() const {
    return std::count_if(players.begin(), players.end(), [](Character* fighter) {
        return fighter != nullptr && fighter->isAlive();
    });
}



void Team::print() {
    for (Character* member : players) {
        if (Cowboy* cowboy = dynamic_cast<Cowboy*>(member)) {
            cout << cowboy->print() << endl;
        }
    }

    for (Character* member : players) {
        if (Ninja* ninja = dynamic_cast<Ninja*>(member)) {
            cout << ninja->print() << endl;
        }
    }

    cout << "The leader is " << lead->print() << endl;
}

