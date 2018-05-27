$(document).ready(function(){
ArmRotate(90);
ClawRotate(90);
$("#ClawOpen").click(function(){
	clawOpen();
	$.ajax({
				url : 'php/claw.php' ,
				method : 'POST' ,
				data : {
				action : 'ClawOpen'
					   }				
				});
});

$("#ClawClose").click(function(){
	clawClose();
	$.ajax({
				url : 'php/claw.php' ,
				method : 'POST' ,
				data : {
				action : 'ClawClose'
					   }				
					});
});

$("#ClawRotate").change(function(){	
				ClawRotate($(this).val());
					$.ajax({
				url : 'php/claw.php' ,
				method : 'POST' ,
				data : {
				angleRotate : $("#ClawRotate").val()
					   }				
							});				
				  });

$("#ClawUpDown").change(function(){			
					ArmRotate($(this).val());
					$.ajax({
				url : 'php/claw.php' ,
				method : 'POST' ,
				data : {
				angleUpDown : $("#ClawUpDown").val()
					   }				
				});				
				  });
	
	
})				

function ClawRotate(d)
				{
					$("#clawO").css(
						{
							'-moz-transform-origin': '50% 50%',                
							'transform-origin': '50% 50%',                   
							'-ms-transform-origin': '50% 50%',                                
							'-webkit-transform-origin': '50% 50%',
						});  
					
					$("#clawC").css(
						{
							'-moz-transform-origin': '50% 50%',                
							'transform-origin': '50% 50%',                   
							'-ms-transform-origin': '50% 50%',                                
							'-webkit-transform-origin': '50% 50%',
						}); 
					
					$("#clawO").css(
						{
							'-moz-transform':'rotate('+d+'deg)',
							'-webkit-transform':'rotate('+d+'deg)',
							'-o-transform':'rotate('+d+'deg)',
							'-ms-transform':'rotate('+d+'deg)',
							'transform': 'rotate('+d+'deg)'
						});

					$("#clawC").css(
						{
							'-moz-transform':'rotate('+d+'deg)',
							'-webkit-transform':'rotate('+d+'deg)',
							'-o-transform':'rotate('+d+'deg)',
							'-ms-transform':'rotate('+d+'deg)',
							'transform': 'rotate('+d+'deg)'
						}); 					
				}	
	
function ArmRotate(val)
				{ 
				 d=(parseInt(val-135)*(-1)-100);
					$("#roboArm").css(
						{
							'-moz-transform-origin': '5% 95%',                
							'transform-origin': '5% 95%',                   
							'-ms-transform-origin': '5% 95%',                                
							'-webkit-transform-origin': '5% 95%',
						});  

					$("#roboArm").css(
						{
							'-moz-transform':'rotate('+d+'deg)',
							'-webkit-transform':'rotate('+d+'deg)',
							'-o-transform':'rotate('+d+'deg)',
							'-ms-transform':'rotate('+d+'deg)',
							'transform': 'rotate('+d+'deg)'
						});  
				}
	
function clawOpen()
				{
					$("#ClawClose").css('visibility' , 'visible');						
					$("#clawO").css('visibility' , 'visible');
					$("#ClawOpen").css('visibility' , 'hidden');
					$("#clawC").css('visibility' , 'hidden');
				}
				
function clawClose()
				{
					$("#ClawClose").css('visibility' , 'hidden');	
					$("#clawO").css('visibility' , 'hidden');
					$("#ClawOpen").css('visibility' , 'visible');
					$("#clawC").css('visibility' , 'visible');
				}	
				
