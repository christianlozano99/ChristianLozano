var urlBase = 'https://getcontactsmatrixstyle.com/LAMPAPI';
var extension = 'php';

var userId = 0;
var firstName = "";
var lastName = "";

function addContact()
{
	var newContact = document.getElementById("newContact").value;
	document.getElementById("contactAddResult").innerHTML = "";
	
	var jsonpayload = '{"contact" : "' + newContact + '", "userId" : ' + userId + '}';
	var url = urlBase + '/register.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
	try
	{
		xhr.onreadystatechange = function()
		{
			if(this.readyState == 4 && this.status == 200)
			{
				document.getElementById("contactAddResult").innerHTML = "Contact has been added";
			}
		};
		xhr.send(jsonpayload);
	}
	catch(err)
	{
		document.getElementById("contactAddResult").innerHTML = err.message;
	}
}