<?php
	switch ( $_POST['action'] )
	{
		case 'CamUp':
			  exec('echo "camUp">/dev/ttyS0');
			break;

		case 'CamRight':
			  exec('echo "camRight">/dev/ttyS0');
			break;

		case 'CamDown':
			  exec('echo "camDown">/dev/ttyS0');
			break;

		case 'CamLeft':
			  exec('echo "camLeft">/dev/ttyS0');
			break;
        
		case 'camstd':
			  exec('echo "camCenter">/dev/ttyS0');
			break;
		
		case 'go':
			  exec('echo "forward">/dev/ttyS0');
			break;	

		case 'back':
			  exec('echo "backward">/dev/ttyS0');
			break;

		case 'left':
			  exec('echo "left">/dev/ttyS0');
			break;

		case 'right':
			  exec('echo "right">/dev/ttyS0');
			break;
		case 'powerOff':
			  exec('sudo shutdown -h now');
			break;
		case 'restartService':
			  exec('sudo /etc/init.d/ffserd restart');
			break;		
		default: exec('echo "'.$_POST['coor'].'">/dev/ttyS0');
	}		
?>	