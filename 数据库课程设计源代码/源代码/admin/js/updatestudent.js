var httpRequest = null;
var delstuid = null;

function DelResult()
{
	var response = null;
	if ( httpRequest.readyState == 4 )
	{
		if ( httpRequest.status == 200 )
		{
			response = httpRequest.responseXML.documentElement;
			if ( response.getElementsByTagName("success")[0].firstChild.nodeValue == "true" )
			{
				document.getElementById(delstuid).style.display = "none";
				delstuid = null;
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

function ShowResult()
{
	var response = null;
	if ( httpRequest.readyState == 4 )
	{
		if ( httpRequest.status == 200 )
		{
			response = httpRequest.responseXML.documentElement;
			if ( response.getElementsByTagName("success")[0].firstChild.nodeValue != "true" )
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

function delstu(stuid)
{
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		delstuid = stuid;
		httpRequest.onreadystatechange = DelResult;
		httpRequest.open("POST", "updateuser.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=delete&deluser=" + stuid;
		httpRequest.send(poststr);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}

function change( id, key, keyvalue )
{
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "updateuser.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=update&id=" + urlencode(id) + "&key=" + urlencode(key) + "&keyvalue=" + urlencode(keyvalue);
		httpRequest.send(poststr);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}

function addstu()
{
	try
	{
		if ( document.getElementById("id").value == "" )
		{
			window.alert("学号不能为空");
			return false;
		}
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "updateuser.php", true );
		httpRequest.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		poststr = "method=add&id="+urlencode(document.getElementById("id").value);
		if ( document.getElementById("name").value != "" )
			poststr += "&name=" + urlencode(document.getElementById("name").value);
		if ( document.getElementById("sex").value != "" )
			poststr += "&sex=" + urlencode(document.getElementById("sex").value);
		if ( document.getElementById("class").value != "" )
			poststr += "&class=" + urlencode(document.getElementById("class").value);
		if ( document.getElementById("department").value != "" )
			poststr += "&department=" + urlencode(document.getElementById("department").value);
		if ( document.getElementById("birthday").value != "" )
			poststr += "&birthday=" + urlencode(document.getElementById("birthday").value);
		if ( document.getElementById("native_place").value != "" )
			poststr += "&native_place=" + urlencode(document.getElementById("native_place").value);
		httpRequest.send(poststr);

		return true;
	}
	catch(e)
	{
		return false;
	}
	return false;
}
