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
				window.location = "class.php";
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

function del_class( id )
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
		httpRequest.open("POST", "class.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=del&id=" + id;
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

function add_class( )
{
	var poststr = null;
	try
	{
		if ( document.getElementById("class_name").value == "" )
		{
			window.alert("班级名称不能为空");
			return false;
		}
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "class.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=add";
		poststr += "&";
		poststr += "class=" + urlencode(document.getElementById("class_name").value);
		poststr += "&";
		poststr += "monitor=" + urlencode(document.getElementById("class_monitor").value);
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

function AppointMonitor( id )
{
	var poststr = null;
	var monitorname = window.prompt("请输入新班长的学号");
	if ( monitorname == null )
		return false;
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "class.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=AppointMonitor&id=" + id + "&monitorname=" + urlencode(monitorname);
		monitorname = null;
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
