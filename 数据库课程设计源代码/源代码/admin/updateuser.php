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
if ( !isset($_POST["method"]) )
{
	header("HTTP/1.0 400 Bad Request");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
require_once("conf/sqlexec.php");
if ( $_POST["method"] == "update" )
{
	$str = "update student set ".mysql_escape_string($_POST["key"])."='".mysql_escape_string($_POST["keyvalue"])."' where id='".mysql_escape_string($_POST["id"])."'";
	$result = sqlexec($str);
	if ( $result )
	{
		$success = "true";
		$text = "更新成功";
	}
	else
	{
		$success = "false";
		$text = "更新失败";
	}
}
else if ( $_POST["method"] == "delete" )
{
	$str = "delete from student where id='".mysql_escape_string($_POST["deluser"])."'";
	$result = sqlexec($str);
	if ( $result )
	{
		$success = "true";
		$text = "删除成功";
	}
	else
	{
		$success = "false";
		$text = "删除失败";
	}
}
else if ( $_POST["method"] == "add" )
{
	if ( !isset ( $_POST["id"] ) )
	{
		$success = "false";
		$text = "学号不能为空";
	}
	else
	{
		$i = 0;
		$colname[$i] = "id";
		$colval[$i] = "'".mysql_escape_string($_POST["id"])."'";
		$i ++;

		if ( isset($_POST["name"]) )
		{
			$colname[$i] = "name";
			$colval[$i] = "'".mysql_escape_string($_POST["name"])."'";
			$i ++;
		}
		if ( isset($_POST["sex"]) )
		{
			$colname[$i] = "sex";
			$colval[$i] = "'".mysql_escape_string($_POST["sex"])."'";
			$i ++;
		}
		if ( isset($_POST["class"]) )
		{
			$colname[$i] = "class";
			$colval[$i] = "'".mysql_escape_string($_POST["class"])."'";
			$i ++;
		}
		if ( isset($_POST["department"]) )
		{
			$colname[$i] = "department";
			$colval[$i] = "'".mysql_escape_string($_POST["department"])."'";
			$i ++;
		}
		if ( isset($_POST["birthday"]) )
		{
			$colname[$i] = "birthday";
			$colval[$i] = "'".mysql_escape_string($_POST["birthday"])."'";
			$i ++;
		}
		if ( isset($_POST["native_place"]) )
		{
			$colname[$i] = "native_place";
			$colval[$i] = "'".mysql_escape_string($_POST["native_place"])."'";
			$i ++;
		}
		$str = "insert into student (".join(",", $colname).") values (".join(",", $colval).")";
		$result = execsql($str);
		if ( $result )
		{
			$success = "true";
			$text = "新增成功";
		}
		else
		{
			$success = "false";
			$text = "新增失败";
		}
	}
}
else
{
	ob_end_clean();
	ob_get_clean();
	header("HTTP/1.0 400 Bad Request");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
ob_end_clean();
ob_get_clean();
header("Content-Type: text/xml; charset=UTF-8");
?>
<?xml version="1.0" encoding="UTF-8"?>
<delresult>
<success><?php echo $success; ?></success>
<text><?php echo $text; ?></text>
</delresult>
