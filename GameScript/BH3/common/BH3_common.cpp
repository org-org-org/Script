void whetherReplace() {
    int use = 0;
    FILE* fp = fopen("common/config.txt", "r");
    char config[128];
    fgets(config, 128, fp);
    sscanf(config, "%d", &use);
    if (use) {
        cout << "use replace key\n";
        replaceMap['J'] = VK_NUMPAD1;
        replaceMap['I'] = VK_NUMPAD5;
        replaceMap['O'] = VK_NUMPAD6;
        replaceMap['U'] = VK_NUMPAD4;
        replaceMap['M'] = VK_NUMPAD0;
        replaceMap['K'] = VK_NUMPAD2;
    }
}