#include "../../common/common_implement.h"
void init() {
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp = searchFile(fileName);
    cout << "then press F8 to implement and press F9 to stop\n";
    inputNum = 0;
    while (~fscanf(fp, "%d%d%d", &inputTime[inputNum], &inputKey[inputNum], &inputType[inputNum])) {
        inputNum++;
    }
    fclose(fp);
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    start = Now();
}
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