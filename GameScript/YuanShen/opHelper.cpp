#include "../../common/sync_implement.h"
string TXT_DIR = "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/";
void pauseEvent() {
    vector<BYTE>pauseKeys = {VK_F7, VK_MENU, VK_TAB, 'M', 'B', 'C', 'L', VK_RETURN};
    checkPause(pauseKeys, {VK_F6, VK_F4});
}
void selfEvent() {
    int flag = 0;
    if (pressing(VK_NUMPAD0)) { // 小键盘0 登录
        loadFile("log_on.txt", TXT_DIR);
        flag = 1;
    }
    if (pressing('H')) { // 领每日
        loadFile("daily_task.txt", TXT_DIR);
        flag = 1;
    }
    if (flag) {
        syncEvent();
        pause({VK_F6, VK_F4});
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