#include "./common/common_implement.h"
#include <unordered_map>
unordered_map<string, int>m;
int key;
void init() {
    m["LB"] = 1, m["RB"] = 2, m["MB"] = 4;
    for (int i = 0; i <= 9; i++) {
        m[to_string(i)] = 48 + i;
    }
    for (int i = 0; i < 26; i++) {
        string ch(1, 'A' + i);
        m[ch] = 65 + i;
    }
    string str;
    cout << "input the key to hit\n";
    getline(cin, str);
    while (m.find(str) == m.end()) {
        cout << "wrong key, please input again\n";
        cin >> str;
    }
    key = m[str];
    cout << "then press F8 to start and press F9 to stop or press F7 to quit\n";
}
int main() {
    init();
    while (1) {
        while (!pressing(beginKey)) { // 按F8开始
            if (GetAsyncKeyState(VK_F7)) {
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
        while (!pressing(endKey)) { // 按F9停止
            if (GetAsyncKeyState(VK_F7)) {
                return 0;
            }
            press(key);
        }
    }
    return 0;
}