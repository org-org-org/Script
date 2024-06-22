#include "../../common/common_implement.cpp"
#include <unordered_map>
unordered_map<string, int>m;
int key = VK_NUMPAD1;
void initMap() {
    m["LB"] = 1, m["RB"] = 2, m["MB"] = 4;
    for (int i = 0; i <= 9; i++) {
        m[to_string(i)] = VK_NUMPAD0 + i;
    }
    for (int i = 0; i < 26; i++) {
        m[string(1, 'A' + i)] = 65 + i;
        m[string(1, 'a' + i)] = 65 + i;
    }
    cout << "input the key to hit\n";
    string str;
    cin >> str;
    while (m.find(str) == m.end()) {
        cout << "wrong key, please input again\n";
        cin >> str;
    }
    key = m[str];
}
int main() {
    initMap();
    INT8 hitF = 0;
    while (1) {
        if (pressing(192)) {
            if (pre[192] == 0) { // 之前没按着现在按着，按下
                pre[192] = 1;
            }
        } else {
            if (pre[192] == 1) { // 之前按着现在没按着，松开
                pre[192] = 0;
                hitF = !hitF;
            }
        }
        if (hitF) {
            hitF++;
            if (hitF > 9) {
                pressKey(key);
                hitF = 1;
            }
        }
        Sleep(SLEEP_DURATION);
    }
    return 0;
}
