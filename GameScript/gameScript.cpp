#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
using namespace std;
map<string, string>m;
vector<string> splitN(string str, char sep, int n = -1) {
    vector<string>res;
    int pre = 0, i = 0;
    for (; i < str.size(); i++) {
        if (str[i] == sep) {
            res.push_back(str.substr(pre, i - pre));
            pre = i + 1;
            if (res.size() == n) {
                return res;
            }
        }
    }
    res.push_back(str.substr(pre, i - pre));
    return res;
}
string trimColon(string str) {
    return str.substr(1, str.size() - 2);
}
void getCurProcess() {
    m.clear();
    char buffer[256];
    FILE* fp = popen("tasklist /FI \"STATUS eq running\" /FO csv /NH", "r");
    if (fp == NULL) {
        cout << "Failed to run tasklist\n";
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        vector<string>s = splitN(buffer, ',', 2);
        string name = trimColon(s[0]), pid = trimColon(s[1]);
        m[name] = pid;
    }
    pclose(fp);
}
void startProcess(string file, string dir) {
    cout << ShellExecute(NULL, LPCTSTR("open"), LPCTSTR(file.c_str()), NULL, LPCTSTR(dir.c_str()), 0);
}
void killProcess(string pName) {
    string pid = m[pName];
    system(("taskkill /F /PID " + pid).c_str());
}
int exist(string pName) {
    return m[pName] != "";
}
void openOrClose(string gameName, string helperName, string helperDir) {
    if (exist(gameName) && !exist(helperName)) { // 启动
        startProcess(helperName, helperDir);
    } else if (!exist(gameName) && exist(helperName)) { // 关
        killProcess(helperName);
    }
}
int main() {
    const string yuanShen = "YuanShen.exe", op = "opHelper.exe";
    const string starRail = "StarRail.exe", xt = "xtHelper.exe";
    const string zenlessZoneZero = "ZenlessZoneZero.exe", zzz = "zzzHelper.exe";
    while (1) {
        getCurProcess();
        openOrClose(yuanShen, op, "./YuanShen/");
        openOrClose(starRail, xt, "./XingTie/");
        openOrClose(zenlessZoneZero, zzz, "./ZZZ/");
        Sleep(15000);
    }
    return 0;
}
