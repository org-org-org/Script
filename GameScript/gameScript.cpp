#include <iostream>
#include <vector>
#include <map>
#include <Windows.h>
using namespace std;

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

map<string, string> getCurProcess() {
    map<string, string>m;
    char buffer[256];
    FILE* fp = popen("tasklist /FI \"STATUS eq running\" /FO csv /NH", "r");
    if (fp == NULL) {
        cout << "Failed to run tasklist\n";
        return m;
    }
    while (fgets(buffer, sizeof(buffer), fp)) {
        vector<string>s = splitN(buffer, ',', 3);
        string name = trimColon(s[0]), pid = trimColon(s[1]);
        m[name] = pid;
    }
    pclose(fp);
    return m;
}

void startProcess(string file, string dir) {
    cout << ShellExecute(NULL, LPCTSTR("open"), LPCTSTR(file.c_str()), LPCTSTR(dir.c_str()), LPCTSTR(dir.c_str()), 0);
}

void killProcess(string pid) {
    system(("taskkill /F /PID " + pid).c_str());
}

int main() {
    while (1) {
        map<string, string>m = getCurProcess();
        string yuanShen = m["YuanShen.exe"], op = m["opHelper.exe"];
        string starRail = m["StarRail.exe"], xt = m["xtHelper.exe"];
        if (yuanShen != "" && op == "") { // 启动op
            startProcess("opHelper.exe", "./YuanShen/");
        } else if (op != "" && yuanShen == "") { // 关op
            killProcess(op);
        } else if (starRail != "" && xt == "") { // 开xt
            startProcess("xtHelper.exe", "./XingTie/");
        } else if (xt != "" && starRail == "") { // 关xt
            killProcess(xt);
        }
        Sleep(15000);
    }
    return 0;
}
