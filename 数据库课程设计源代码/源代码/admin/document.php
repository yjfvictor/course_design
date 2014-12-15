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
$result = sqlexec("select * from student");
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学生档案管理页面</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/updatestudent.js"></script>
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
echo "<th>学号</th>";
echo "<th>姓名</th>";
echo "<th>性别</th>";
echo "<th>班级</th>";
echo "<th>所属院系编号</th>";
echo "<th>生日</th>";
echo "<th>籍贯</th>";
echo "<th>操作</th>";
echo "</tr>";
while ( $row = mysql_fetch_array($result) )
{
	$id = urlencode($row["id"]);
	echo "<tr id=\"$id\">";

	echo "<td>";
	echo $id;
	echo "</td>";
	echo "<td>";
	if ( $row["name"] == null )
		$name = "";
	else
		$name = $row["name"];
	echo "<input type=\"text\" value=\"$name\" onchange=\"change('$id', 'name', this.value)\" />";
	echo "</td>";
	echo "<td>";
	echo "<select onchange=\"change('$id', 'sex', this.value)\">";
	if ( $row["sex"] == null )
	{
		echo "<option value=\"男\">男</option>";
		echo "<option value=\"女\">女</option>";
		echo "<option value=\"其他\" selected=\"selected\">其他</option>";
	}
	else
	{
		if ($row["sex"] == "男")
		{
			echo "<option value=\"男\" selected=\"selected\">男</option>";
			echo "<option value=\"女\">女</option>";
			echo "<option value=\"其他\">其他</option>";
		}
		else if ($row["sex"] == "女")
		{
			echo "<option value=\"男\">男</option>";
			echo "<option value=\"女\" selected=\"selected\">女</option>";
			echo "<option value=\"其他\">其他</option>";
		}
		else
		{
			echo "<option value=\"男\">男</option>";
			echo "<option value=\"女\">女</option>";
			echo "<option value=\"其他\" selected=\"selected\">其他</option>";
		}
	}
	echo "</select>";
	echo "</td>";
	echo "<td>";
	if ( $row["class"] == null )
		$Class = "";
	else
		$Class = $row["class"];
	echo "<select onchange=\"change('$id', 'class', this.value)\">";
	$classresult = sqlexec("select * from class");
	while ( $classrow = mysql_fetch_array($classresult) )
	{
		if ( $classrow["id"] == $Class )
			echo "<option value=\"".$classrow["id"]."\" selected=\"selected\">";
		else
			echo "<option value=\"".$classrow["id"]."\">";
		echo $classrow["name"];
		echo "</option>";
	}
	echo "</select>";
	echo "</td>";
	echo "<td>";
	if ( $row["department"] == null )
		$department = "";
	else
		$department = $row["department"];
	echo "<select onchange=\"change('$id', 'department', this.value)\">";
	$departmentresult = sqlexec("select * from department");
	while ( $departmentrow = mysql_fetch_array($departmentresult) )
	{
		if ( $departmentrow["id"] == $department )
			echo "<option value=\"".$departmentrow["id"]."\" selected=\"selected\">";
		else
			echo "<option value=\"".$departmentrow["id"]."\">";
		echo $departmentrow["name"];
		echo "</option>";
	}
	echo "</select>";
	echo "</td>";
	echo "<td>";
	if ( $row["birthday"] == null )
		$birthday = "";
	else
		$birthday = $row["birthday"];
	echo "<input type=\"text\" value=\"$birthday\" onchange=\"change('$id','birthday',this.value)\" />";
	echo "</td>";
	echo "<td>";
	if ( $row["native_place"] == null )
		$native_place = "";
	else
		$native_place = $row["native_place"];
	echo "<input type=\"text\" value=\"$native_place\" onchange=\"change('$id','native_place', this.value)\" />";
	echo "</td>";

	echo "<td style=\"text-align: center\">";
	echo "<input type=\"button\" value=\"删除\" onclick=\"delstu('".urlencode($row[0])."');\" />";
	echo "</td>";
	echo "</tr>";
}
?>
<tr>
<td><input type="text" id="id" /></td>
<td><input type="text" id="name" /></td>
<td><input type="text" id="sex" /></td>
<td><input type="text" id="class" /></td>
<td><input type="text" id="department" /></td>
<td><input type="text" id="birthday" /></td>
<td><input type="text" id="native_place" /></td>
<td style="text-align: center"><input type="button" value="新增" onclick="addstu()" /></td>;
</td>
</tr>
</table>
</body>
</html>
