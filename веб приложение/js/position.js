$(document).ready(function(){	
	setInterval(function(){		//запрос положения в пространстве
		$.getJSON("/php/position.php",
    function(data){
        positionRotate('#tangageBotPic',data[0]);
		positionRotate('#careneBotPic',(data[1]*(-1)));
        
				  });
					
	},300);
})

function positionRotate(object,x) //поворот миниатюр крен и тангаж
				{					
					$(object).css(
						{
							'-moz-transform-origin': '70px 50px',                
							'transform-origin': '70px 50px%',                   
							'-ms-transform-origin': '70px 50px',                                
							'-webkit-transform-origin': '70px 50px',
						});  

					
					$(object).css(
						{
							'-moz-transform':'rotate('+x+'deg)',
							'-webkit-transform':'rotate('+x+'deg)',
							'-o-transform':'rotate('+x+'deg)',
							'-ms-transform':'rotate('+x+'deg)',
							'transform': 'rotate('+x+'deg)'
						});
				}
