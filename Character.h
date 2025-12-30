#pragma once
#include <iostream>
#include <string>

class Character {
private:
    std::string _Name;
    int _Level;
    int _Health;
    int _MaxHealth;
    int _Attack;
    int _Experence;
    int _Gold;

public:
    Character(std::string name);

    int GetLevel() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetExperence() const;
    int GetGold() const;

    void SetLevel();
    void SetHealth(int amount); 
    void LevelUp();         
    void GainExperience(int exp);
    void GainGold(int gold);

    void ShowStatus() const;
};