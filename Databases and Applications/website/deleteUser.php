<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "DELETE FROM USERS WHERE USERNAME = $1";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["username"])) or die(pg_last_error());
header("Location: ./admin.php");
exit;
?>
