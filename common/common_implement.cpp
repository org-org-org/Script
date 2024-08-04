#include "common.cpp"
BYTE replaceMap[256] = {0};
int ROUND_DURATION = 0;
int ROUND = 1;
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
                break;
            }
        }
    }
    closedir(dir);
    return fp;
}
void getAllSimilarFile(vector<string>& files, string searchName, string prefix = LOAD_DIR) {
    DIR* dir = opendir(prefix.c_str());
    struct dirent* entry;
    while (entry = readdir(dir)) {
        string curName = entry->d_name;
        if (curName.find(searchName) != curName.npos) {
            files.push_back(curName);
        } else if (curName.find('.') == curName.npos) { // 是文件夹
            getAllSimilarFile(files, searchName, prefix + curName + '/');
        }
    }
    closedir(dir);
}
FILE* searchFile() {
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp;
    if ((fp = findFile(fileName)) != NULL) {
        return fp;
    }
    vector<string>files;
    getAllSimilarFile(files, fileName);
    while (files.empty()) {
        cout << "wrong filename, please input again\n";
        cin >> fileName;
        getAllSimilarFile(files, fileName);
    }
    cout << "input the number to choose file:\n";
    for (int i = 0; i < files.size(); i++) {
        cout << i + 1 << ": " << files[i] << endl;
    }
    int id;
    cin >> id;
    while (id <= 0 || id > files.size()) {
        cout << "wrong id, please input again\n";
        cin >> id;
    }
    return findFile(files[id - 1]);
}
void readInputFile() {
    FILE* fp = searchFile();
    cout << "then press F8 to implement and press F9 to stop\n";
    inputNum = 0;
    while (~fscanf(fp, "%d%d%d", &inputTime[inputNum], &inputKey[inputNum], &inputType[inputNum])) {
        if (inputKey[inputNum] > 0 && replaceMap[inputKey[inputNum]]) {
            inputKey[inputNum] = replaceMap[inputKey[inputNum]];
        }
        inputNum++;
    }
    fclose(fp);
}
void init() {
    readInputFile();
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    start = Now();
}
void initLoopImplement() {
    loadAllKeys();
    cout << "whether start a new round manually or sleep?\n";
    cout << "input 0 or N, 0 means manually and N means sleep N second\n";
    cin >> ROUND_DURATION;
    cout << "input the loop times\n";
    cin >> ROUND;
    readInputFile();
}
void pressKey(int key, int afterSleepDuration = 0) {
    pressDown(key);
    Sleep(SLEEP_DURATION);
    pressUp(key);
    Sleep(afterSleepDuration);
}
void checkPressedKeyUntilNextPressed(int vKey, void (*oper)(), int interval = 9) {
    if (pressing(vKey)) {
        if (pre[vKey] == 0) { // 之前没按着现在按着，按下
            pre[vKey] = 1;
        }
    } else {
        if (pre[vKey] == 1) { // 之前按着现在没按着，松开
            pre[vKey] = 0;
            hit[vKey] = !hit[vKey];
        }
    }
    if (hit[vKey]) {
        hit[vKey]++;
        if (hit[vKey] > interval) {
            oper();
            hit[vKey] = 1;
        }
    }
}
void checkPressingKey(int vKey, void (*oper)(), int interval = 9) {
    if (pressing(vKey)) {
        hit[vKey]++;
        if (hit[vKey] > interval) {
            oper();
            hit[vKey] = 1;
        }
    } else {
        hit[vKey] = 0;
    }
}
void checkPressingKeyOnce(int vKey, void (*oper)(), int interval = 9) {
    if (pressing(vKey)) {
        if (hit[vKey] == 0) {
            oper();
            hit[vKey] = 1;
        }
    } else {
        hit[vKey] = 0;
    }
}