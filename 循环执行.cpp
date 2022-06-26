#include "./common/common_implement.h"
int main() {
    initLoopImplement();
    for (int T = 0; T < ROUND; T++) {
        if (waitToStart(T) == 0) {
            return 0;
        }
        start = Now();
        int i = 0;
        while (i < inputNum) {
            if (pressing(endKey)) { // 按F9直接结束本次
                clearPressingState();
                T--;
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