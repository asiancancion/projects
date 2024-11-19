<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "INSERT INTO ORCHESTRA_MEMBER (EMAIL, PHONE_NUMBER, FIRSTNAME, LASTNAME, INSTRUMENT, ABSENCE_NUMBER) VALUES ($1, $2, $3, $4, $5, $6)";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["email"],$_POST["phoneNum"],$_POST["firstName"],$_POST["lastName"],$_POST["instrument"], 0));
header("Location: ./admin.php");
exit;
?>
