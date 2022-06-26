#include "common_implement.h"
void init() {
    loadAllKeys();
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
int main() {
    init();
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