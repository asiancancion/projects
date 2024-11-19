<!DOCTYPE html>

<html>
  <head>
    <title> Orchestra Members </title>
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
    <center>
      <div class="adminTitle">
        <h2>Admin Page</h2>
      </div>
    </center>


    <!-- comment-->

      <!-- displaying the student records -->
    <div class="table">
      <center>
      <style>
        table {
          border-collapse: collapse;
          width: 90%;
          text-align: center;
        }
        
        th, td {
          text-align: left;
          padding: 8px;
        }
        
        tr:nth-child(even) {
          background-color: white;
        }
        tr:hover {background-color: #D6EEEE;}
        div2 {
          border-radius: 5px;
          background-color: #ffffff;
          padding: 20px;
        }
        </style>
          <h4>Member Records</h4>
            <table>
              <tr>

                <th>First Name</th>
                <th>Last Name</th>
                <th>Phone Number</th>
                <th>Email</th>
                <th>Instrument</th>
              </tr>
              <?php
		session_start(); // start (or resume) session

		// create database connection ($connection)
		$connection = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

		if (!$connection) {
 		   die("Connection failed: " . pg_last_error());
		}
		$result = pg_prepare($connection, "my_query", "SELECT * FROM ORCHESTRA_MEMBER");
		$result = pg_execute($connection, "my_query", array());
		while ($row = pg_fetch_assoc($result)) {
           		 echo "<tr>";
          		 echo "<td>" . $row['firstname'] . "</td>";
         		 echo "<td>" . $row['lastname'] . "</td>";
         		 echo "<td>" . $row['phone_number'] . "</td>";
         		 echo "<td>" . $row['email'] . "</td>";
         		 echo "<td>" . $row['instrument'] . "</td>";
                	 echo "</tr>";
      		 }

		?>
            </table>
            
      
        

      </div>
      <div class="table">
      <center>
  </body>

</html>
