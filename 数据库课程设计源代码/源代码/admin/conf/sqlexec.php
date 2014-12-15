<?php
function sqlexec($sql)
{
	$con = mysql_connect("localhost", "victor", "19911027" );
	if ( !$con )
		die("Connect to MySQL failed");
	mysql_select_db("students_info", $con );
	$result = mysql_query($sql);
	mysql_close($con);
	return $result;
}
?>
