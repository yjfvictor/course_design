<?php
ob_start();
session_start();
header("Pragma: no-cache");
if ( isset($_SESSION["admin"]) )
{
	header("HTTP/1.1 302 Found");
	header("Location: admin/administration.php");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
if ( isset($_SESSION["user"]) )
{
	header("HTTP/1.1 302 Found");
	header("Location: user.php");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
header("Content-Type: text/html; charset=UTF-8");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学生信息管理系统</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/login.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="js/IE9.js"></script>
<![endif]-->
</head>

<body>
<h1 style="padding-top: 10%; text-align: center; font-size:36px; font-family: '华文行楷', '黑体';">学生信息管理系统</h1>
<form action="" method="post" onsubmit="return false;">
<table align="center">
<tr><td colspan="2" style="padding-top:10%; text-align: center; font-size: 36px; height: 100px; font-family: '黑体';">登录页面</td></tr>
<tr><td>账号：</td><td><input type="text" id="username" name="username" style="width: 200px" /></td></tr>
<tr><td>密码：</td><td><input type="password" id="password" name="password" style="width: 200px" /></td></tr>
<tr><td colspan="2" style="text-align: center"><input type="submit" value="登录" onclick="check()" /></td></tr>
</table>
</form>
<!--[if IE 6]>
<script type="text/javascript" src="js/ie6tip.js"></script>
<![endif]-->
<!--[if IE 7]>
<script type="text/javascript" src="js/ie7tip.js"></script>
<![endif]-->
<!--[if IE 8]>
<script type="text/javascript" src="js/ie8tip.js"></script>
<![endif]-->
</body>
</html>
