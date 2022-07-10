#include "./common/common_implement.h"
#include <map>
map<string, int>m;
int key;
void init() {
    m["LB"] = 1, m["RB"] = 2, m["MB"] = 4;
    for (int i = 0; i <= 9; i++) {
        m[to_string(i)] = 48 + i;
    }
    for (int i = 0; i < 26; i++) {
        char ch = 'A' + i;
        string str(1, ch);
        m[str] = 65 + i;
    }
    string str;
    cout << "input the key to hit\n";
    getline(cin, str);
    while (m.find(str) == m.end()) {
        cout << "wrong key, please input again\n";
        cin >> str;
    }
    key = m[str];
    cout << "then press F8 to start and press F9 to stop\n";
}
int main() {
    init();
    while (!pressing(beginKey)) { // 按F8开始
        Sleep(SLEEP_DURATION);
    }
    while (!pressing(endKey)) { // 按F9停止
        press(key);
    }
    return 0;
}