var pin1 = document.getElementById("pin1_button");
var pin1_status = 0;
//var text1 = document.getElementById("pin1_text");

var pin2 = document.getElementById("pin2_button");
var pin2_status = 0;
//var text2 = document.getElementById("pin2_text");

var pin3 = document.getElementById("pin3_button");
var pin3_status = 0;
//var text3 = document.getElementById("pin3_text");

function pin_state()
{
	var request = new XMLHttpRequest();
	request.open('GET','/pin_status',true);
				
	request.onload = function() 
	{
		if (request.readyState == 4 && request.status == 200) 
		{
			var response = request.responseText;
			pin1_status = Number.parseInt(response[0]);
			pin2_status = Number.parseInt(response[1]);
			pin3_status = Number.parseInt(response[2]);
			
			if (pin1_status == 0)
            {
				pin1.classList.add('pin_off');
				//text1.innerHTML = "OUTPUT 1 OFF";
			}
			else
            {
				pin1.classList.add('pin_on');
                //text1.innerHTML = "OUTPUT 1 ON";
			}
			
			if (pin2_status == 0)
            {
				pin2.classList.add('pin_off');
				//text2.innerHTML = "OUTPUT 2 OFF";
			}
			else
            {
				pin2.classList.add('pin_on');
                //text2.innerHTML = "OUTPUT 2 ON";
			}
			
			if (pin3_status == 0)
            {
				pin3.classList.add('pin_off');
				//text3.innerHTML = "OUTPUT USB OFF";
			}
			else
            {
				pin3.classList.add('pin_on');
                //text3.innerHTML = "OUTPUT USB ON";
			}
		}
	}
	request.send();
}
			
function pin1_inverse() 
{
	var request = new XMLHttpRequest();
	request.open('GET','/pin1_switch',false);
	request.send();
				
	if (request.readyState == 4 && request.status == 200) 
	{
		var response = request.responseText;
					
        if (response  == '0')
		{
			pin1.classList.remove('pin_on');
            pin1.classList.add('pin_off');
            //text1.innerHTML = "OUTPUT 1 OFF";
			pin1_status = 0;
		} 
		else 
		{
			pin1.classList.remove('pin_off');
			pin1.classList.add('pin_on');
			//text1.innerHTML = "OUTPUT 1 ON";
			pin1_status = 1;
		}
	}
}

function pin2_inverse() 
{
	var request = new XMLHttpRequest();
	request.open('GET','/pin2_switch',false);
	request.send();
				
	if (request.readyState == 4 && request.status == 200) 
	{
		var response = request.responseText;
					
        if (response  == '0')
		{
			pin2.classList.remove('pin_on');
            pin2.classList.add('pin_off');
            //text2.innerHTML = "OUTPUT 2 OFF";
			pin2_status = 0;
		} 
		else 
		{
			pin2.classList.remove('pin_off');
			pin2.classList.add('pin_on');
			//text2.innerHTML = "OUTPUT 2 ON";
			pin2_status = 1;
		}
	}
}

function pin3_inverse() 
{
	var request = new XMLHttpRequest();
	request.open('GET','/pin3_switch',false);
	request.send();
				
	if (request.readyState == 4 && request.status == 200) 
	{
		var response = request.responseText;
					
        if (response  == '0')
		{
			pin3.classList.remove('pin_on');
            pin3.classList.add('pin_off');
            //text3.innerHTML = "OUTPUT USB OFF";
			pin3_status = 0;
		} 
		else 
		{
			pin3.classList.remove('pin_off');
			pin3.classList.add('pin_on');
			//text3.innerHTML = "OUTPUT USB ON";
			pin3_status = 1;
		}
	}
}
			
document.addEventListener('DOMContentLoaded', pin_state);
pin1.addEventListener('click', pin1_inverse);
pin2.addEventListener('click', pin2_inverse);
pin3.addEventListener('click', pin3_inverse);