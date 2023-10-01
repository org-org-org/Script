#include "../../common/common_implement.h"
char vis[32][32] = {0};
char di[] = {1, 0, -1, 0};
char dj[] = {0, 1, 0, -1};
char pressDir[] = {'S', 'D', 'W', 'A'};
int n, m, dir = 0, cnt = 0;
bool check(int i, int j) {
    return i > 0 && i <= n && j > 0 && j <= m && !vis[i][j];
}
void dfs(int i, int j) {
    if (GetAsyncKeyState(endKey)) {
        return;
    }
    pressKey('F', 1400);
    cnt++;
    if (cnt == n * m) {
        return;
    }
    pressKey(pressDir[dir], 800);
    i += di[dir];
    j += dj[dir];
    if (!check(i + di[dir], j + dj[dir])) {
        dir = (dir + 1) & 3;
        pressKey(pressDir[dir], 800);
    }
    vis[i][j] = 1;
    dfs(i, j);
}
int main() {
    loadAllKeys();
    cout << "cin >> n >> m\n";
    cin >> n >> m;
    cout << "then press F8 to implement and press F9 to stop\n";
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
    dfs(0, 1);
    return 0;
}
