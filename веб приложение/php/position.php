<?php 
	$str=shell_exec('cat /tmp/Pos');
	$positionData=explode(" ",$str);
    echo json_encode($positionData);	
?>
