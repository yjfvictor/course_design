var httpRequest = null;

function BackToHomePage()
{
	var response = null;
	if ( httpRequest.readyState == 4 )
	{
		if ( httpRequest.status == 200 )
		{
			response = httpRequest.responseXML.documentElement;
			if ( response.firstChild.nodeValue == "log out success" )
				window.parent.location = "/";
			else
			{
				retry = window.confirm("服务器发生异常，退出失败\n是否重试？");
				if ( retry )
					logout();
			}
			response = null;
		}
		else
		{
			retry = window.confirm("服务器发生异常，退出失败\n是否重试？");
			if ( retry )
				logout();
		}
		httpRequest = null;
	}
}

function logout()
{
	httpRequest = CreateHttpRequest();
	if ( !httpRequest )
	{
		window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
		return false;
	}
	httpRequest.onreadystatechange = BackToHomePage;
	httpRequest.open("POST", "../logout.php", true );
	httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	httpRequest.send(null);
	return false;
}
