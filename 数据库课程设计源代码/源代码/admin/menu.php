<?php
ob_start();
session_start();
header("Pragma: no-cache");
if ( !isset($_SESSION["admin"]) )
{
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
header("Content-Type: text/html; charset=UTF-8");
require_once("conf/sqlexec.php");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>管理页面菜单</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" src="js/logout.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="../js/IE9.js"></script>
<![endif]-->
<link type="text/css" rel="stylesheet" href="../css/menu.css" />
</head>

<body>
<h1>管理页面</h1>

<hr />

<ol>
<li><a href="user_management.php" target="main">登录用户管理</a></li>
<li><a href="../user.php" target="main">学生信息录入</a></li>
<li><a href="document.php" target="main">学生档案管理</a></li>
<li><a href="changes.php" target="main">学籍变更管理</a></li>
<li><a href="class.php" target="main">班级管理</a></li>
<li><a href="department.php" target="main">学院管理</a></li>
<li><a href="reward.php" target="main">奖学金评定</a></li>
<li><a href="punishment.php" target="main">处分页面</a></li>
<!--<li><a href="sql.php" target="main">SQL页面</a></li> -->
<li><a href="#" onclick="return logout()">退出</a></li>
</ol>
</body>

</html>
