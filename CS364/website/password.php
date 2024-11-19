<?php
// Start or resume a session
session_start();

// Connection string
$connectionString = "host=localhost dbname=orchestraDatabase user=student password=CompSci364";

// Connect to the PostgreSQL database
$connection = pg_connect($connectionString);

if (!$connection) {
    die("Connection failed: " . pg_last_error());
}

// Check if the form has been submitted
if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["username"], $_POST["password"])) {
    $username = $_POST["username"];
    $password = $_POST["password"];

    // Hash the password
    $hashed_password = password_hash($password, PASSWORD_DEFAULT);

    // SQL query to insert the hashed password and username into the Users table
    $query = "INSERT INTO Users (username, password_hash) VALUES ($1, $2)";

    // Prepare and execute the query
    $result = pg_prepare($connection, "insert_user", $query);
    $result = pg_execute($connection, "insert_user", array($username, $hashed_password));

    if ($result) {
        echo "User registered successfully!";
    } else {
        echo "Error: " . pg_last_error($connection);
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register User</title>
</head>
<body>
    <h1>Register User</h1>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br><br>
        <button type="submit">Register</button>
    </form>
</body>
</html>
s
