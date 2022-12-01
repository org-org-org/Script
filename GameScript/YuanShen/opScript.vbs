SLEEP_DURATION = 1000 * 20
dir = "D:\0_vscode_cpp\Script\GameScript\YuanShen\"
do
    set obj = getobject("winmgmts:\\.\root\cimv2")
    set op = obj.execquery("select ProcessID from win32_process where name='YuanShen.exe'")
    set helper = obj.execquery("select ProcessID from win32_process where name='opHelper.exe'")
    if op.Count > 0 and helper.Count = 0 then 
        CreateObject("wscript.shell").run dir + "opHelper.exe" + " " + dir, 0
    elseif op.Count = 0 then 
        for each i in helper
            i.terminate()
        next
    end if
    wscript.sleep SLEEP_DURATION
loop