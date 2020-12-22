var urlBase = 'https://getcontactsmatrixstyle.com/LAMPAPI';
var extension = 'php';

var userId = 0;
var firstName = "";
var lastName = "";

function login()
{
	userId = 0;
	firstName = "";
	lastName = "";
	
	var login = document.getElementById("UsernameField").value;
	var password = document.getElementById("passwordField").value;
	var hash = md5(password);
	
	document.getElementById("loginResult").innerHTML = "";
	
	var jsonPayload = '{"login" : "' + login + '", "password" : "' + hash + '"}';
	var url = urlBase + '/login.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, false);
	xhr.setRequestHeader("Content-type", "application/json; charset=UTF-8");
	try
	{
		xhr.send(jsonPayload);
		
		var jsonObject = JSON.parse(xhr.responseText);
		userId = jsonObject.UserID;
		
		if(userId < 1)
		{
			document.getElementById("loginResult").innerHTML = "User/Password combination incorrect";
			return;
		}
		firstName = jsonObject.FirstName;
		lastName = jsonObject.LastName;
		
		saveCookie();
		
		window.location.href = "/html/newLogin.html";
	}
	catch(err)
	{
		document.getElementById("loginResult").innerHTML = err.message;
	}
}

function saveCookie()
{
	var minutes = 20;
	var date = new Date();
	date.setTime(date.getTime()+(minutes*60*1000));	
	document.cookie = "firstName=" + firstName + ",lastName=" + lastName + ",userId=" + userId + ";expires=" + date.toGMTString();
}

function readCookie()
{
	userId = -1;
	var data = document.cookie;
	var splits = data.split(",");
	for(var i = 0; i < splits.length; i++) 
	{
		var thisOne = splits[i].trim();
		var tokens = thisOne.split("=");
		if( tokens[0] == "firstName" )
		{
			firstName = tokens[1];
		}
		else if( tokens[0] == "lastName" )
		{
			lastName = tokens[1];
		}
		else if( tokens[0] == "userId" )
		{
			userId = parseInt( tokens[1].trim() );
		}
	}
	
	if( userId < 0 )
	{
		window.location.href = "index.html";
	}
	else
	{
		document.getElementById("UsernameField").innerHTML = "Logged in as " + firstName + " " + lastName;
	}
}

//CREATING NEW Contact
function addContact()
{
	//userId = 0;
	document.getElementById("addContacts").innerHTML = "";
	
	//info gathering
	var firstName = document.getElementById("firstName").value;
	var lastName = document.getElementById("lastName").value;
	var email = document.getElementById("email").value;
	var number = document.getElementById("number").value;
	//var id = document.getElementById("id").value;
	var id = userId;
	
	var jsonPayload = JSON.stringify({firstName : firstName, lastName : lastName, email : email, number : number, id : userId});
	var url = urlBase + '/create.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
		    {
		    	var jsonObject = JSON.parse(xhr.responseText);
				//checking to see if it worked
				firstName = jsonObject.firstName;
				lastName = jsonObject.lastName;
				email = jsonObject.email;
				number = jsonObject.number;
				id = jsonObject.id;
			}
		};
		xhr.send(jsonPayload);
		
	}	
	catch(err)
	{
		document.getElementById("addContacts").innerHTML = err.message;
	}
	document.getElementById("addContacts").innerHTML = "contact added!";

}

//UPDATE CONTACT
function update()
{
	document.getElementById("update").innerHTML = "";
	
	//gather old info 
	var firstName = document.getElementById("firstName").value;
	var lastName = document.getElementById("lastName").value;
	var number = document.getElementById("number").value;
	var email = document.getElementById("email").value;
	var id = userId;
	
	//gather new info 
	var newFirst = document.getElementById("newFirst").value;
	var newLast = document.getElementById("newLast").value;
	var newEmail = document.getElementById("newEmail").value;
	var newNumber = document.getElementById("newNumber").value;
	
	var jsonPayload = JSON.stringify({firstName : firstName, lastName : lastName, email : email, number : number, id : userId, newFirst : newFirst, newLast : newLast, newEmail : newEmail, newNumber : newNumber});
	var url = urlBase + '/update.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    document.getElementById("update").innerHTML = "Contact updated Successfully!";
				var jsonObject = JSON.parse(xhr.responseText);
				window.location.href = "/html/newLogin.html";
			}
		};
		xhr.send(jsonPayload);
	}
	catch(err)
	{
		document.getElementById("update").innerHTML = err.message;
	}
}

//REGISTERATION
function register()
{
	userId = 0;
	document.getElementById("register").innerHTML = "";
	
	//info gathering
	var firstName = document.getElementById("firstName").value;
	var lastName = document.getElementById("lastName").value;
	var userName = document.getElementById("userName").value;
	var password = document.getElementById("password").value;
	var email = document.getElementById("email").value;
	//var hash = md5(password);

	var jsonPayload = JSON.stringify({firstName : firstName, lastName : lastName, username : userName, password : password, email : email});
	var url = urlBase + '/register.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
{
	xhr.onreadystatechange = function()
	{
		if (this.readyState == 4 && this.status == 200) 
		{
			var jsonObject = JSON.parse(xhr.responseText);
			window.firstName = firstName;
			window.lastName = lastName;
			saveCookie();
			window.location.href = "/";
		}
	};
	console.login = firstName;
	console.login = lastName;
	console.login = userName;
	console.login = password;
	console.login = email;
	xhr.send(jsonPayload);
}
catch(err)
{
	document.getElementById("register").innerHTML = err.message;
}
//document.getElementById("register").innerHTML = echo.message;
}

// DELETE CONTACT
function deleteAccount()
{
	//userId = 0;
	document.getElementById("deleteContacts").innerHTML = "";
	
	//getting the info for php
	var firstName = document.getElementById("firstName").value;
	var lastName = document.getElementById("lastName").value;
	var email = document.getElementById("email").value;
	var number = document.getElementById("number").value;
	var id = userId;

	var jsonPayload = JSON.stringify({firstName : firstName, lastName : lastName, email : email, number : number, id : userId});
	var url = urlBase + '/delete.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    document.getElementById("deleteContacts").innerHTML = "Contact deleted Successfully!";
				var jsonObject = JSON.parse(xhr.responseText);
				window.location.href = "/html/newLogin.html";
				
			}
			
		};
		xhr.send(jsonPayload);
	}
	catch(err)
	{
		document.getElementById("deleteContacts").innerHTML = err.message;
	}
}

//Function to read / search
function read()
{
	document.getElementById("read").innerHTML = "";
	var id = userId;
	var search = document.getElementById("searchBar").value;
	var searchList = "";
	
	var jsonPayload = JSON.stringify({id : userId, search: search});
	var url = urlBase + '/read.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    
                document.getElementById("list").innerHTML = ""; 
                document.getElementById("newList").innerHTML = "";
			    document.getElementById("read").innerHTML = "<p>search has been performed!</p>";
			    //document.getElementById("read").innerHTML = "<li>" + xhr.responseText + "</li>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			    //var jsonObject = JSON.parse(xhr.responseText);
				//document.getElementById("read").innerHTML = xhr.responseText;
			/*	for(var i = 0; i < jsonObject.results.length; i++)
				{
				    searchList += jsonObject.results[i];
				    if(i < jsonObject.results.length - 1)
				    {
				        searchList += "<br />\r\n";
				    }
				} 
				document.getElementsByTagName("p")[0].innerHTML = searchList;
				*/
				var flag = 0;

                if(flag == 0)
                {
    				var ul = document.getElementById("list");
    				 ul.innerHTML += "<li>" +   xhr.responseText.replaceAll('lineEnded', '<br/><br/>') + "</li>";
    				 xhr.responseText;
    				 flag = -1;
                }
			}
			
			
            //made flag because somtimes it'd double print the results otherwise

              /*  var ul = document.getElementById("list");


				var contacts = xhr.responseText;

				var newtext = xhr.responseText.replaceAll(/\"/g, " ").replaceAll("{" ,"").replaceAll("}","").replaceAll("[","").replaceAll("]","").replaceAll("firstName", "<p></p>First Name:").replaceAll("results : ","<p>Results</p>" );

                newtext = newtext.replaceAll("error","").replaceAll(",","|").replaceAll(" :", "").replaceAll("lastName", "Last Name:").replaceAll("email", "Email:").replaceAll("number", "Number:").replaceAll("id0|", "Result");


				ul.innerHTML += "<li>" +  newtext + "</li>";
				flag = -1;
				*/
			
		};
			    
		xhr.send(jsonPayload);
	}
	catch(err)
	{
		document.getElementById("read").innerHTML = err.message;
		document.getElementById("read").innerHTML = "Contact was not found! please try again.";
	}
	
}

//Function to sign out
function logout()
{
    userId = 0;
	firstName = "";
	lastName = "";
	document.cookie = "firstName= ; expires = Thu, 01 Jan 1970 00:00:00 GMT";
	window.location.href = "index.html";
}

//Function which gets all the contacts using userId
 /* function getContactInfo()
{
    document.getElementById("contactInfo").innerHTML = "";
	var id = userId;
//	var search = document.getElementById("searchBar").value;
//	var searchList = "";
	
	var jsonPayload = JSON.stringify({id : userId});
	var url = urlBase + '/listAllCont.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    document.getElementById("contactInfo").innerHTML = "";
			    document.getElementById("contactInfo").innerHTML = "<p>list of all contacts</p>";
               // document.getElementById("").innerHTML = ""; 
			  //  document.getElementById("read").innerHTML = "<p>search has been performed!</p>";
			    //document.getElementById("read").innerHTML = "<li>" + xhr.responseText + "</li>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			    //var jsonObject = JSON.parse(xhr.responseText);
				//document.getElementById("read").innerHTML = xhr.responseText;
			/*	for(var i = 0; i < jsonObject.results.length; i++)
				{
				    searchList += jsonObject.results[i];
				    if(i < jsonObject.results.length - 1)
				    {
				        searchList += "<br />\r\n";
				    }
				} 
				document.getElementsByTagName("p")[0].innerHTML = searchList;
				*/
		//	}
			
			
            //made flag because somtimes it'd double print the results otherwise

              /*  var ul = document.getElementById("list");


				var contacts = xhr.responseText;

				var newtext = xhr.responseText.replaceAll(/\"/g, " ").replaceAll("{" ,"").replaceAll("}","").replaceAll("[","").replaceAll("]","").replaceAll("firstName", "<p></p>First Name:").replaceAll("results : ","<p>Results</p>" );

                newtext = newtext.replaceAll("error","").replaceAll(",","|").replaceAll(" :", "").replaceAll("lastName", "Last Name:").replaceAll("email", "Email:").replaceAll("number", "Number:").replaceAll("id0|", "Result");


				ul.innerHTML += "<li>" +  newtext + "</li>";
				flag = -1;
				
			
		};
			    var flag = 0;

                if(flag == 0)
                {
    				var ul = document.getElementById("list");
    				 ul.innerHTML += "<li>" +   xhr.responseText + "</li>";
    				 flag = -1;
                }
		xhr.send(jsonPayload);
	}
	catch(err)
	{
		document.getElementById("contactInfo").innerHTML = err.message;
		document.getElementById("contactInfo").innerHTML = "Contact was not found! please try again.";
	}
   
} */

function getContactInfo()
{
    document.getElementById("contactInfo").innerHTML = "";
	var id = userId;
	//var search = document.getElementById("searchBar").value;
	//var searchList = "";
	
	var jsonPayload = JSON.stringify({id : userId});
	var url = urlBase + '/listAllCont.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
	
	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    
                document.getElementById("newList").innerHTML = ""; 
                document.getElementById("list").innerHTML = "";
			    document.getElementById("read").innerHTML = "<p>All Contacts has been performed!</p>";
			    //document.getElementById("read").innerHTML = "<li>" + xhr.responseText + "</li>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			   // document.getElementById("read").innerHTML = "<p> </p>";
			    //var jsonObject = JSON.parse(xhr.responseText);
				//document.getElementById("read").innerHTML = xhr.responseText;
			/*	for(var i = 0; i < jsonObject.results.length; i++)
				{
				    searchList += jsonObject.results[i];
				    if(i < jsonObject.results.length - 1)
				    {
				        searchList += "<br />\r\n";
				    }
				} 
				document.getElementsByTagName("p")[0].innerHTML = searchList;
				*/
				var flag = 0;

                if(flag == 0)
                {
    				var ul = document.getElementById("newList");
    				 ul.innerHTML += "<li>" +   xhr.responseText.replaceAll('lineEnded', '<br/><br/>') + "</li>";
    				 flag = -1;
                }
			}
			
			
            //made flag because somtimes it'd double print the results otherwise

              /*  var ul = document.getElementById("list");


				var contacts = xhr.responseText;

				var newtext = xhr.responseText.replaceAll(/\"/g, " ").replaceAll("{" ,"").replaceAll("}","").replaceAll("[","").replaceAll("]","").replaceAll("firstName", "<p></p>First Name:").replaceAll("results : ","<p>Results</p>" );

                newtext = newtext.replaceAll("error","").replaceAll(",","|").replaceAll(" :", "").replaceAll("lastName", "Last Name:").replaceAll("email", "Email:").replaceAll("number", "Number:").replaceAll("id0|", "Result");


				ul.innerHTML += "<li>" +  newtext + "</li>";
				flag = -1;
				*/
			
		};
			    
		xhr.send(jsonPayload);
	}
	catch(err)
	{
		document.getElementById("contactInfo").innerHTML = err.message;
		document.getElementById("contactInfo").innerHTML = "Contact was not found! please try again.";
	}
}

//Function to delete the User itself 
function deleteUser()
{
    document.getElementById("deleteUser").innerHTML = "";
    var id = userId;
    
    var jsonPayload = JSON.stringify({id : userId});
    var url = urlBase + '/deleteUser.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
    
    	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    firstName = "";
                lastName = "";
			    document.getElementById("deleteUser").innerHTML = "User has been deleted!";
			    var jsonObject = JSON.parse(xhr.responseText);
			    window.location.href = "/";
			}
		};
		xhr.send(jsonPayload);
	}
	
	catch(err)
	{
	    document.getElementById("deleteUser").innerHTML = err.message;
	}
	document.cookie = "firstName= ; expires = Thu, 01 Jan 1970 00:00:00 GMT";
}

//Function to delete all contacts 
function deleteAllContacts()
{
    document.getElementById("deleteAllContacts").innerHTML = "";
    var id = userId;
    
    var jsonPayload = JSON.stringify({id : userId});
    var url = urlBase + '/deleteContacts.' + extension;
	
	var xhr = new XMLHttpRequest();
	xhr.open("POST", url, true);
	xhr.setRequestHeader("Content-type", "application/json");
    
    	try
	{
		xhr.onreadystatechange = function()
		{
			if (this.readyState == 4 && this.status == 200) 
			{
			    document.getElementById("deleteAllContacts").innerHTML = "Contacts has been deleted!";
			    var jsonObject = JSON.parse(xhr.responseText);
			    window.location.href = "/html/newLogin.html";
			}
		};
		xhr.send(jsonPayload);
	}
	
	catch(err)
	{
	    document.getElementById("deleteAllContacts").innerHTML = err.message;
	    document.getElementById("deleteAllContacts").innerHTML ="pls work";
	}
}

