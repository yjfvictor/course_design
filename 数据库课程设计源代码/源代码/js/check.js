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
			window.alert( "您输入的出生日期不合法。不存在这样的时间。");
			return false;
		}
	}
	else
	{
		window.alert( "您输入的出生日期格式不合法。应以yyyy-mm-dd形式输入。");
		return false;
	}
}


function check()
{
	if ( document.getElementById("studentid").value == "" )
	{
		window.alert("学号不能为空！");
		return false;
	}
	else if ( document.getElementById("birthday").value != "" )
	{
		return check_date( document.getElementById("birthday").value );
	}
	else
		return true;
}
