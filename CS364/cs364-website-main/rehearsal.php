<!DOCTYPE html>
<html>
  <head>
    <title> Rehearsal Attendance </title>
    <link rel="stylesheet" type="text/css" href="csl.css"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>
  <script>
  function addUser(){
    if (document.getElementById('form').checkValidity()){
      alert('User added');
      return true;
    }
    else{
      return false;
    }
    
  }
  </script>
  
  <body class = "partners">    
    <h1>Williamsburg Youth Orchestra Attendance System</h1>
    <a href="logout.php"><button>Logout</button></a>
    <h2>
    <break>
    <img src = "wyo-logo.jpeg" /> </break>
    <nav>
    <br><br>
    <nav>
        <a href="./member_crud.html"><button>Edit Members</button></a> 
        <a href="./user_crud.html"><button>Edit Users</button></a> 
        <a href="./rehearsal.php"><button>Rehearsal</button></a> 
        <a href="./rental.php"><button>Rentals</button></a> 
        <a href="./admin.php"><button>Admin</button></a>
        <br>
        <br>
    </nav>
    </h2>
    <div class = "adminTitle">
    <h2>Rehearsal Attendance</h2></div>
    </div>


    <!-- comment-->

      <!-- displaying the student records -->
    <div class="table">
      <center>
      <style>
        .button {
          background-color: #04AA6D;
          border: none;
          color: white;
          padding: 20px;
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 16px;
          margin: 4px 2px;
        }
        table {
          border-collapse: collapse;
          width: 100%;
          text-align: center;
        }
        
        th, td {
          text-align: middle;
          padding: 8px;
        }
        
        tr:nth-child(even) {
          background-color: white;
        }
        tr:hover {background-color: #D6EEEE;}
        div2 {
          border-radius: 5px;
          background-color: #ffffff;
          padding: 10px;
        }
        </style>
    <h4>Attendance Information</h4>
            <table>
              <tr>

                <th>Rehearsal Number</th>
                <th>Member Email</th>
                <th>Member First Name</th>
              </tr>
              <?php
		session_start(); // start (or resume) session

		// create database connection ($connection)
		$connection = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

		if (!$connection) {
 		   die("Connection failed: " . pg_last_error());
		}
		$result = pg_prepare($connection, "my_query", "SELECT * FROM ATTENDANCE");
		$result = pg_execute($connection, "my_query", array());
		while ($row = pg_fetch_assoc($result)) {
           		 echo "<tr>";
          		 echo "<td>" . $row['rehearsal_number'] . "</td>";
         		 echo "<td>" . $row['email'] . "</td>";
         		 echo "<td>" . $row['firstname'] . "</td>";
                	 echo "</tr>";
      		 }

		?>
            </table>
      
  
  </body>
    
</html>
