<?php
error_reporting(0);
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

$query = "UPDATE RENTAL SET CHECKED_IN = 'FALSE', USERNAME = $1 WHERE SERIAL_NUMBER = $2";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["email"], $_POST["serial_number"]))  or die(pg_last_error());
header("Location: ./rental.php");
exit;
?>
