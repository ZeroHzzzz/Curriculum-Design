#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

void printAdjacencyMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// 生成强联通图
void generateStronglyConnectedGraph(vector<vector<int>>& adjMatrix, int n) {
    // 保证强连通
    for (int i = 0; i < n; ++i) {
        adjMatrix[i][(i + 1) % n] = 1;
    }

    // 添加随机路径
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && getRandomInt(0, 1) == 1) {
                adjMatrix[i][j] = 1;
            }
        }
    }
}

// 生成非强连通图
void generateNonStronglyConnectedGraph(vector<vector<int>>& adjMatrix, int n) {
    // Split the nodes into two sets to ensure non-strong connectivity
    int splitPoint = n / 2;

    for (int i = 0; i < splitPoint; ++i) {
        for (int j = 0; j < splitPoint; ++j) {
            if (i != j && getRandomInt(0, 1) == 1) {
                adjMatrix[i][j] = 1;
            }
        }
    }
    for (int i = splitPoint; i < n; ++i) {
        for (int j = splitPoint; j < n; ++j) {
            if (i != j && getRandomInt(0, 1) == 1) {
                adjMatrix[i][j] = 1;
            }
        }
    }

    // 添加随机边
    for (int i = 0; i < splitPoint; ++i) {
        for (int j = splitPoint; j < n; ++j) {
            if (getRandomInt(0, 1) == 1) {
                adjMatrix[i][j] = 1;
            }
        }
    }
}

int main() {
    srand(time(0));

    int n;
    bool isStronglyConnected =
        false;  // true 生成强连通图，false 生成非强联通图

    cout << "输入点的个数 > ";
    cin >> n;

    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    if (isStronglyConnected) {
        generateStronglyConnectedGraph(adjMatrix, n);
    } else {
        generateNonStronglyConnectedGraph(adjMatrix, n);
    }

    printAdjacencyMatrix(adjMatrix);

    return 0;
}
