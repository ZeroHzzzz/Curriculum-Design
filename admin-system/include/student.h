#ifndef MODEL_H
#define MODEL_H

#include <ctime>
#include <string>
int parseTimeToMinutes(const std::string&);
int getMinuteDifference(const std::string&, const std::string&);

class Info {
   public:
    Info();
    ~Info();
    const std::string& getName() const;
    const std::string& getNum() const;
    const std::string& getClassName() const;
    const std::string& getMachineNum() const;
    const std::string& getBeginTime() const;
    const std::string& getEndTime() const;
    const int& getTotalTime() const;
    const double& getCost() const;

    void setName(const std::string& name);
    void setNum(const std::string& num);
    void setClassName(const std::string& className);
    void setMachineNum(const std::string& machineNum);
    void setBeginTime(const std::string& beginTime);
    void setEndTime(const std::string& endTime);

    void setTotalTime();
    void calculateCost(const int& totalTime);

    friend std::istream& operator>>(std::istream& in, Info& right);
    // friend std::ifstream& operator>>(std::ifstream& in, Info& right);
    friend std::ostream& operator<<(std::ostream& out, const Info& right);

   private:
    std::string name = "-";
    std::string num = "-";
    std::string className = "-";
    std::string machineNum = "-";
    std::string beginTime = "-";
    std::string endTime = "-";
    int totalTime = 0;
    double cost = 0;
};

#endif  // STUDENT_H
