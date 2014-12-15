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
if ( isset($_POST["method"]) )
{
	if ( $_POST["method"] == "add" )
	{
		if ( isset ( $_POST["monitor"] ) )
		{
			$str = "insert into class ( name, monitor ) values ";
			$str .= "( '".mysql_escape_string($_POST["class"])."', ";
			$str .= "'".mysql_escape_string($_POST["monitor"])."' )";
		}
		else
			$str = "insert into class ( name ) values ( '".mysql_escape_string($_POST["class"])."' )";
		$result = sqlexec( $str );
		if ( $result )
		{
			$success = "true";
			$text = "班级添加成功";
		}
		else
		{
			$success = "false";
			$text = "班级添加失败";
		}
	}
	else if ( $_POST["method"] == "del" )
	{
		$str = "delete from class where id = '".mysql_escape_string($_POST["id"])."'";
		$result = sqlexec( $str );
		if ( $result )
		{
			$success = "true";
			$text = "班级删除成功";
		}
		else
		{
			$success = "false";
			$text = "班级删除失败";
		}
	}
	else  // AppointMonitor
	{
		$str = "update class set monitor='".mysql_escape_string($_POST["monitorname"])."' where id='".mysql_escape_string($_POST["id"])."'";
		$result = sqlexec($str);
		if ( $result )
		{
			$success = "true";
			$text = "新班长任命成功";
			$text = $str;
		}
		else
		{
			$success = "false";
			$text = "新班长任命失败";
		}
	}
	ob_end_clean();
	ob_get_clean();
	header("Pragma: no-cache");
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
$result = sqlexec("select * from class");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>班级信息录入</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/modify_class.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="../js/IE9.js"></script>
<![endif]-->
<link rel="stylesheet" type="text/css" href="../css/user.css" />
</head>

<body style="padding-top: 10%;">
<h1>班级信息录入页面</h1>

<form style="text-align: left;" action="" method="post" onsubmit="return false;">
<table align="center" border="1" cellspacing="0" cellpadding="0">
<?php
$cols = mysql_num_fields($result);
echo "<th>班级编号</th>";
echo "<th>班级名称</th>";
echo "<th>班长</th>";
echo "<th>操作</th>";
echo "</tr>";
while ( $row = mysql_fetch_array($result) )
{
	echo "<tr id=\"".urlencode($row["id"])."\">";
	echo "<td>";
	echo $row["id"];
	echo "</td>";
	echo "<td>";
	echo $row["name"];
	echo "</td>";
	echo "<td>";
	if ( $row["monitor"] == null )
		echo "[暂无班长]";
	else
		echo $row["monitor"];
	echo "&nbsp;&nbsp;&nbsp;&nbsp;";
	echo "<input type=\"button\" value=\"任命新班长\" onclick=\"AppointMonitor('".urlencode($row["id"])."')\" />";
	echo "</td>";
	echo "<td style=\"text-align: center;\">";
	echo "<input type=\"button\" value=\"删除班级\" onclick=\"del_class('".urlencode($row["id"])."')\" />";
	echo "</td>";
	echo "</tr>";
}
?>
<tr>
<td>自动编号</td>
<td><input type="text" id="class_name" name="class_name" class="text" /></td>
<td><input type="text" id="class_monitor" name="class_monitor" class="text" /></td>
<td style="text-align: center;"><input type="submit" value="增加班级" onclick="add_class()" /></td>
</tr>
</table>
</form>
</body>

</html>
