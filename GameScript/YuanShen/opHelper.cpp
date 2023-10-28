#include "../../common/sync_implement.h"
string TXT_DIR = "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/";
vector<BYTE>endKeys{VK_F6};
vector<BYTE>pauseKeys = {VK_F7, VK_MENU, VK_TAB, 'M', 'B', 'C', 'L', VK_RETURN};
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
        if (pressing(VK_DECIMAL)) { // 小键盘.
            pressDown('W');
        }
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
            if (hitF >= 18) {
                pressKey('F');
                hitF = 1;
            }
        }
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}