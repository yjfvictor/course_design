var httpRequest = null;

function is_valid_date ( year, month, day )
{
	if ( month == "00" || day == "00" )
		return false;
	if ( month > 12 )
		return false;
	if ( month == "01" || month == "03" || month == "05" || month == "07" || month == "08" || month == "10" || month == "12" )
	{
		if ( day > 31 )
			return false;
	}
	else if ( month == "04" || month == "06" || month == "09" || month == "11" )
	{
		if ( day > 30 )
			return false;
	}
	else // month == 2
	{
		if ( is_leap_year( year ) )
		{
			if ( day > 29 )
				return false;
		}
		else
		{
			if ( day > 28 )
				return false;
		}
	}
	return true;
}


function check_date( dateinput )
{
	var regex = /^([1-2][0-9][0-9][0-9])-([0-1][0-9])-([0-3][0-9])$/g;
	if ( regex.test( dateinput ) )
	{
		var year = dateinput.replace( regex, "$1" );
		var month = dateinput.replace( regex, "$2" );
		var day = dateinput.replace( regex, "$3" );

		if ( is_valid_date( year, month, day ) )
		{
			return true;
		}
		else
		{
			window.alert( "您输入的记录时间不合法。不存在这样的时间。");
			return false;
		}
	}
	else
	{
		window.alert( "您输入的记录时间格式不合法。应以yyyy-mm-dd形式输入。");
		return false;
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
			if ( response.getElementsByTagName("success")[0].firstChild.nodeValue == "true" )
			{
				window.location = "punishment.php";
			}
			else
				window.alert(response.getElementsByTagName("text")[0].firstChild.nodeValue);
			response = null;
		}
		else
			window.alert("服务器发生异常");
	}
}

function del_punish(id)
{
	var str = "method=del_punish&id=" + id;
	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "punishment.php", true );
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

function add_punish()
{
	var str = "method=add_punish";
	if ( document.getElementById("studentid").value != "" )
		str += "&studentid=" + urlencode(document.getElementById("studentid").value);
	if ( document.getElementById("levels").value != "" )
		str += "&levels=" + urlencode(document.getElementById("levels").value);
	if ( document.getElementById("rec_time").value != "" )
	{
		if ( check_date(document.getElementById("rec_time").value) )
			str += "&rec_time=" + urlencode(document.getElementById("rec_time").value);
		else
			return false;
	}
	if ( document.getElementById("description").value != "" )
		str += "&description=" + urlencode(document.getElementById("description").value);

	try
	{
		httpRequest = CreateHttpRequest();
		if ( !httpRequest )
		{
			window.alert("您的浏览器不支持AJAX，请升级您的浏览器");
			return false;
		}
		httpRequest.onreadystatechange = ShowResult;
		httpRequest.open("POST", "punishment.php", true );
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
