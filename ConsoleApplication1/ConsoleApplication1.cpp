#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class VehicleType { BUS, CAR, TRUCK };

class Vehicle {
   private:
    int id;
    string company;
    string purchaseDate;
    string model;
    int totalMiles;
    double fuelPerMile;
    int maintenanceFee;
    int roadFee;
    double totalFee;
    VehicleType type;

   public:
    Vehicle()
        : id(0),
          company(""),
          purchaseDate(""),
          model(""),
          totalMiles(0),
          fuelPerMile(0.0),
          maintenanceFee(0),
          roadFee(0),
          totalFee(0.0),
          type(VehicleType::BUS) {}
    Vehicle(int id,
            const string& company,
            const string& purchaseDate,
            const string& model,
            int totalMiles,
            double fuelPerMile,
            VehicleType type)
        : id(id),
          company(company),
          purchaseDate(purchaseDate),
          model(model),
          totalMiles(totalMiles),
          fuelPerMile(fuelPerMile),
          type(type) {
        setMaintenanceFee(type);
        roadFee = 500;
        calculateTotalFee();
    }

    void setMaintenanceFee(VehicleType type) {
        switch (type) {
            case VehicleType::BUS:
                maintenanceFee = 2000;
                break;
            case VehicleType::CAR:
                maintenanceFee = 1000;
                break;
            case VehicleType::TRUCK:
                maintenanceFee = 1500;
                break;
        }
    }

    void calculateTotalFee() {
        totalFee = fuelPerMile * totalMiles + maintenanceFee + roadFee;
    }
    int getId() const { return id; }

    // getCompany方法
    const string& getCompany() const { return company; }

    // getPurchaseDate方法
    const string& getPurchaseDate() const { return purchaseDate; }

    // getModel方法
    const string& getModel() const { return model; }

    // getTotalMiles方法
    int getTotalMiles() const { return totalMiles; }

    // getFuelPerMile方法
    double getFuelPerMile() const { return fuelPerMile; }

    // getMaintenanceFee方法
    int getMaintenanceFee() const { return maintenanceFee; }

    // getRoadFee方法
    int getRoadFee() const { return roadFee; }

    // getTotalFee方法
    double getTotalFee() const { return totalFee; }

    // getType方法
    VehicleType getType() const { return type; }

    void updateTotalMiles(int additionalMiles) {
        totalMiles += additionalMiles;
        calculateTotalFee();
    }
    friend ostream& operator<<(ostream& out, const Vehicle& v);
    friend ifstream& operator>>(ifstream& in, Vehicle& v);
};

ostream& operator<<(ostream& out, const Vehicle& v) {
    out << "编号: " << v.id << ", 制造公司: " << v.company
        << ", 购买时间: " << v.purchaseDate << ", 型号: " << v.model
        << ", 总公里数: " << v.totalMiles << ", 耗油量/公里: " << v.fuelPerMile
        << ", 维护费用: " << v.maintenanceFee << ", 路费: " << v.roadFee
        << ", 累计费用: " << v.totalFee
        << ", 类型: " << static_cast<int>(v.type);
    return out;
}

ifstream& operator>>(ifstream& in, Vehicle& v) {
    in >> v.id >> v.company >> v.purchaseDate >> v.model >> v.totalMiles >>
        v.fuelPerMile;
    int typeInt;
    in >> typeInt;
    v.type = static_cast<VehicleType>(typeInt);  // 将整数值转换为枚举类型
    v.setMaintenanceFee(v.type);
    in >> v.roadFee;
    v.calculateTotalFee();
    return in;
}

void printMenu() {
    cout << "车辆管理系统" << endl;
    cout << "1. 增加车辆信息" << endl;
    cout << "2. 修改车辆信息" << endl;
    cout << "3. 删除车辆信息" << endl;
    cout << "4. 查询车辆信息" << endl;
    cout << "5. 车辆费用排序" << endl;
    cout << "6. 保存车辆信息" << endl;
    cout << "7. 读取车辆信息" << endl;
    cout << "8. 退出" << endl;
}
// 全局车辆列表
vector<Vehicle> vehicles;

void addVehicle() {
    int id;
    cout << "输入车辆编号: ";
    cin >> id;
    cin.ignore();  // 忽略换行符
    string company, purchaseDate, model;
    cout << "输入车辆制造公司: ";
    getline(cin, company);
    cout << "输入购买时间: ";
    cin >> purchaseDate;
    cout << "输入型号: ";
    cin >> model;
    int totalMiles;
    cout << "输入总公里数: ";
    cin >> totalMiles;
    double fuelPerMile;
    cout << "输入耗油量/公里: ";
    cin >> fuelPerMile;
    int type;
    cout << "输入车辆类型(1:客车 2:小轿车 3:卡车): ";
    cin >> type;

    // 创建车辆实例并添加到车辆列表中
    VehicleType vehicleType = static_cast<VehicleType>(type - 1);
    Vehicle newVehicle(id, company, purchaseDate, model, totalMiles,
                       fuelPerMile, vehicleType);
    vehicles.push_back(newVehicle);
}

void modifyVehicle() {
    int id;
    cout << "输入要修改的车辆编号: ";
    cin >> id;

    // 查找具有指定ID的车辆
    auto it = find_if(vehicles.begin(), vehicles.end(),
                      [id](const Vehicle& v) { return v.getId() == id; });

    if (it != vehicles.end()) {
        // 如果找到了车辆，请求用户输入新的当月公里数
        int additionalMiles;
        cout << "输入新的当月公里数: ";
        cin >> additionalMiles;

        // 更新车辆的总公里数和总费用
        it->updateTotalMiles(additionalMiles);
        cout << "车辆信息已更新" << endl;
    } else {
        // 如果没有找到车辆，显示错误消息
        cout << "未找到编号为 " << id << " 的车辆" << endl;
    }
}

void deleteVehicle() {
    int id;
    cout << "输入要删除的车辆编号: ";
    cin >> id;

    // 查找具有指定ID的车辆
    auto it = find_if(vehicles.begin(), vehicles.end(),
                      [id](const Vehicle& v) { return v.getId() == id; });

    if (it != vehicles.end()) {
        // 如果找到了车辆，从列表中删除它
        vehicles.erase(it);
        cout << "车辆已删除" << endl;
    } else {
        // 如果没有找到车辆，显示错误消息
        cout << "未找到编号为 " << id << " 的车辆" << endl;
    }
}

void queryVehicle() {
    int id;
    cout << "输入要查询的车辆编号: ";
    cin >> id;

    // 查找具有指定ID的车辆
    auto it = find_if(vehicles.begin(), vehicles.end(),
                      [id](const Vehicle& v) { return v.getId() == id; });

    if (it != vehicles.end()) {
        // 如果找到了车辆，显示车辆信息
        cout << *it << endl;
    } else {
        // 如果没有找到车辆，显示错误消息
        cout << "未找到编号为 " << id << " 的车辆" << endl;
    }
}

void sortVehicle() {
    // 根据累计费用从低到高排序车辆列表
    sort(vehicles.begin(), vehicles.end(),
         [](const Vehicle& a, const Vehicle& b) {
             return a.getTotalFee() < b.getTotalFee();
         });
    cout << "按累计费用从低到高排序后的车辆信息:" << endl;
    for (const auto& v : vehicles) {
        cout << v << endl;
    }
}

void saveVehicle() {
    ofstream out("vehicles.txt");
    for (const auto& v : vehicles) {
        // 将车辆信息写入文件
        out << v.getId() << " " << v.getCompany() << " " << v.getPurchaseDate()
            << " " << v.getModel() << " " << v.getTotalMiles() << " "
            << v.getFuelPerMile() << " " << v.getMaintenanceFee() << " "
            << v.getRoadFee() << " " << v.getTotalFee() << " "
            << static_cast<int>(v.getType()) << endl;
    }
    cout << "车辆信息已保存到文件" << endl;
}

void readVehicle() {
    ifstream in("vehicles.txt");
    if (!in.is_open()) {
        cout << "无法打开文件" << endl;
        return;
    }
    vehicles.clear();
    Vehicle v;
    while (in >> v) {  // 使用重载的输入运算符
        vehicles.push_back(v);
    }
    if (in.fail() && !in.eof()) {
        cout << "读取文件时发生错误" << endl;
    } else {
        cout << "车辆信息已从文件读取" << endl;
    }
}

int main() {
    while (true) {
        printMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                addVehicle();
                break;
            case 2:
                modifyVehicle();
                break;
            case 3:
                deleteVehicle();
                break;
            case 4:
                queryVehicle();
                break;
            case 5:
                sortVehicle();
                break;
            case 6:
                saveVehicle();
                break;
            case 7:
                readVehicle();
                break;
            case 8:
                return 0;
        }
    }
}
