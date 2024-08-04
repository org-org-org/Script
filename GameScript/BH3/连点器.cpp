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
void event1() {
    pressKey(key);
}
int main() {
    initMap();
    INT8 hitF = 0;
    while (1) {
        checkPressedKeyUntilNextPressed(192, event1);
        Sleep(SLEEP_DURATION);
    }
    return 0;
}
