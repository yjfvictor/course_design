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
if ( isset($_POST["add"]) )
{
	ob_end_clean();
	ob_get_clean();
	header("Pragma: no-cache");
	header("Content-Type: text/xml; charset=UTF-8");
	$str = "insert into department ( name ) values ( '".mysql_escape_string($_POST["add"])."' )";
	$result = sqlexec( $str );
	if ( $result )
	{
		$success = "true";
		$text = "学院添加成功";
	}
	else
	{
		$success = "false";
		$text = "学院添加失败";
	}
?>
<?xml version="1.0" encoding="UTF-8"?>
<result>
<success><?php echo $success; ?></success>
<text><?php echo $text; ?></text>
</result>
<?php
	exit(0);
}
else if ( isset($_POST["del"]) )
{
	ob_end_clean();
	ob_get_clean();
	header("Pragma: no-cache");
	header("Content-Type: text/xml; charset=UTF-8");
	$str = "delete from department where id = '".mysql_escape_string($_POST["del"])."'";
	$result = sqlexec( $str );
	if ( $result )
	{
		$success = "true";
		$text = "学院删除成功";
	}
	else
	{
		$success = "false";
		$text = "学院删除失败";
	}
?>
<?xml version="1.0" encoding="UTF-8"?>
<result>
<success><?php echo $success; ?></success>
<text><?php echo $text; ?></text>
</result>
<?php
	exit(0);
}
$result = sqlexec("select * from department");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学院信息录入</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/modify_dep.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="../js/IE9.js"></script>
<![endif]-->
<link rel="stylesheet" type="text/css" href="../css/user.css" />
</head>

<body style="padding-top: 10%;">
<h1>学院信息录入页面</h1>

<form style="text-align: left;" action="" method="post" onsubmit="return false;">
<table align="center" border="1" cellspacing="0" cellpadding="0">
<?php
$cols = mysql_num_fields($result);
echo "<th>学院编号</th>";
echo "<th>学院名称</th>";
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
	echo "<td style=\"text-align: center;\">";
	echo "<input type=\"button\" value=\"删除学院\" onclick=\"del_dep('".urlencode($row["id"])."')\" />";
	echo "</td>";
	echo "</tr>";
}
?>
<tr>
<td>自动编号</td>
<td><input type="text" id="dep_name" name="dep_name" class="text" /></td>
<td style="text-align: center;"><input type="submit" value="增加学院" onclick="add_dep()" /></td>
</tr>
</table>
</form>
</body>

</html>

