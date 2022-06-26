#include "common_implement.h"
int syncImitate[N] = {0};
int syncCnt = 0;
int syncFlag = 0;
void syncImitateChange() {
    // PgUp, PgDn模拟滚轮
    if (pressing(VK_PRIOR)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, MOUSE_SPEED, 0);
    } else if (pressing(VK_NEXT)) {
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -MOUSE_SPEED, 0);
    }
    if (curTime >= syncImitate[syncFlag]) {
        syncFlag++;
        // 小键盘模拟视角变换
        if (pressing(VK_LEFT)) {
            mouse_event(MOUSEEVENTF_MOVE, -MOUSE_SPEED, 0, 0, 0);
        } else if (pressing(VK_RIGHT)) {
            mouse_event(MOUSEEVENTF_MOVE, MOUSE_SPEED, 0, 0, 0);
        } else if (pressing(VK_UP)) {
            mouse_event(MOUSEEVENTF_MOVE, 0, -MOUSE_SPEED, 0, 0);
        } else if (pressing(VK_DOWN)) {
            mouse_event(MOUSEEVENTF_MOVE, 0, MOUSE_SPEED, 0, 0);
        }
    }
}