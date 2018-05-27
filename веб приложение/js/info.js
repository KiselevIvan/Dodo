$(document).ready(function(){
	var heigh=0;
	
	var scrollTimer= setInterval(function(){		
		$.ajax({ //запрос системной информации
          	type:'POST',
          	url:'php/info.php',
          	success:function(msg){
			
     		$('#info > #value').append(msg); //добавление в div
			heigh+=60;
			if (!$("#value").is(":hover")) //не скролить вниз, если указатель мыши над блоком
			$('#info > #value').scrollTop(heigh);//автоскролл
          	}
        	});
	},1000);


	
})

								
								
