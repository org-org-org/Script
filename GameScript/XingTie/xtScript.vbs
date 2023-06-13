SLEEP_DURATION = 1000 * 20
dir = "D:\0_vscode_cpp\Script\GameScript\XingTie\"
do
    set obj = getobject("winmgmts:\\.\root\cimv2")
    set xt = obj.execquery("select ProcessID from win32_process where name='StarRail.exe'")
    set helper = obj.execquery("select ProcessID from win32_process where name='xtHelper.exe'")
    if xt.Count > 0 and helper.Count = 0 then 
        CreateObject("wscript.shell").run dir + "xtHelper.exe" + " " + dir, 0
    elseif xt.Count = 0 then 
        for each i in helper
            i.terminate()
        next
    end if
    wscript.sleep SLEEP_DURATION
loop