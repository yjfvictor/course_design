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
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Frameset//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>教务管理页面</title>
<script type="text/javascript" src="js/ajax.js"></script>
</head>

<frameset cols="20,90">
<frame name="menu" src="menu.php" />
<frame name="main" src="welcome.php" />
<noframes>
<h1 style="color:red;text-align:center;position:absolute;top:45%">您的浏览器版本太低，请升级版本后再试。</h1>
</noframes>
</frameset>

</html>
