#include "../../common/sync_implement.h"
string TXT_DIR = "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/";
void pauseEvent() {
    vector<BYTE>pauseKeys = {VK_F7, VK_MENU, VK_TAB, 'M', 'B', 'C', 'L', VK_RETURN};
    checkPause(pauseKeys, {VK_F6, VK_F4});
}
void selfEvent() {
    for (int i = 0; i <= 9; i++) { // 小键盘0到9的自定义事件
        if (pressing(VK_NUMPAD0 + i)) {
            string fileName = to_string(i) + ".txt";
            loadFile(fileName, TXT_DIR);
            syncEvent();
            pause({VK_F6, VK_F4});
            return;
        }
    }
}
int main(int argc, char* argv[]) {
    loadAllKeys();
    if (argc == 2) {
        TXT_DIR = argv[1];
    }
    pause({VK_F6, VK_F4});
    while (!pressing(VK_F4)) {
        pauseEvent();
        pressKey('F');
        if (pressing('N')) {
            pressDown('W');
        }
        selfEvent();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}