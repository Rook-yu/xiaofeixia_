#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>

using namespace std;

// 武士类型及其初始生命值
struct WarriorStats {
    int dragon;
    int ninja;
    int iceman;
    int lion;
    int wolf;
};

// 武器名称映射
const string weaponNames[3] = {"sword", "bomb", "arrow"};

// 红方和蓝方的武士制造顺序
const int redOrder[5] = {2, 3, 4, 1, 0};    // iceman, lion, wolf, ninja, dragon
const int blueOrder[5] = {3, 0, 1, 2, 4};   // lion, dragon, ninja, iceman, wolf

// 武士类型名称
const string warriorNames[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

// 司令部类
class Headquarter {
private:
    string color;               // 颜色
    int lifeElements;           // 剩余生命元
    int warriorCount[5];        // 各类武士数量
    int totalWarriors;          // 总武士数
    int nextToMake;             // 下一个要制造的武士索引
    bool stopped;               // 是否停止制造
    const int* makeOrder;       // 制造顺序

public:
    Headquarter(string c, int m, const int* order) 
        : color(c), lifeElements(m), nextToMake(0), stopped(false), makeOrder(order) {
        for (int i = 0; i < 5; ++i) {
            warriorCount[i] = 0;
        }
        totalWarriors = 0;
    }

    // 尝试制造武士，返回是否成功
    bool makeWarrior(int time, const WarriorStats& stats) {
        if (stopped) return false;

        int start = nextToMake;
        int cost_check;  // 重命名变量，避免与后面的cost重名
        bool found = false;
        int type_found = -1;
        int cost_found = 0;

        // 查找可以制造的武士
        do {
            int type = makeOrder[nextToMake];
            switch (type) {
                case 0: cost_check = stats.dragon; break;
                case 1: cost_check = stats.ninja; break;
                case 2: cost_check = stats.iceman; break;
                case 3: cost_check = stats.lion; break;
                case 4: cost_check = stats.wolf; break;
            }

            if (lifeElements >= cost_check) {
                found = true;
                type_found = type;
                cost_found = cost_check;
                break;
            }

            nextToMake = (nextToMake + 1) % 5;
        } while (nextToMake != start);

        if (!found) {
            // 无法制造任何武士，输出停止信息
            printf("%03d %s headquarter stops making warriors\n", time, color.c_str());
            stopped = true;
            return false;
        }

        // 制造武士
        int type = type_found;
        int cost = cost_found;

        lifeElements -= cost;
        totalWarriors++;
        warriorCount[type]++;

        // 输出武士降生信息
        printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
               time, color.c_str(), warriorNames[type].c_str(), totalWarriors,
               cost, warriorCount[type], warriorNames[type].c_str(), color.c_str());

        // 输出特殊属性
        switch (type) {
            case 0: { // dragon
                int weapon = totalWarriors % 3;
                double morale = static_cast<double>(lifeElements) / cost;
                printf("It has a %s,and it's morale is %.2f\n",
                       weaponNames[weapon].c_str(), morale);
                break;
            }
            case 1: { // ninja
                int weapon1 = totalWarriors % 3;
                int weapon2 = (totalWarriors + 1) % 3;
                printf("It has a %s and a %s\n",
                       weaponNames[weapon1].c_str(), weaponNames[weapon2].c_str());
                break;
            }
            case 2: { // iceman
                int weapon = totalWarriors % 3;
                printf("It has a %s\n", weaponNames[weapon].c_str());
                break;
            }
            case 3: { // lion
                printf("It's loyalty is %d\n", lifeElements);
                break;
            }
            // wolf 没有特殊属性
        }

        nextToMake = (nextToMake + 1) % 5;
        return true;
    }

    bool isStopped() const { return stopped; }
};

int main() {
    int t;
    cin >> t;

    for (int caseNum = 1; caseNum <= t; ++caseNum) {
        int M;
        cin >> M;

        WarriorStats stats;
        cin >> stats.dragon >> stats.ninja >> stats.iceman >> stats.lion >> stats.wolf;

        Headquarter red("red", M, redOrder);
        Headquarter blue("blue", M, blueOrder);

        cout << "Case:" << caseNum << endl;

        int time = 0;
        while (true) {
            red.makeWarrior(time, stats);
            blue.makeWarrior(time, stats);

            if (red.isStopped() && blue.isStopped()) {
                break;
            }

            time++;
        }
    }

    return 0;
}
