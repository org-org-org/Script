#include "common_var.h"
void press(BYTE vKey) {
    keybd_event(vKey, 0, 0, 0);
    keybd_event(vKey, 0, 2, 0);
}
bool pressing(int vKey) {
    return GetAsyncKeyState(vKey) >> 15;
}
time_t Now() { // 获取当前时间戳，毫秒级
    time_t second;
    time(&second);
    SYSTEMTIME ms;
    GetSystemTime(&ms);
    return second * 1000 + ms.wMilliseconds;
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
void loadAllKeys() {
    vKeys = vector<BYTE>{1, 2, 4, 8, 9, 13, 16, 17, 18, 20, 27, 44, 46, 192};
    for (int i = 32; i <= 40; i++) {
        vKeys.push_back(i);
    }
    for (int i = 48; i <= 92; i++) { // 0~9 + A~Z
        vKeys.push_back(i);
    }
    for (int i = 112; i <= 123; i++) { // F1~F12
        vKeys.push_back(i);
    }
    // for (int i = 96; i <= 111; i++) { // 小键盘
    //     vKeys.push_back(i);
    // }
}
void clearPressingState() {
    for (auto v : vKeys) {
        keybd_event(v, 0, 2, 0);
    }
}