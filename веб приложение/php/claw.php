<?php
	switch ( $_POST['action'] )
	{
		case 'ClawClose':
			  exec('sudo /var/www/html/bash/claw_close_open close');
			break;
		case 'ClawOpen':
			  exec('sudo /var/www/html/bash/claw_close_open open');
			break;		
	}	
	exec ('sudo /var/www/html/bash/claw_rotate '.$_POST['angleRotate']);
	exec ('sudo /var/www/html/bash/claw_up_down '.$_POST['angleUpDown']);	
?>	