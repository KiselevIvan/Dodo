<?php 

$cpufreq = shell_exec('cpufreq-info -fm');
$sysLoad = shell_exec('cat /proc/loadavg ');
$time = shell_exec('awk \'{printf("%02d:%02d:%02d",($1/60/60%24),($1/60%60),($1%60))}\' /proc/uptime');

$temp = shell_exec('cat /sys/devices/virtual/thermal/thermal_zone0/temp');
printf("<pre> %.7s | %.15s |   %.2s °C | %s </pre>", $cpufreq, $sysLoad,$temp,$time )
 

?>
