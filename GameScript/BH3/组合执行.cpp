#include "../../common/common_implement.h"
#include <queue>
queue<string>fileNames;
void init() {
    loadAllKeys();
    cout << "whether start next manually or sleep?\n";
    cout << "input 0 or N, 0 means manually and N means sleep N second\n";
    cin >> ROUND_DURATION;
    while (1) {
        cout << "input a filename to read, or input -1 to stop\n";
        cin >> fileName;
        if (fileName == "-1") {
            break;
        }
        while ((findFile(fileName)) == NULL) {
            cout << "wrong filename, please input again\n";
            cin >> fileName;
        }
        fileNames.push(fileName);
    }
    cout << "then press F8 to implement and press F9 to stop\n";
}
void roundInit() {
    inputNum = 0;
    fileName = fileNames.front();
    fileNames.pop();
    FILE* fp = findFile(fileName);
    while (~fscanf(fp, "%d%d%d", &inputTime[inputNum], &inputKey[inputNum], &inputType[inputNum])) {
        inputNum++;
    }
    fclose(fp);
}
int main() {
    init();
    while (!fileNames.empty()) {
        roundInit();
        if (waitToStart(start) == 0) {
            return 0;
        }
        start = Now();
        int i = 0;
        while (i < inputNum) {
            if (pressing(endKey)) { // 按F9直接结束本次
                clearPressingState();
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
            Sleep(SLEEP_DURATION);
        }
    }
    return 0;
}