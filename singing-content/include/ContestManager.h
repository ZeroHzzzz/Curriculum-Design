#ifndef CONTESTMANAGER_H
#define CONTESTMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Contestant {
    std::string id;
    std::string name;
    std::vector<double> scores;
    double totalScore = 0;
    double averageScore = 0;
};

class ContestManager {
   private:
    std::vector<Contestant> contestants;
    void calculateScores(Contestant& contestant);
    void displayContestant(const Contestant& contestant);

   public:
    void addContestant();
    void modifyContestant();
    void deleteContestant();
    void judgeContestant();
    void sortContestants();
    void sortByJudgeScore();
    void displayAllContestants();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif  // CONTESTMANAGER_H
