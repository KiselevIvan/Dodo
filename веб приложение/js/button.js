$(document).ready(function(){
var roboCamTopRotate=0;

	$( "img.button" ).mousedown(function() {
		$( this ).css('background-image','radial-gradient(#8a8a8a , #f3f3f3 70%)');
											});

	$( "img.button" ).mouseup(function() {		 
		$( this ).css('background-image','radial-gradient(#f3f3f3 25%,#b4b4b4 80%, #707070)');
	
									 });
									 
	$( "#power" ).mousedown(function() {
		$( this ).css('background-image','radial-gradient(#b60000 , #ff0000 70%)');
		
											});

	$( "#power" ).mouseup(function() {		 
		$( this ).css('background-image','radial-gradient(#e65353 25%,#cd0a00 80%, #b80000)');	
									 });
	
	var bid='';//button ID
    var flagKeyFirstPress=true;//чтобы при нажатии клавиши запустить только один таймер
	$(this).keydown(function (){
		if(flagKeyFirstPress)
		{
		 
		 switch (event.which){
								case 87: {
											bid='1';
											break;
									     }
										 
								case 68: {
											bid='2';
											break;
									     }
										 
								case 83: {
											bid='3';
											break;
									     }

								case 65: {
											bid='4';
											break;
									     }
								
								case 73: {
											bid='5';
											break;
									     }
										 
								case 76: {
										  bid='6';
										  break;
									     }
										 
								case 75: {
									      bid='7';
										  break;
									     }					
										
								case 74: {
										  bid='8';
										  break;
									     }

								case 84: {
											$("#camCentr").trigger('click');
											break;
									     }										
							 }
							 
							 if (bid!='')
							 {
								$( "#b"+bid ).trigger('mousedown');
								
							 }
									flagKeyFirstPress=false;
		}				  
										  	     
		
										})
										
	$(this).keyup(function (){
	
	$( "#b"+bid ).trigger('mouseup');
	bid='';
	flagKeyFirstPress=true;
							})							
	var myInterval;
	$('.moveControl,.stepCamMove').mousedown (function() {
		 
		var actButton;//требуемая команда
		switch ($( this ).attr('id')) {	 
	  case "b1":$actButton = 'go';
				break;
	  case "b2":$actButton = 'right';
				break;
	  case "b3":$actButton = 'back';
				break;
	  case "b4":$actButton = 'left';
				break;		
				
			
	  case "b5":$actButton = 'CamUp';
				break;
	  case "b6":$actButton = 'CamRight';
				break;
	  case "b7":$actButton = 'CamDown';
				break;
	  case "b8":$actButton = 'CamLeft';
				break;
	  default:$actButton = null;
				break;
	  }
	
	

	
  myInterval = setInterval(function() {	  
	$.ajax({
				url : 'php/actions.php' ,
				method : 'POST' ,
				data : {
				action : $actButton				
					   },
				success : function(resp){
				//...
										}
				});
	if ($actButton=='CamLeft')
	{		
	  if ((roboCamTopRotate>-90))
			{
				roboCamTopRotate-=4;
				CamMove(roboCamTopRotate);//поворачиваем миниатюру камеры
			}					  
	}
	else 
		if ($actButton=='CamRight')
	{		
	  if (roboCamTopRotate<=90)
			{
				roboCamTopRotate+=4;
				CamMove(roboCamTopRotate);//поворачиваем миниатюру камеры
			}					  
	}
	
	  
  }, 200);
 
  
 });
	
	$('.moveControl,.stepCamMove').mouseup (function(){
		 clearInterval(myInterval); }); 
	
	var flagFirstTimer=true;//чтобы запустить только один таймер
	$('#video').mousemove(function(e){
	if (e.shiftKey )
		{
				if (flagFirstTimer)
				setTimeout(function() {
					
				var posBlock=$('#video').offset();
				var coorX=Math.round((e.pageX-posBlock.left)/640*100);//переводим в проценты
				var coorY=Math.round((e.pageY-posBlock.top)/480*100);		 				
				
				CamMove(coorX*180/100-90);//поворачиваем миниатюру
				$.ajax({
					url : 'php/actions.php' ,
					method : 'POST' ,
					data : {
					coor : 'coor'+coorX+':'+coorY
						},
					success : function(resp){
					//...
					
											}
					});
					flagFirstTimer=true;
					},50);
					flagFirstTimer=false;
		}

		});

	$("#camCentr").click(function() {
		roboCamTopRotate=0;
		CamMove(roboCamTopRotate);
		$.ajax({
				url : 'php/actions.php' ,
				method : 'POST' ,
				data : {
				action : 'camstd'				
					   },
				success : function(resp){
				//...
										}
				});
									});
		
	$("#power").click(	
		function(){
			if (confirm("Вы точно хотите выключить робота?"))
					$.ajax({
				url : 'php/actions.php' ,
				method : 'POST' ,
				data : {
				action : 'powerOff'
					   }				
				});
				  }
					);
						
	$("#restartService").click(		
			function(){
				if (confirm("Вы точно хотите перезапустить видеосервер?"))
		{
					$.ajax({
				url : 'php/actions.php' ,
				method : 'POST' ,
				data : {
				action : 'restartService'
					   }				
				});
				window.location.reload();				
		}	
					  }				  
					);
});
	
function CamMove(x)	
				{					
					$("#roboCamTop").css(
						{
							'-moz-transform-origin': '45% 80%',                
							'transform-origin': '45% 80%',                   
							'-ms-transform-origin': '45% 80%',                                
							'-webkit-transform-origin': '45% 80%',
						});  

					
					$("#roboCamTop").css(
						{
							'-moz-transform':'rotate('+x+'deg)',
							'-webkit-transform':'rotate('+x+'deg)',
							'-o-transform':'rotate('+x+'deg)',
							'-ms-transform':'rotate('+x+'deg)',
							'transform': 'rotate('+x+'deg)'
						});
				}
