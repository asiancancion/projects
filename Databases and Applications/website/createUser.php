<?php
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$hashed_password = password_hash($_POST["password"], PASSWORD_DEFAULT);
$query = "INSERT INTO USERS (USERNAME, PASSWORD_HASH, USER_ADMIN) VALUES ($1, $2, $3)";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["username"],$hashed_password, $_POST["user_admin"]));
header("Location: ./admin.php");
exit;
?>
