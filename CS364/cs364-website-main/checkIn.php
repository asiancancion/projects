<?php
error_reporting(0);
$db = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");
$query = "INSERT INTO ATTENDANCE (REHEARSAL_NUMBER, EMAIL, FIRSTNAME) VALUES ($1, $2, $3)";
$statement = pg_prepare($db, "my_query", $query);
$result = pg_execute($db, "my_query", array($_POST["number"], $_POST["email"],$_POST["firstName"]));

if ($result){
  $message = "Checked In";
}
else{
  $message = "Already Checked In";
}
echo "<script>alert('$message'); window.location.href='logout.php';</script>";
exit;
?>
