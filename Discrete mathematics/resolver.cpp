#include <math.h>
#include <iostream>
using namespace std;

int main() {
    cout << "请输入顶点数: ";
    int dot;
    cin >> dot;
    int adj[dot][dot], b[dot][dot], c[dot][dot],
        acc[dot][dot];  // 邻接矩阵与可达矩阵
    cout << "请按次序输入每行数据，形成此图的邻接矩阵 (" << dot << "*" << dot
         << "矩阵" << "): " << endl;
    for (int i = 0; i < dot; i++)  // 邻接矩阵赋值
    {
        for (int j = 0; j < dot; j++) {
            cin >> adj[i][j];
            acc[i][j] = adj[i][j];
            b[i][j] = acc[i][j];
            c[i][j] = acc[i][j];
        }
        getchar();
    }

    int sum, x = 2;  // 求邻接矩阵2~n-1次方对应每个点之和
    while (x < dot) {
        cout << "矩阵的" << x << "次方为: " << endl;
        for (int i = 0; i < dot; i++) {
            for (int j = 0; j < dot; j++) {
                sum = 0;
                for (int k = 0; k < dot; k++) {
                    sum +=
                        abs(b[i][k]) *
                        abs(adj[k][j]);  // 有向图中有-1表示反向，所以加上绝对值
                }
                c[i][j] = sum;
                acc[i][j] += c[i][j];
                cout << c[i][j] << " ";
            }  // j
            cout << endl;
            for (int i = 0; i < dot; i++) {
                for (int j = 0; j < x; j++) {
                    b[i][j] = c[i][j];
                }
            }
        }  // i
        ++x;
    }  // while

    for (int i = 0; i < dot; i++)  // 形成此图的可达矩阵
    {
        for (int j = 0; j < x; j++) {
            if (acc[i][j] || i == j)
                acc[i][j] = 1;
        }
    }

    cout << "此图的可达矩阵为: " << endl;
    for (int i = 0; i < dot; i++) {
        for (int j = 0; j < dot; j++) {
            cout << acc[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < dot; i++)  // 判断是否为强连通图
    {
        for (int j = 0; j < dot; j++) {
            if (!acc[i][j]) {
                cout << "此图是非强连通图！" << endl;
                return 0;
            }
        }
    }
    cout << "此图为强联通图!" << endl;
}