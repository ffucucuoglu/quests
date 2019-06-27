if(-not ((Get-ScheduledTask | Where TaskName -eq denemetask ).State -eq "Ready")){
    schtasks.exe /create /tn denemetask /sc daily /tr "powershell  -WindowStyle Hidden C:\Users\fuatf\Desktop\son\questAdditional.ps1" /st 03:33
    exit
}