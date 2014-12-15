<?php
ob_start();
session_start();
require_once("conf/sqlexec.php");
ob_end_clean();
ob_get_clean();
header("Pragma: no-cache");
if ( !isset($_SESSION["admin"]) )
{
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
if ( isset( $_POST["method"] ) )
{
	if ( $_POST["username"] == "admin" )
	{
		$success = "false";
		$text = "不得修改admin的权限";
	}
	else if ( $_POST["method"] == "addloginuser" )
	{
		if ( $_POST["admin"] == "admin" )
			$admin = "true";
		else
			$admin = "false";
		$str = "insert into login_users values ('".mysql_escape_string($_POST["username"])."', '".md5($_POST["password"])."', $admin )";
		$result = sqlexec($str);
		if ( $result )
		{
			$success = "true";
			$text = "新增用户成功";
		}
		else
		{
			$success = "false";
			$text = "新增用户失败";
		}
	}
	else if ( $_POST["method"] == "delloginuser" )
	{
		$str = "delete from login_users where username='".mysql_escape_string($_POST["username"])."'";
		$result = sqlexec($str);
		if ( $result )
		{
			$success = "true";
			$text = "删除用户成功";
		}
		else
		{
			$success = "false";
			$text = "删除用户失败";
		}
	}
	else if ( $_POST["method"] == "updateloginuser" )
	{
		if ( $_POST["admin"] == "admin" )
			$admin = "true";
		else
			$admin = "false";
		$str = "update login_users set admin=$admin where username='".mysql_escape_string($_POST["username"])."'";
		$result = sqlexec($str);
		if ( $result )
		{
			$success = "true";
			$text = "用户权限更新成功";
		}
		else
		{
			$success = "false";
			$text = "用户权限更新失败";
		}
	}
	else
	{
		header("HTTP/1.0 400 Bad Request");
		header("Content-Type: text/plain; charset=UTF-8");
		exit(0);
	}
	header("Content-Type: text/xml; charset=UTF-8");
?>
<?xml version="1.0" encoding="UTF-8"?>
<result>
	<success><?php echo $success; ?></success>
	<text><?php echo $text; ?></text>
</result>
<?php
	exit(0);
}
header("Content-Type: text/html; charset=UTF-8");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学生档案管理页面</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" src="js/login_user.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="../js/IE9.js"></script>
<![endif]-->
<link type="text/css" rel="stylesheet" href="../css/user.css" />
</head>

<body>
<h1>登录用户管理页面</h1>

<hr />

<table align="center" border="1" cellspacing="0" cellpadding="0">
<?php
$result = sqlexec("select * from login_users");
echo "<tr>";
echo "<th>用户名</th>";
echo "<th>密码（md5加密)</th>";
echo "<th>权限</th>";
echo "<th>操作</th>";
echo "</tr>";
while ( $row = mysql_fetch_array($result) )
{
	echo "<tr>";
	echo "<td>";
	echo $row["username"];
	echo "</td>";
	echo "<td>";
	echo $row["password"];
	echo "</td>";
	echo "<td>";
	echo "<select onchange=\"update_login_user('".urlencode($row["username"])."', this.value)\">";
	if ( $row["admin"] )
	{
		echo "<option value=\"admin\" selected=\"selected\">教务处</option>";
		echo "<option value=\"user\">录入名单</option>";
	}
	else
	{
		echo "<option value=\"admin\">教务处</option>";
		echo "<option value=\"user\" selected=\"selected\">录入名单</option>";
	}
	echo "</select>";
	echo "</td>";
	echo "<td style=\"text-align: center\">";
	echo "<input type=\"button\" value=\"删除登录用户\" onclick=\"del_login_user('".urlencode($row["username"])."')\" />";
	echo "</td>";
	echo "</tr>";
}
?>
<tr>
<td><input type="text" id="username" /></td>
<td><input type="text" id="password" /></td>
<td><select id="admin"><option value="admin">教务处</option><option value="user" selected="selected">录入名单</option></select></td>
<td style="text-align: center"><input type="button" value="新增登录用户" onclick="add_login_user()" /></td>
</tr>
</table>
</body>
</html>
