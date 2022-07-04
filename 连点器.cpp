#include "./common/common_implement.h"
int main() {
    while (!pressing(beginKey)) { // 按F8开始
        Sleep(SLEEP_DURATION);
    }
    while (!pressing(endKey)) { // 按F9停止
        press(1);
    }
    return 0;
}