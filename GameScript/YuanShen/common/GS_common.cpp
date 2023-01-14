void readSyncInputFile() {
    cout << "input a filename to read\n";
    cin >> fileName;
    FILE* fp = searchFile(fileName);
    cout << "then press F8 to implement and press F9 to stop\n";
    fscanf(fp, "%d", &inputNum);
    for (int i = 0; i < inputNum; i++) {
        fscanf(fp, "%d%d%d", &inputTime[i], &inputKey[i], &inputType[i]);
    }
    fscanf(fp, "%d", &syncCnt);
    for (int i = 0; i < syncCnt; i++) {
        fscanf(fp, "%d", &syncImitate[i]);
    }
    fclose(fp);
}
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