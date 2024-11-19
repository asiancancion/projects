<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "DELETE FROM ORCHESTRA_MEMBER WHERE EMAIL = $1 AND FIRSTNAME = $2";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST['email'], $_POST['firstName']));
header("Location: ./admin.php");
exit;
?>
