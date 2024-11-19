<!DOCTYPE html>


<html>
  <head>
    <title>Member Check in</title>
    <link rel="stylesheet" type="text/css" href="csl.css"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
  </head>
  
  
  <body>    
    <h1>Williamsburg Youth Orchestra Attendance System</h1>
    <a href="logout.php"><button>Logout</button></a>
    <h2>
    <break>
    <img src = "wyo-logo.jpeg" /> </break>
    <nav>
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
          <h4>Rehearsal Attendance</h3>
            <table>
              <tr>

                <th>First Name</th>
                <th>Last Name</th>
                <th>Phone Number</th>
                <th>Email</th>
                <th>Instrument</th>
                <th>Rehearsal Number</th>
                <th>Check in</th>
              </tr>
              

              <?php
		session_start(); // start (or resume) session

		// create database connection ($connection)
		$connection = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

		if (!$connection) {
 		   die("Connection failed: " . pg_last_error());
		}
		$email = $_SESSION['username'];
		$result = pg_prepare($connection, "my_query", "SELECT * FROM ORCHESTRA_MEMBER WHERE EMAIL = $1");
		$result = pg_execute($connection, "my_query", array($email));
		while ($row = pg_fetch_assoc($result)) {
           		 echo "<tr> <form action='checkIn.php' method='post'>";
          		 echo "<td>" . $row['firstname'] . "</td>";
         		 echo "<td>" . $row['lastname'] . "</td>";
         		 echo "<td>" . $row['phone_number'] . "</td>";
         		 echo "<td>" . $row['email'] . "</td>";
         		 echo "<td>" . $row['instrument'] . "</td>";
         		 echo "<td> 
    				<select class = 'select1' id='number' name='number'>
    			 	<option value='1'>1</option>
     				<option value='2'>2</option>
   				<option value='3'>3</option>
        			<option value='4'>4</option>
       				<option value='5'>5</option>
       				<option value='6'>6</option>
   				</select>
         		 	</td>";
           		 echo "<td>
           		 	<input type = 'hidden' name = 'email' value ='" . $row['email'] . "'/>
           		 	<input type = 'hidden' name = 'firstName' value ='" . $row['firstname'] . "'/>
                          	<button type='submit' name='checkInButton'>Check In</button>
                      		</form></td>
                		</label></td>";
                	echo "</tr>";
      		 }

		?>
            </table>
    </div>
  
   
    
    
  </body>
  
  
</html>
