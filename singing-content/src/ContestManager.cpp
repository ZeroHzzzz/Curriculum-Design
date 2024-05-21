#include "../include/ContestManager.h"
#include <algorithm>
#include <iomanip>

void ContestManager::calculateScores(Contestant& contestant) {
    if (contestant.scores.size() != 10)
        return;
    double total = 0;
    double maxScore =
        *std::max_element(contestant.scores.begin(), contestant.scores.end());
    double minScore =
        *std::min_element(contestant.scores.begin(), contestant.scores.end());

    for (double score : contestant.scores) {
        total += score;
    }

    contestant.totalScore = total - maxScore - minScore;
    contestant.averageScore = contestant.totalScore / 8;
}

void ContestManager::displayContestant(const Contestant& contestant) {
    std::cout << "选手ID: " << contestant.id << ", 姓名: " << contestant.name
              << ", 选手成绩: ";
    if (contestant.scores.size() == 0) {
        std::cout << "-" << " ";
    } else {
        std::cout << "{ ";
        for (double score : contestant.scores) {
            std::cout << score << " ";
        }
        std::cout << "}";
    }

    std::cout << ", 总成绩: " << contestant.totalScore
              << ", 平均成绩: " << contestant.averageScore << std::endl;
}

void ContestManager::addContestant() {
    Contestant contestant;
    std::cout << "输入选手 ID" << std::endl << ">";
    std::cin >> contestant.id;
    std::cout << "输入选手姓名" << std::endl << ">";
    std::cin >> contestant.name;
    contestants.push_back(contestant);
}

void ContestManager::modifyContestant() {
    std::string id;
    std::cout << "输入选手 ID" << std::endl << ">";
    std::cin >> id;
    for (auto& contestant : contestants) {
        if (contestant.id == id) {
            std::cout << "输入新的名字: ";
            std::cin >> contestant.name;
            return;
        }
    }
    std::cout << "Contestant not found!" << std::endl;
}

void ContestManager::deleteContestant() {
    std::string id;
    std::cout << "输入选手 ID" << std::endl << ">";
    std::cin >> id;
    contestants.erase(std::remove_if(contestants.begin(), contestants.end(),
                                     [id](Contestant& contestant) {
                                         return contestant.id == id;
                                     }),
                      contestants.end());
}

void ContestManager::judgeContestant() {
    if (contestants.size() == 0)
        return;
    std::string id;
    std::cout << "输入选手 ID " << std::endl << ">";
    std::cin >> id;
    for (auto& contestant : contestants) {
        if (contestant.id == id) {
            if (contestant.scores.size() != 0) {
                std::cout << "该选手已有评委评分，确定覆盖？(y/n):";
                char type;
                while (std::cin >> type) {
                    if (type == 'y') {
                        contestant.scores.clear();
                        std::cout << "依次输入十个分数: ";
                        for (int i = 0; i < 10; i++) {
                            double score;
                            std::cin >> score;
                            contestant.scores.push_back(score);
                        }
                        calculateScores(contestant);
                        return;
                    } else {
                        return;
                    }
                }
            } else {
                contestant.scores.clear();
                std::cout << "依次输入十个分数: ";
                for (int i = 0; i < 10; i++) {
                    double score;
                    std::cin >> score;
                    contestant.scores.push_back(score);
                }
                calculateScores(contestant);
                return;
            }
        }
    }
    std::cout << "未找到该选手" << std::endl;
}

void ContestManager::sortContestants() {
    std::cout << "排序依据：" << std::endl
              << "1. 总成绩" << std::endl
              << "2. 平均成绩 " << std::endl
              << ">";
    int option;
    std::cin >> option;
    if (option == 1) {
        std::sort(contestants.begin(), contestants.end(),
                  [](const Contestant& a, const Contestant& b) {
                      return a.totalScore > b.totalScore;
                  });
    } else if (option == 2) {
        std::sort(contestants.begin(), contestants.end(),
                  [](const Contestant& a, const Contestant& b) {
                      return a.averageScore > b.averageScore;
                  });
    }
}

void ContestManager::sortByJudgeScore() {
    int judgeIndex;
    std::cout << "输入用于排序的评委编号: " << std::endl << ">";
    while (std::cin >> judgeIndex) {
        if (judgeIndex < 0 || judgeIndex > 9) {
            std::cout << "输入错误！请重新输入" << std::endl << "<";
        } else {
            std::sort(contestants.begin(), contestants.end(),
                      [judgeIndex](const Contestant& a, const Contestant& b) {
                          return a.scores[judgeIndex] > b.scores[judgeIndex];
                      });
            break;
        }
    }
    return;
}

void ContestManager::displayAllContestants() {
    if (contestants.size() == 0)
        std::cout << "当前无选手信息" << std::endl;
    else {
        for (const auto& contestant : contestants) {
            displayContestant(contestant);
        }
    }
}

void ContestManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& contestant : contestants) {
        file << contestant.id << " " << contestant.name << " ";
        if (contestant.scores.size() == 0) {
            for (int i = 0; i < 10; i++) {
                file << 0.0 << " ";
            }
        } else {
            for (double score : contestant.scores) {
                file << score << " ";
            }
        }
        file << contestant.totalScore << " " << contestant.averageScore
             << std::endl;
    }
    std::cout << "保存文件成功!" << std::endl;
    file.close();
}

void ContestManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    contestants.clear();
    while (file) {
        Contestant contestant;
        file >> contestant.id >> contestant.name;
        contestant.scores.resize(10);
        for (double& score : contestant.scores) {
            file >> score;
        }
        file >> contestant.totalScore >> contestant.averageScore;
        if (file) {
            contestants.push_back(contestant);
        }
    }
    std::cout << "文件载入成功！" << std::endl;
    file.close();
}
