function urlencode( str )
{
	str = encodeURIComponent(str);
	str = str.replace(/%20/g,"+");
	str = str.replace(/(%0D)?(%0A)/g,"%0D%0A");
	return str;
}

function CreateHttpRequest()
{
	if (window.XMLHttpRequest)
		return new XMLHttpRequest();
	else if (window.ActiveXObject)
	{
		try
		{
			return new ActiveXObject("Msxml2.XMLHTTP.6.0");
		}
		catch(e)
		{
			try
			{
				return new ActiveXObject("Msxml2.XMLHTTP.4.0");
			}
			catch(e)
			{
				try
				{
					return new ActiveXObject("Msxml2.XMLHTTP.5.0");
				}
				catch(e)
				{
					try
					{
						return new ActiveXObject("Msxml2.XMLHTTP.4.0");
					}
					catch(e)
					{
						try
						{
							return new ActiveXObject("Msxml2.XMLHTTP.3.0");
						}
						catch(e)
						{
							try
							{
								return new ActiveXObject("Msxml2.XMLHTTP.2.6");
							}
							catch(e)
							{
								try
								{
									return new ActiveXObject("Msxml2.XMLHTTP");
								}
								catch(e)
								{
									try
									{
										return new ActiveXObject("Microsoft.XMLHTTP");
									}
									catch(e)
									{
										return null;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		return null;
	}
}
