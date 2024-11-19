<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");


$hashed_password = password_hash($_POST["password"], PASSWORD_DEFAULT);
$query = "UPDATE USERS SET PASSWORD_HASH = $1, USER_ADMIN = $2 WHERE USERNAME = $3";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($hashed_password,$_POST["user_admin"], $_POST["username"]));
header("Location: ./admin.php");
exit;
?>
