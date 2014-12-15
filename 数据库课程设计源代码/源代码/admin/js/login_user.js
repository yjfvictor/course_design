var httpRequest = null;

function ShowResult()
{
	var response = null;
	if ( httpRequest.readyState == 4 )
	{
		if ( httpRequest.status == 200 )
		{
			response = httpRequest.responseXML.documentElement;
			if ( response.getElementsByTagName("success")[0].firstChild.nodeValue == "true" )
			{
				window.location = "user_management.php";
				//window.alert(response.getElementsByTagName("text")[0].firstChild.nodeValue);
			}
			else
				window.alert(response.getElementsByTagName("text")[0].firstChild.nodeValue);
			response = null;
		}
		else
			window.alert("服务器发生异常");
	}
}

function update_login_user( username, admin )
{
	var str = "method=updateloginuser";
	str += "&username=" + username;
	str += "&admin=" + admin;
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "user_management.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		httpRequest.send(str);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}

function del_login_user( username )
{
	var str = "method=delloginuser&username=" + username;
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "user_management.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		httpRequest.send(str);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}

function add_login_user()
{
	var str = "method=addloginuser";

	if ( document.getElementById("username").value == "" )
	{
		window.alert("用户名不能为空");
		return false;
	}
	else
		str += "&username=" + urlencode(document.getElementById("username").value);

	if ( document.getElementById("password").value == "" )
	{
		window.alert("密码不能为空");
		return false;
	}
	else
		str += "&password=" + urlencode(document.getElementById("password").value);

	if ( document.getElementById("admin").value == "" )
		str += "&admin=user";
	else
		str += "&admin=" + urlencode(document.getElementById("admin").value);

	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "user_management.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		httpRequest.send(str);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}
