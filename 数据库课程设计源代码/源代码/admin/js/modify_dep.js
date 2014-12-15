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
				window.location = "department.php";
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

function del_dep( id )
{
	var poststr = null;
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "department.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "del=" + id;
		httpRequest.send(poststr);
		poststr = null;

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}

function add_dep( )
{
	var poststr = null;
	try
	{
		if ( document.getElementById("dep_name").value == "" )
		{
			window.alert("学院名称不能为空");
			return false;
		}
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "department.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "add=" + urlencode(document.getElementById("dep_name").value);
		httpRequest.send(poststr);
		poststr = null;

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}
