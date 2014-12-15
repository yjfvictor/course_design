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
				window.location = response.getElementsByTagName("location")[0].firstChild.nodeValue;
				//window.alert(response.getElementsByTagName("text")[0].firstChild.nodeValue);
			}
			else
				window.alert(response.getElementsByTagName("text")[0].firstChild.nodeValue);
			response = null;
		}
		else
		{
			window.alert("服务器发生异常");
		}
		httpRequest = null;
	}
}

function check()
{
	try
	{
		var submitstr = null;
		if ( document.getElementById("username").value == "" )
		{
			window.alert("账号不能为空");
			return false;
		}
		else
		{
			submitstr = "username=" + urlencode(document.getElementById("username").value);
			if ( document.getElementById("password").value == "" )
			{
				window.alert("密码不能为空");
				return false;
			}
			else
			{
				submitstr += "&";
				submitstr += "password=" + urlencode(document.getElementById("password").value);
				httpRequest = CreateHttpRequest();
				if ( !httpRequest )
				{
					window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
					return false;
				}
				httpRequest.onreadystatechange = ShowResult;
				httpRequest.open("POST", "login.php", true );
				httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
				httpRequest.send(submitstr);

				return true;
			}
		}
	}
	catch(e)
	{
		return false;
	}
	return false;
}
