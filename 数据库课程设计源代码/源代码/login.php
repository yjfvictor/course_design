<?php
ob_start();
session_start();
header("Pragma: no-cache");
if ( !isset($_POST["username"]) || !isset($_POST["password"]) )
{
	header("HTTP/1.0 400 Bad Request");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
require_once("conf/sqlexec.php");
header("Content-Type: text/xml; charset=UTF-8");
unset($_SESSION["admin"]);
unset($_SESSION["user"]);
unset($_SESSION["username"]);
session_destroy();
session_start();
$success = "false";
$text = "账号或密码错误";
$result = sqlexec( "select * from login_users where username='".mysql_escape_string($_POST["username"])."'" );
while ( $row = mysql_fetch_array( $result ) )
{
	if ( $row["password"] == md5($_POST["password"]) )
	{
		$success = "true";
		$text = "登录成功";
		$_SESSION["username"] = $row["username"];
		if ( $row["admin"] )
		{
			$_SESSION["admin"] = true;
			$location = "admin/administration.php";
		}
		else
		{
			$_SESSION["user"] = true;
			$location = "user.php";
		}
	}
}
?>
<?xml version="1.0" encoding="UTF-8"?>
<result>
<success><?php echo $success; ?></success>
<text><?php echo $text; ?></text>
<location><?php echo $location; ?></location>
</result>
