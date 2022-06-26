#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <dirent.h>
using namespace std;
const int N = 1 << 18;
const int MOUSE_SPEED = 32;
const int SLEEP_DURATION = 10;
const string LOAD_DIR = "./input/";
int inputTime[N] = {0}, inputKey[N] = {0}, inputType[N] = {0};
int inputNum = 0;
time_t start = 0, curTime = 0;
string fileName;
BYTE beginKey = VK_F8, endKey = VK_F9;
vector<BYTE>vKeys;
bool pre[256] = {0};