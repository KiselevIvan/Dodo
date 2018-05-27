<!DOCTYPE HTML>
<html>
	<head>
		<title>
			ControlPanel
		</title>
		<meta charset="UTF-8" />
	
		<link rel="stylesheet" type="text/css" href="style.css?t=<?php echo(microtime(true)); ?>" >
		<script type="text/javascript" src="js/jquery-3.2.1.min.js"></script>
		<script type="text/javascript" src="js/button.js?t=<?php echo(microtime(true)); ?>"></script>			
		<script type="text/javascript" src="js/info.js?t=<?php echo(microtime(true)); ?>"></script>			
		<script type="text/javascript" src="js/position.js?t=<?php echo(microtime(true)); ?>"></script>			
		<script type="text/javascript" src="js/claw.js?t=<?php echo(microtime(true)); ?>"></script>			
		
	</head>
	<body >
		<div class="main">
			<div id="video">
			 <object type="application/x-shockwave-flash" data="player_flv_maxi.swf" width="640" height="480">
				<param name="movie" value="player_flv_maxi.swf" />
				<param name="FlashVars" value="flv=http://<?php echo exec('hostname -I')?>:8090/webcam.flv&buffer=0.4&autoplay=1&showplayer=never" />
			</object>
			
			<!-- ?php echo exec('wget -O - -q icanhazip.com')?> для внешнего адреса-->
		 
			</div>
			
			<div id="rightBlock">
				
				<div id="systemInfo">
					<div id="info">
						<b><pre>   CPU   |   System Load   |   TEMP  |  UPTIME</pre></b>
						<div id="value">
						</div>
					</div>
				</div>
				
				<div id="position">
					<div id="tangage" class="positionCoor" title="Тангаж">						
						
						<img alt="coor" 
							 src="img/coor.png"
							 class="positionCoorPic"
							 id="tangageCoorPic"
							 
						>
						<img alt="Tangage" 
							 src="img/img6.png"
							 class="positionBotPic"
							 id="tangageBotPic"
						>
						
					</div>
					<div id="carene" class="positionCoor" title="Крен">
						<img alt="coor" 
							 src="img/coor.png"
							 class="positionCoorPic"
							 id="careneCoorPic"
						>
						<img alt="Carene" 
							 src="img/img5.png"
							 class="positionBotPic"
							 id="careneBotPic"
						>
						
					</div>
				</div>
				
			
			
				<div id="ClawControl" class="Control">
						
						<p>
							Управление клешней
						</p>
						
						<img 
							alt="ClawOpen" 
							src="img/ClawO.png" 
							class="clawThumbs" 
							style="visibility:hidden" 
							id="clawO"
							title="Захват открыт"
						>
						
						<img 
							alt="ClawClose" 
							src="img/ClawC.png" 
							class="clawThumbs" 
							id="clawC"
							title="Захват закрыт"
						>
									
						<img 
							alt="ClawClose"					
							src="img/ClawClose.png"
							class="ClawButton button"
							style="visibility:hidden"
							id="ClawClose"
							title="Закрыть захват"
						>
						
						<img 
							alt="ClawOpen"					
							src="img/ClawOpen.png"
							class="ClawButton button"
							id="ClawOpen"
							title="Открыть захват"
						>
						<input 
							type="range" 
							min="1" 
							max="180" 
							step="1" 
							id="ClawRotate"
							title="Вращение захвата"
						>
						
				</div>
				
				<div id="MainButton" class="Control">	
					<img 
						alt="restartService"					
						src="img/restart.png"
						class="button"						
						id="restartService"
						title="Перезапустить видеосервер"
					>
					<img 
						alt="power"					
						src="img/power.png"
						class="button"						
						id="power"
						title="Выключить робота"
					>
				</div>
				
				
			</div>
			
			<div id="bottomBlock">				
				
					<div class="ControlButton Control" >
													
						
						<p>
							Управление двигателями
						</p>
						
						<img 
							alt="up"					
							src="img/up.png"
							class="button moveControl"
							id="b1"
							title="Движение вперед"
						>
						
						<img 
							alt="right"					
							src="img/right.png"
							class="button moveControl"
							id="b2"
							title="Вращение вправо"
						>
					
						<img 
							alt="down"					
							src="img/down.png"
							class="button moveControl"
							id="b3"
							title="Движение назад"
						>
						
						<img 
							alt="left"					
							src="img/left.png"
							class="button moveControl"
							id="b4"
							title="Вращение влево"
						>				
						
					</div>

					<div id="Manipulator">
							
						<input 
							type="range" 
							min="1" 
							max="180" 
							step="1" 
							id="ClawUpDown"
							title="Поворот плеча"
						>
						<img src="img/img2.png" id="roboBodyRight">
						<img src="img/img3.png" id="roboArm">
					</div>
				
					<div class="ControlButton Control">	
						
						<p>
							Управление камерой
						</p>
						
						<img 
							alt="up"					
							src="img/up.png"
							class="button stepCamMove"
							id="b5"
							title="Поднять камеру"
						>
						
						<img 
							alt="right"					
							src="img/right.png"
							class="button stepCamMove"
							id="b6"
							title="Повернуть камеру вправо"
						>
					
						<img 
							alt="down"					
							src="img/down.png"
							class="button stepCamMove"
							id="b7"
							title="Опустить камеру"
						>
						
						<img 
							alt="left"					
							src="img/left.png"
							class="button stepCamMove"
							id="b8"
							title="Повернуть камеру влево"
						>
						
						<img 
							alt="camstd"					
							src="img/center.png"
							class="button"
							id="camCentr"
							title="Выровнить камеру по центру"
						>
					</div>
					
					<div id="thumbianCam">
							<img src="img/img1.png" id="roboBodyTop">
							<img src="img/img4.png" id="roboCamTop">
					</div>
					
					
			</div>
						
		</div>
		
 </body>
</html>
