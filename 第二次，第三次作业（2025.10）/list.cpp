#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 用哈希表存储id到序列的映射，序列使用list便于合并操作
    unordered_map<int, list<int>> seq_map;

    while (n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "new") {
            int id;
            cin >> id;
            // 若id不存在则创建空列表，存在则不操作
            seq_map[id];
        } 
        else if (cmd == "add") {
            int id, num;
            cin >> id >> num;
            // 向指定序列添加元素
            seq_map[id].push_back(num);
        } 
        else if (cmd == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            if (id1 == id2) continue; // 相同id不操作
            seq_map[id1].splice(seq_map[id1].end(), seq_map[id2]);
        } 
        else if (cmd == "unique") {
            int id;
            cin >> id;
            auto& lst = seq_map[id];
            // 先排序使重复元素相邻，再去重
            lst.sort();
            auto last = unique(lst.begin(), lst.end());
            lst.erase(last, lst.end());
        } 
        else if (cmd == "out") {
            int id;
            cin >> id;
            auto& lst = seq_map[id];
            // 复制到vector中排序
            vector<int> temp(lst.begin(), lst.end());
            sort(temp.begin(), temp.end());
            // 按格式输出
            for (size_t i = 0; i < temp.size(); ++i) {
                if (i > 0) cout << " ";
                cout << temp[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
