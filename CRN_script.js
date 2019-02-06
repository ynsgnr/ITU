javascript:
addCRN();
void(0);
function addCRN(){
    var crn=[13328,13327];
	for(var i=0;i<crn.length;i++)
	{var d=document.getElementById("crn_id"+(i+1));
	d.value=crn[i];
	}
	var buttons = document.getElementsByTagName('input');
	for(var i = 0; i <= buttons.length; i++)
	{
	var value = buttons[i].value;
	if(value=="Submit Changes")
	{buttons[i].click();}
	}
}
