#include "../../common/common_implement.h"
int main() {
    loadAllKeys();
    while (!pressing(VK_F4)) {
        init();
        int i = 0;
        while (i < inputNum) {
            if (pressing(endKey)) { // 按F9中途结束
                clearPressingState();
                break;
            }
            curTime = Now() - start;
            while (i < inputNum && curTime >= inputTime[i]) {
                if (inputKey[i] <= 0) { // 鼠标移动
                    mouseMove(i);
                } else if (inputType[i] == 0) {
                    pressDown(inputKey[i]);
                } else if (inputType[i] == 2) {
                    pressUp(inputKey[i]);
                }
                i++;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    return 0;
}