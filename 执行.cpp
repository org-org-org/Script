#include "myhead.h"
void init() {
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp;
    while ((fp = findFile(fileName)) == NULL) {
        cout << "wrong filename, please input again\n";
        cin >> fileName;
    }
    cout << "then press F8 to implement and press F9 to stop\n";
    while (~fscanf(fp, "%d%d%d", &inputTime[inputNum], &inputKey[inputNum], &inputType[inputNum])) {
        inputNum++;
    }
    fclose(fp);
    while (!pressing(VK_F8)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    start = Now();
}
int main() {
    init();
    int i = 0;
    while (i < inputNum) {
        if (pressing(VK_F9)) { // 按F9中途结束
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
        imitateChange();
        Sleep(SLEEP_DURATION);
    }
    return 0;
}