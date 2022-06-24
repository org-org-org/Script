#include "myhead.h"
int ROUND_DURATION = 0;
int ROUND = 1;
void init() {
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp;
    while ((fp = findFile(fileName)) == NULL) {
        cout << "wrong filename, please input again\n";
        cin >> fileName;
    }
    cout << "whether start a new round manually or sleep?\n";
    cout << "input 0 or N, 0 means manually and N means sleep N second\n";
    cin >> ROUND_DURATION;
    cout << "input the loop times\n";
    cin >> ROUND;
    cout << "then press F8 to implement and press F9 to stop\n";
    while (~fscanf(fp, "%d%d%d", &inputTime[inputNum], &inputKey[inputNum], &inputType[inputNum])) {
        inputNum++;
    }
    fclose(fp);
}
int waitToStart(int T) {
    if (ROUND_DURATION && T) {
        Sleep(ROUND_DURATION * 1000);
    } else {
        while (!pressing(VK_F8)) { // 按F8开始执行
            if (pressing(VK_F9)) { // 按F9中途结束
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    return 1;
}
int main() {
    init();
    for (int T = 0; T < ROUND; T++) {
        if (waitToStart(T) == 0) {
            return 0;
        }
        start = Now();
        int i = 0;
        while (i < inputNum) {
            if (pressing(VK_F9)) { // 按F9中途结束
                return 0;
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
    }
    return 0;
}