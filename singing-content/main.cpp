#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

struct Contestant {
    string id;
    string name;
    vector<double> scores;
    double totalScore = 0;
    double averageScore = 0;
};

class ContestManager {
   private:
    vector<Contestant> contestants;
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
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};

void ContestManager::calculateScores(Contestant& contestant) {
    if (contestant.scores.size() != 10)
        return;
    double total = 0;
    double maxScore =
        *max_element(contestant.scores.begin(), contestant.scores.end());
    double minScore =
        *min_element(contestant.scores.begin(), contestant.scores.end());

    for (double score : contestant.scores) {
        total += score;
    }

    contestant.totalScore = total - maxScore - minScore;
    contestant.averageScore = contestant.totalScore / 8;
}

void ContestManager::displayContestant(const Contestant& contestant) {
    cout << "选手ID: " << contestant.id << ", 姓名: " << contestant.name
         << ", 选手成绩: ";
    if (contestant.scores.size() == 0) {
        cout << "-" << " ";
    } else {
        cout << "{ ";
        for (double score : contestant.scores) {
            cout << score << " ";
        }
        cout << "}";
    }

    cout << ", 总成绩: " << contestant.totalScore
         << ", 平均成绩: " << contestant.averageScore << endl;
}

void ContestManager::addContestant() {
    Contestant contestant;
    cout << "输入选手 ID" << endl << ">";
    cin >> contestant.id;
    cout << "输入选手姓名" << endl << ">";
    cin >> contestant.name;
    contestants.push_back(contestant);
}

void ContestManager::modifyContestant() {
    string id;
    cout << "输入选手 ID" << endl << ">";
    cin >> id;
    for (auto& contestant : contestants) {
        if (contestant.id == id) {
            cout << "输入新的名字: ";
            cin >> contestant.name;
            return;
        }
    }
    cout << "Contestant not found!" << endl;
}

void ContestManager::deleteContestant() {
    string id;
    cout << "输入选手 ID" << endl << ">";
    cin >> id;
    contestants.erase(
        remove_if(contestants.begin(), contestants.end(),
                  [id](Contestant& contestant) { return contestant.id == id; }),
        contestants.end());
}

void ContestManager::judgeContestant() {
    string id;
    cout << "输入选手 ID " << endl << ">";
    cin >> id;
    for (auto& contestant : contestants) {
        if (contestant.id == id) {
            if (contestant.scores.size() != 0) {
                cout << "该选手已有评委评分，确定覆盖？(y/n):";
                char type;
                while (cin >> type) {
                    if (type == 'y') {
                        contestant.scores.clear();
                        cout << "依次输入十个分数: ";
                        for (int i = 0; i < 10; i++) {
                            double score;
                            cin >> score;
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
                cout << "依次输入十个分数: ";
                for (int i = 0; i < 10; i++) {
                    double score;
                    cin >> score;
                    contestant.scores.push_back(score);
                }
                calculateScores(contestant);
                return;
            }
        }
    }
    cout << "未找到该选手" << endl;
}

void ContestManager::sortContestants() {
    cout << "排序依据：" << endl
         << "1. 总成绩" << endl
         << "2. 平均成绩 " << endl
         << ">";
    int option;
    cin >> option;
    if (option == 1) {
        sort(contestants.begin(), contestants.end(),
             [](const Contestant& a, const Contestant& b) {
                 return a.totalScore > b.totalScore;
             });
    } else if (option == 2) {
        sort(contestants.begin(), contestants.end(),
             [](const Contestant& a, const Contestant& b) {
                 return a.averageScore > b.averageScore;
             });
    }
}

void ContestManager::sortByJudgeScore() {
    int judgeIndex;
    cout << "输入用于排序的评委编号: " << endl << ">";
    while (cin >> judgeIndex) {
        if (judgeIndex < 0 || judgeIndex > 9) {
            cout << "输入错误！请重新输入" << endl << "<";
        } else {
            sort(contestants.begin(), contestants.end(),
                 [judgeIndex](const Contestant& a, const Contestant& b) {
                     return a.scores[judgeIndex] > b.scores[judgeIndex];
                 });
            break;
        }
    }
    return;
}

void ContestManager::displayAllContestants() {
    for (const auto& contestant : contestants) {
        displayContestant(contestant);
    }
}

void ContestManager::saveToFile(const string& filename) {
    ofstream file(filename);
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
        file << contestant.totalScore << " " << contestant.averageScore << endl;
    }
    file.close();
}

void ContestManager::loadFromFile(const string& filename) {
    ifstream file(filename);
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
    file.close();
}

void displayMainMenu() {
    cout << endl;
    cout << setw(20) << setfill('-') << "-" << endl;
    cout << "请输入你的选择: " << endl;
    cout << "1. 选手管理" << endl;
    cout << "2. 评委评分" << endl;
    cout << "3. 选手排序" << endl;
    cout << "4. 选手展示" << endl;
    cout << "5. 文件操作" << endl;
    cout << "0. 退出系统" << endl;
    cout << ">";
}

void displayManageMenu() {
    cout << endl;
    cout << setw(20) << setfill('-') << "-" << endl;
    cout << "请输入你的选择: " << endl;
    cout << "1. 添加选手" << endl;
    cout << "2. 修改选手信息" << endl;
    cout << "3. 删除选手" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << ">";
}

void displaySortMenu() {
    cout << endl;
    cout << setw(20) << setfill('-') << "-" << endl;
    cout << "请输入你的选择: " << endl;
    cout << "1. 按照总成绩和平均分排序" << endl;
    cout << "2. 按某一评委评分排序" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << ">";
}

void displayFileMenu() {
    cout << endl;
    cout << setw(20) << setfill('-') << "-" << endl;
    cout << "请输入你的选择: " << endl;
    cout << "1. 保存到文件" << endl;
    cout << "2. 从文件中加载" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << ">";
}

int main() {
    ContestManager manager;
    int choice = 0;
    string filename;
    displayMainMenu();
    while (cin >> choice) {
        switch (choice) {
            case 0: {
                cout << "还没有保存，确定要退出吗(y/n):";
                char type;
                while (cin >> type) {
                    if (type == 'y')
                        return 0;
                    else
                        break;
                }
                break;
            }
            case 1: {
                displayManageMenu();
                int subChoice = 0;
                while (cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1: {
                            manager.addContestant();
                            break;
                        }
                        case 2: {
                            manager.modifyContestant();
                            break;
                        }
                        case 3: {
                            manager.deleteContestant();
                            break;
                        }
                        default: {
                            cout << "非法输入，请重新输入：" << endl << ">";
                            break;
                        }
                    }
                    if (subChoice)
                        displayManageMenu();
                }
                break;
            }
            case 2: {
                manager.judgeContestant();
                break;
            }
            case 3: {
                displaySortMenu();
                int subChoice = 0;
                while (cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1:
                            manager.sortContestants();
                            break;
                        case 2:
                            manager.sortByJudgeScore();
                            break;
                        default:
                            cout << "非法输入，请重新输入：" << endl << ">";
                    }
                    if (subChoice)
                        displaySortMenu();
                }
                break;
            }
            case 4: {
                manager.displayAllContestants();
                break;
            }
            case 5: {
                displayFileMenu();
                int subChoice = 0;
                while (cin >> subChoice && subChoice) {
                    switch (subChoice) {
                        case 1: {
                            cout << "输入文件名：" << endl << ">";
                            cin >> filename;
                            manager.saveToFile(filename);
                            break;
                        }
                        case 2: {
                            cout << "输入文件名：" << endl << ">";
                            cin >> filename;
                            manager.loadFromFile(filename);
                            break;
                        }
                        default:
                            cout << "非法输入，请重新输入：" << endl << ">";
                    }
                    if (subChoice)
                        displayFileMenu();
                }
                break;
            }
            default: {
                cout << "非法输入，请重新输入：" << endl << ">";
                break;
            }
        }
        displayMainMenu();
    }
    return 0;
}