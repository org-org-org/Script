#include "../../common/common_implement.h"
#include <unordered_map>
unordered_map<string, int>m;
int key;
void init() {
    m["LB"] = 1, m["RB"] = 2, m["MB"] = 4;
    for (int i = 0; i <= 9; i++) {
        m[to_string(i)] = 48 + i;
    }
    for (int i = 0; i < 26; i++) {
        m[string(1, 'A' + i)] = 65 + i;
        m[string(1, 'a' + i)] = 65 + i;
    }
    // string str;
    // cout << "input the key to hit\n";
    // getline(cin, str);
    // while (m.find(str) == m.end()) {
    //     cout << "wrong key, please input again\n";
    //     cin >> str;
    // }
    // key = m[str];
    cout << "then press F8 to start and press F7 to pause or press F4 to stop\n";
}
void pauseEvent() {
    if (pressing(VK_F7) || pressing(VK_MENU) && pressing(VK_TAB)) {
        clearPressingState();
        while (!pressing(beginKey)) { // 按F8开始
            Sleep(SLEEP_DURATION);
        }
    }
    if (pressing(VK_ESCAPE)) {
        clearPressingState();
        while (!pressing(192)) { // 按 ` 开始
            Sleep(SLEEP_DURATION);
        }
    }
}
int main() {
    init();
    while (!pressing(beginKey)) { // 按F8开始
        Sleep(SLEEP_DURATION);
        if (pressing(VK_F4)) {
            return 0;
        }
    }
    while (!pressing(VK_F4)) {
        pressKey('J');
        // pressKey('U');
        // if (pressing('N')) {
        //     pressDown('J');
        //     Sleep(100);
        // }
        pauseEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}
