#include "../../common/common_implement.h"
vector<string>files;
void getAllSimilarFile(string searchName, string prefix = LOAD_DIR) {
    DIR* dir = opendir(prefix.c_str());
    struct dirent* entry;
    while (entry = readdir(dir)) {
        string curName = entry->d_name;
        if (curName.find(searchName) != curName.npos) {
            files.push_back(curName);
        } else if (curName.find('.') == curName.npos) { // 是文件夹
            getAllSimilarFile(searchName, prefix + curName + '/');
        }
    }
    closedir(dir);
}
FILE* searchFile(string fileName) {
    FILE* fp;
    if ((fp = findFile(fileName)) != NULL) {
        return fp;
    }
    getAllSimilarFile(fileName);
    while (files.empty()) {
        cout << "wrong filename, please input again\n";
        cin >> fileName;
        getAllSimilarFile(fileName);
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
void init() {
    loadAllKeys();
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp = searchFile(fileName);
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
int main() {
    init();
    int i = 0;
    while (i < inputNum) {
        if (pressing(endKey)) { // 按F9中途结束
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
    return 0;
}