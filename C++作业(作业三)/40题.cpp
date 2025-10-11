#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(); 
    
    vector<multiset<int>> sequences(10000);
    
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string cmd;
        iss >> cmd;
        
        if (cmd == "new") {
            int id;
            iss >> id;
            sequences[id].clear(); // 确保新建时为空
        } else if (cmd == "add") {
            int id, num;
            iss >> id >> num;
            sequences[id].insert(num);
        } else if (cmd == "merge") {
            int id1, id2;
            iss >> id1 >> id2;
            if (id1 == id2) continue;
            
            multiset<int> &s1 = sequences[id1];
            multiset<int> &s2 = sequences[id2];
            
            if (s1.size() < s2.size()) {
                s2.insert(s1.begin(), s1.end());
                s1.clear();
                swap(s1, s2);
            } else {
                s1.insert(s2.begin(), s2.end());
                s2.clear();
            }
        } else if (cmd == "unique") {
            int id;
            iss >> id;
            multiset<int> &s = sequences[id];
            set<int> unique_set(s.begin(), s.end());
            s.clear();
            s.insert(unique_set.begin(), unique_set.end());
        } else if (cmd == "out") {
            int id;
            iss >> id;
            const multiset<int> &s = sequences[id];
            bool first = true;
            for (int num : s) {
                if (!first) cout << " ";
                cout << num;
                first = false;
            }
            cout << endl;
        }
    }
    
    return 0;
}