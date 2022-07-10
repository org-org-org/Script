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
    curTime = Now() - start;
    if (curTime >= syncImitate[syncFlag]) {
        syncFlag++;
        imitateChange();
    }
}