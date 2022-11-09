#include "../../common/sync_implement.h"
const string TXT_DIR = "D:/0_vscode_cpp/Script/GameScript/YuanShen/input/";
void pauseEvent() {
    if (pressing(VK_F7) || pressing(VK_MENU) && pressing(VK_TAB)) {
        pause({VK_F6, VK_F4});
    }
    if (pressing('M') || pressing('B') || pressing('C') || pressing('L') || pressing(VK_RETURN)) {
        pause({VK_ESCAPE, VK_F6, VK_F4});
    }
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
void init() {
    loadAllKeys();
}
int main() {
    init();
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