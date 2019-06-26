


if((Get-ScheduledTask | Where TaskName -eq taskschedulerdeneme ).State -eq "Ready"){
    powershell C:\Users\fuatf\Desktop\Untitled2.ps1
}else{
    schtasks.exe /create /tn pwrshldeneme /sc daily /tr "powershell -WindowStyle Hidden .\questek.ps1" /st 12:50
}
