void whetherReplace() {
    int use = 0;
    cout << "whether to use replace key?\n";
    cout << "input 0 or 1, 0 means no and 1 means yes\n";
    cin >> use;
    if (use) {
        replaceMap['J'] = VK_NUMPAD1;
        replaceMap['I'] = VK_NUMPAD5;
        replaceMap['O'] = VK_NUMPAD6;
        replaceMap['U'] = VK_NUMPAD4;
        replaceMap['M'] = VK_NUMPAD0;
        replaceMap['K'] = VK_NUMPAD2;
    }
}