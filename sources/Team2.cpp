#include "Team2.hpp"
#include "Team.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <numeric>

using namespace ariel;
using namespace std;

Team2::Team2(Character* lead) {
    if (lead->TeamLeader()) {
        throw std::runtime_error(" is already in another team");
    }

    this ->setLeader(lead);
    this ->addMember(lead);
    lead->setTeamMember();
}

Team2::Team2():Team(){}

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


