<?php
error_reporting(0);
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "INSERT INTO RENTAL (SERIAL_NUMBER, INSTRUMENT_TYPE, CHECKED_IN) VALUES ($1, $2, $3)";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["serial_number"],$_POST["instrument"], "false")) or die(pg_last_error());
header("Location: ./rental.php");
exit;
?>
