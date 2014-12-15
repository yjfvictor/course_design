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
require_once("conf/sqlexec.php");
ob_end_clean();
ob_get_clean();
if ( isset($_POST["method"]) )
{
	header("Content-Type: text/xml; charset=UTF-8");
	if ( $_POST["method"] == "add_record" )
	{
		$i = 0;
		if ( isset($_POST["studentid"]) )
		{
			$colname[$i] = "studentid";
			$colval[$i] = "'".mysql_escape_string($_POST["studentid"])."'";
			$i ++;
		}
		if ( isset($_POST["changes"]) )
		{
			$colname[$i] = "changes";
			$colval[$i] = "'".mysql_escape_string($_POST["changes"])."'";
			$i ++;
		}
		if ( isset($_POST["rec_time"]) )
		{
			$colname[$i] = "rec_time";
			$colval[$i] = "'".mysql_escape_string($_POST["rec_time"])."'";
			$i ++;
		}
		if ( isset($_POST["description"]) )
		{
			$colname[$i] = "description";
			$colval[$i] = "'".mysql_escape_string($_POST["description"])."'";
			$i ++;
		}
		$str = "insert into changes (".join(",",$colname)." ) values (".join(",", $colval ).")";
		$result = sqlexec( $str );
		if ( $result )
		{
			$success = "true";
			$text = "增加记录成功";
		}
		else
		{
			$success = "false";
			$text = "增加记录失败";
		}
	}
	else // del_record
	{
		$str = "delete from changes where id='".mysql_escape_string($_POST["id"])."'";
		$result = sqlexec( $str );
		if ( $result )
		{
			$success = "true";
			$text = "删除记录成功";
		}
		else
		{
			$success = "false";
			$text = "删除记录失败";
		}
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
header("Content-Type: text/html; charset=UTF-8");
require_once("conf/sqlexec.php");
$result = sqlexec("select * from changes");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学生档案管理页面</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/add_del_record.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="../js/IE9.js"></script>
<![endif]-->
<link type="text/css" rel="stylesheet" href="../css/user.css" />
</head>

<body>
<h1>学生档案管理页面</h1>

<hr />

<table align="center" border="1" cellspacing="0" cellpadding="0">
<?php
$cols = mysql_num_fields($result);
echo "<tr>";
echo "<th>记录号</th>";
echo "<th>学号</th>";
echo "<th>变更代码</th>";
echo "<th>记录时间</th>";
echo "<th>描述</th>";
echo "<th>操作</th>";
echo "</tr>";
while ( $row = mysql_fetch_array($result) )
{
	echo "<tr id=\"".urlencode($row["id"])."\">";

	echo "<td>";
	echo $row["id"];
	echo "</td>";
	echo "<td>";
	if ( $row["studentid"] == null )
		echo "暂未填写";
	else
		echo $row["studentid"];
	echo "</td>";
	echo "<td>";
	$change_result = sqlexec( "select * from change_code where code='".$row["changes"]."'" );
	$change_row = mysql_fetch_array($change_result);
	echo $change_row["description"];
	echo "</td>";
	echo "<td>";
	if ( $row["rec_time"] == null )
		echo "暂未填写";
	else
		echo $row["rec_time"];
	echo "</td>";
	echo "<td>";
	if ( $row["description"] == null )
		echo "暂未填写";
	else
		echo $row["description"];
	echo "</td>";

	echo "<td style=\"text-align: center\">";
	echo "<input type=\"button\" value=\"删除记录\" onclick=\"del_record('".urlencode($row[0])."');\" />";
	echo "</td>";
	echo "</tr>";
}
?>
<tr>
<td>自动编号</td>
<td><input type="text" id="studentid" /></td>
<td><select id="changes"><?php
$change_result = sqlexec( "select * from change_code" );
while ( $change_row = mysql_fetch_array($change_result) )
	echo "<option value=\"".$change_row["code"]."\">".$change_row["description"]."</option>";
?></option></td>
<td><input type="text" id="rec_time" /></td>
<td><input type="text" id="description" /></td>
<td style="text-align: center"><input type="button" value="新增记录" onclick="add_record()" /></td>
</tr>
</table>
</body>
</html>
