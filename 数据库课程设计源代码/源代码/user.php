<?php
ob_start();
session_start();
header("Pragma: no-cache");
if ( !isset($_SESSION["username"]) )
{
	header("HTTP/1.0 403 Forbidden");
	header("Content-Type: text/plain; charset=UTF-8");
	exit(0);
}
header("Content-Type: text/html; charset=UTF-8");
require_once("conf/sqlexec.php");
if ( isset($_POST["insert"]) )
{
	$colname = "";
	$colval = "";
	if ( isset($_POST["studentid"]) && $_POST["studentid"] != "" )
	{
		$colname .= "id";
		$colval .= "'".mysql_escape_string($_POST["studentid"])."'";
		if ( isset( $_POST["name"] ) && $_POST["name"] != "" )
		{
			$colname .= ", name";
			$colval .= ",'".mysql_escape_string($_POST["name"])."'";
		}
		if ( isset( $_POST["sex"] ) && $_POST["sex"] != "" )
		{
			$colname .= ", sex";
			$colval .= ",'".mysql_escape_string($_POST["sex"])."'";
		}
		if ( isset( $_POST["class"] )  && $_POST["class"] != "" )
		{
			$colname .= ", class";
			$colval .= ",'".mysql_escape_string($_POST["class"])."'";
		}
		if ( isset( $_POST["department"] ) && $_POST["department"] != "" )
		{
			$colname .= ", department";
			$colval .= ",'".mysql_escape_string($_POST["department"])."'";
		}
		if ( isset( $_POST["birthday"] ) && $_POST["birthday"] != "" )
		{
			$colname .= ", birthday";
			$colval .= ",'".mysql_escape_string($_POST["birthday"])."'";
		}
		if ( isset( $_POST["native_place"] ) && $_POST["native_place"] != "" )
		{
			$colname .= ", native_place";
			$colval .= ",'".mysql_escape_string($_POST["native_place"])."'";
		}
		$str = "insert into student ($colname) values ( $colval )";
		sqlexec($str);
	}
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="zh" xml:lang="zh">
<head>
<title>学生信息录入页面</title>
<script type="text/javascript" src="js/ajax.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/logout.js"></script>
<script type="text/javascript" charset="UTF-8" src="js/check.js"></script>
<!--[if lt IE 9]>
<script type="text/javascript" src="js/IE9.js"></script>
<![endif]-->
<link rel="stylesheet" type="text/css" href="css/user.css" />
</head>

<body>
<div style="text-align: right">您好，欢迎<?php echo $_SESSION["username"] ?>&nbsp;&nbsp;&nbsp;<input type="button" value="退出登录" onclick="logout()" /></div>
<h1 style="padding-top: 10%;">学生个人信息录入</h1>
<form style="text-align: left; padding-left: 35%" action="" method="post" onsubmit="return check();">
<table border="0" cellspaing="0">
<tr><td>学号</td><td><input class="text" id="studentid" name="studentid" type="text" /><span style="color: red">*</span></td></tr>
<tr><td>姓名</td><td><input class="text" id="name" name="name" type="text" /></td></tr>
<tr><td>性别</td><td><select id="sex" name="sex"><option>男</option><option>女</option><option>其他</option></select></td></tr>
<tr><td>班级</td><td><select id="class" name="class"><?php
$result = sqlexec( "select * from class" );
while ( $row = mysql_fetch_array($result) )
{
	echo "<option value=\"".$row["id"]."\">";
	echo $row["name"];
	echo "</option>";
}
?></select></td></tr>
<tr><td>所属院系编号</td><td><select id="department" name="department"><?php
$result = sqlexec( "select * from department" );
while ( $row = mysql_fetch_array($result) )
{
	echo "<option value=\"".$row["id"]."\">";
	echo $row["name"];
	echo "</option>";
}
?></select></td></tr>
<tr><td>生日</td><td><input class="text" id="birthday" name="birthday" type="text" /><span style="color:red">(yyyy-mm-dd)</span></td></tr>
<tr><td>籍贯</td><td><input class="text" id="native_place" name="native_place" type="text" /></td></tr>
<tr><td colspan="2" style="text-align: center"><input type="submit" name="insert" value="录入数据" /></td></tr>
</table>
<br />
</form>

<br />
<br />
<br />
<br />

<table align="center" border="1" cellspacing="0" cellpadding="0">
<?php
$result = sqlexec("select * from student");
$cols = mysql_num_fields($result);
echo "<tr>";
echo "<th>学号</th>";
echo "<th>姓名</th>";
echo "<th>性别</th>";
echo "<th>班级</th>";
echo "<th>所属院系编号</th>";
echo "<th>生日</th>";
echo "<th>籍贯</th>";
echo "</tr>";
while ( $row = mysql_fetch_array($result) )
{
	echo "<tr id=\"".urlencode($row["id"])."\">";
	echo "<td>";
	echo $row["id"];
	echo "</td>";
	echo "<td>";
	if ( $row["name"] == null )
		echo "暂未填写";
	else
		echo $row["name"];
	echo "</td>";
	echo "<td>";
	if ( $row["sex"] == null )
		echo "暂未填写";
	else
		echo $row["sex"];
	echo "</td>";
	echo "<td>";
	if ( $row["class"] == null )
		echo "暂未填写";
	else
	{
		$classresult = sqlexec( "select * from class where id = '".$row["class"]."'" );
		$classrow = mysql_fetch_array($classresult);
		echo $classrow["name"];
	}
	echo "</td>";
	echo "<td>";
	if ( $row["department"] == null )
		echo "暂未填写";
	else
	{
		$departmentresult = sqlexec( "select * from department where id = '".$row["department"]."'" );
		$departmentrow = mysql_fetch_array($departmentresult);
		echo $departmentrow["name"];
	}
	echo "</td>";
	echo "<td>";
	if ( $row["birthday"] == null )
		echo "暂未填写";
	else
	{
		echo $row["birthday"];
	}
	echo "</td>";
	echo "<td>";
	if ( $row["native_place"] == null )
		echo "暂未填写";
	else
	{
		echo $row["native_place"];
	}
	echo "</td>";
	echo "</tr>";
}
?>
</table>
</body>

</html>
