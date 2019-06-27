
$today=(Get-Date).Hour.ToString()+"_"+(Get-Date).Day.ToString()+"_"+(Get-Date).Month.ToString()+"_"+(Get-Date).Year.ToString()+".txt"
$ystrdy=Get-Date
$ystrdy=$ystrdy.AddDays(-1)

$discLetters=(Get-Partition|Where-Object -FilterScript {$_.Type -Eq "Basic"}).DriveLetter

for ($i = 0; $i -le ($discLetters.length - 1); $i += 1) {
    $discLetters[$i]=$discLetters[$i]+":\"
    Get-ChildItem $discLetters[$i] -ErrorAction SilentlyContinue -Recurse|ForEach-Object{#-force
        if($_.LastWriteTime -ge $ystrdy){
            (echo $_.LastWriteTime $_.FullName )>>C:\Users\fuatf\Desktop\$today
        }
    }
}