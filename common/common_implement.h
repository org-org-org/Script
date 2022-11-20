#include "common.h"
int ROUND_DURATION = 0;
int ROUND = 1;
void press(int key) {
    pressDown(key);
    Sleep(8 * SLEEP_DURATION);
    pressUp(key);
    Sleep(8 * SLEEP_DURATION);
}
void mouseMove(int i) {
    SetCursorPos(-inputKey[i], -inputType[i]);
}
int waitToStart(int T = 1) {
    if (ROUND_DURATION && T) {
        Sleep(ROUND_DURATION * 1000);
    } else {
        while (!pressing(beginKey)) { // 按F8开始执行
            if (pressing(endKey)) { // 按F9中途结束
                return 0;
            }
            Sleep(SLEEP_DURATION);
        }
    }
    return 1;
}
FILE* findFile(string fileName, string prefix = LOAD_DIR) {
    if (fileName.find(".txt") == fileName.npos) {
        fileName += ".txt";
    }
    FILE* fp = fopen((prefix + fileName).c_str(), "r");
    if (fp != NULL) {
        return fp;
    }
    DIR* dir = opendir(prefix.c_str());
    struct dirent* entry;
    while (entry = readdir(dir)) {
        string curName = entry->d_name;
        if (curName.find('.') == curName.npos) { // 是文件夹
            fp = findFile(fileName, prefix + curName + '/');
            if (fp != NULL) {
                closedir(dir);
                return fp;
            }
        }
    }
    closedir(dir);
    return NULL;
}
void initImplement() {
    loadAllKeys();
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
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    start = Now();
}
void initLoopImplement() {
    cout << "whether start a new round manually or sleep?\n";
    cout << "input 0 or N, 0 means manually and N means sleep N second\n";
    cin >> ROUND_DURATION;
    cout << "input the loop times\n";
    cin >> ROUND;
    loadAllKeys();
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
}
void pressKey(BYTE vKey) {
    static char cnt[256] = {0};
    if (cnt[vKey] == 8) {
        pressDown(vKey);
    } else if (cnt[vKey] == 16) {
        pressUp(vKey);
        cnt[vKey] = 0;
    }
    cnt[vKey]++;
}