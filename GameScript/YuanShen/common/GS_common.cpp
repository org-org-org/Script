void syncInit() {
    loadAllKeys();
    readSyncInputFile();
    while (!pressing(beginKey)) { // 按F8开始执行
        Sleep(SLEEP_DURATION);
    }
}
void initSyncLoopImplement() {
    loadAllKeys();
    cout << "whether start a new round manually or sleep?\n";
    cout << "input 0 or N, 0 means manually and N means sleep N second\n";
    cin >> ROUND_DURATION;
    cout << "input the loop times\n";
    cin >> ROUND;
    readSyncInputFile();
}