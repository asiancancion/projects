<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

$query = "UPDATE ORCHESTRA_MEMBER SET PHONE_NUMBER = $1, LASTNAME = $2, INSTRUMENT = $3, ABSENCE_NUMBER = $4 WHERE EMAIL = $5 AND FIRSTNAME = $6";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["phoneNum"],$_POST["lastName"],$_POST["instrument"],0,$_POST["email"], $_POST["firstName"]));
header("Location: ./admin.php");
exit;
?>
