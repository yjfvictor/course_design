<?php
ob_start();
session_start();
header("Pragma: no-cache");
header("Content-Type: text/xml; charset=UTF-8");
unset($_SESSION["username"]);
unset($_SESSION["user"]);
unset($_SESSION["admin"]);
session_destroy();
?>
<?xml version="1.0" encoding="UTF-8"?>
<result>log out success</result>
