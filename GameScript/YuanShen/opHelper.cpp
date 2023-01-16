#include "../../common/sync_implement.h"
string TXT_DIR = "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/";
vector<BYTE>endKeys{VK_F6};
vector<BYTE>pauseKeys = {VK_F7, VK_MENU, VK_TAB, 'M', 'B', 'C', 'L', VK_RETURN};
void pressKey(BYTE vKey) {
    static BYTE cnt[256] = {0};
    if (cnt[vKey] == 6) {
        pressDown(vKey);
    } else if (cnt[vKey] == 12) {
        pressUp(vKey);
        cnt[vKey] = 0;
    }
    cnt[vKey]++;
}
void selfEvent() {
    for (int i = 0; i <= 9; i++) { // 小键盘0到9的自定义事件
        if (pressing(VK_NUMPAD0 + i)) {
            string fileName = to_string(i) + ".txt";
            loadFile(fileName, TXT_DIR);
            syncEvent();
            return;
        }
    }
}
int main(int argc, char* argv[]) {
    loadAllKeys();
    if (argc == 2) {
        TXT_DIR = argv[1];
    }
    INT8 hitF = 0;
    while (1) {
        if (pressing(VK_ADD)) { // 小键盘+
            hitF = 1;
        } else if (pressing(VK_SUBTRACT)) { // 小键盘-
            hitF = 0;
        } else if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
        if (hitF) {
            pressKey('F');
        }
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}