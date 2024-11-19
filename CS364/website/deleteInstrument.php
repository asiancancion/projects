<?php
error_reporting(0);
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "DELETE FROM RENTAL WHERE SERIAL_NUMBER=$1";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST['serial_number']));
header("Location: ./rental.php");
exit;
?>
