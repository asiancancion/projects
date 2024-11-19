<!DOCTYPE html>
<?php
session_start(); // start (or resume) session

// create database connection ($connection)
$connection = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

if (!$connection) {
    die("Connection failed: " . pg_last_error());
}

$error = false;
if (! isset($_SESSION["username"]) // already authenticated
    && isset($_POST["username"], $_POST["password"])) {
  // query database for account information
  $result = pg_prepare($connection, "my_query", 'SELECT password_hash, user_admin FROM Users WHERE username = $1;');
  $result = pg_execute($connection, "my_query", array($_POST["username"]));


  // username present in database
  if ($row = pg_fetch_assoc($result)) {
    // verify that the password matches stored password hash
    if (password_verify($_POST["password"], $row["password_hash"])) {
      // store the username to indicate authentication
      $_SESSION["username"] = $_POST["username"];
      $_SESSION["user_admin"] = $row["user_admin"];
    }
    else{
      $error = true;
    }
  }
  else{
    $error = true;
  }
}


if (isset($_SESSION["username"])) { // authenticated
  $location = './member.php';
  if ($_SESSION["user_admin"] == 't'){
    $location = './admin.php';
  }

  header("Location: $location");
  exit;
}

 ?>


<html>
 
  <head>
    <title>Log In</title>
    <link rel="stylesheet" type="text/css" href="csl.css"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
  
  <body class = "s">   
    <h1>Williamsburg Youth Orchestra Attendance System
    </h1>
    <h2>
    <break>
    <img src = "wyo-logo.jpeg" /> </break>
    <nav>
    <!-- <h3>Login Page</h3> -->
    <p>
    


      <div>
        <style>
          input[type=password], select {
            width: 25%;
            padding: 12px 20px;
            margin: 8px 0;
            display: inline-block;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
          }
          input[type=email], select {
            width: 25%;
            padding: 12px 20px;
            margin: 8px 0;
            display: inline-block;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
          }
          
          input[type=submit] {
            width: 20%;
            background-color: gray;
            color: white;
            padding: 14px 20px;
            margin: 8px 0;
            border: none;
            border-radius: 4px;
            cursor: pointer;
          }
          
          input[type=submit]:hover {
            background-color: #45a049;
          }
          
          div {
            border-radius: 5px;
            background-color: #f2f2f2;
            padding: 20px;
          }
          </style>
    <h3>Login</h3>
    <?php if ($error) echo "<p>Invalid username or password.</p>"; ?>
    <form id = "form" action = "<?php echo $_SERVER["PHP_SELF"].
                             "?".$_SERVER["QUERY_STRING"]; ?>" method = "post">
    
      <center>
      	<label for="username">
      	Email</label>
      	<br> 
        <input type = "email" 
        id = "emailAddress" 
        name = "username" 
        required 
        placeholder="name@example.com"
        pattern = "^[A-Za-z0-9_.-]+@[A-Za-z0-9_.-]{2,50}$" 
        title = "Email must be 1-50 characters and only contain spaces, letters, and hyphens"/>
        </br><br></center>
      
      <center>
      	<label for="password">
      	Password</label>
      	<br>
        <input type = "password" 
        name = "password" 
        placeholder="Letters, numbers, special characters" 
        title = "Last Name must be 1-50 characters and only contain spaces, letters, and hyphens"/>
      </br><br></center>


      <center><input type="submit" value="Log in" />
        <br><br></center>
        </form>
      </p>
    </div>

  </body>
  
</html>
