<!DOCTYPE html>
<html>
  <head>
    <title> Rentals </title>
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
    <div class="adminTitle">
    <h2>Rentals</h2>
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
          <h3>Rehearsal Information</h3>
            <table>
              <tr>

                <th>Serial Number</th>
                <th>Instrument</th>
                <th>Checked out to</th>
                <th>Checked In</th>
              </tr>
              <?php
		session_start(); // start (or resume) session

		// create database connection ($connection)
		$connection = pg_connect("host=localhost dbname=orchestraDatabase user=student password=CompSci364");

		if (!$connection) {
 		   die("Connection failed: " . pg_last_error());
		}
		$result = pg_prepare($connection, "my_query", "SELECT * FROM RENTAL");
		$result = pg_execute($connection, "my_query", array());
		while ($row = pg_fetch_assoc($result)) {
           		 echo "<tr>";
          		 echo "<td>" . $row['serial_number'] . "</td>";
         		 echo "<td>" . $row['instrument_type'] . "</td>";
         		 echo "<td>" . $row['username'] . "</td>";
         		 if ($row['checked_in'] == 't'){
         		   echo "<td> Checked In </td>";
         		 }
         		 else{
         		   echo "<td> Checked Out </td>";
         		 }
                	 echo "</tr>";
      		 }

		?>
            </table>      

      </div>
      <center>
      <div class="adminTitle">
      <h2>Edit Instruments</h2>
      </div>
    </center>
      <center>
    <h4>Add Instrument</h4>
    <div>
    <!-- get data to add in -->
    <form id="form" action="createInstrument.php" method="POST">
      <label>Serial Number</label><br><input 
        type="text" 
        id="serial_number" 
        pattern="[0-9]{1,6}"
        placeholder="Ex: 100001"
        name = "serial_number"
        maxlength = "6"
        required
        ><br><br>    

      <label>Instrument</label><br>
      <select class = "select" name="instrument" id="instrument">
        <option value="Viola">Viola</option>
        <option value="Violin">Violin</option>
        <option value="Cello">Cello</option>
        <option value="Trumpet">Trumpet</option>
        <option value="Tuba">Tuba</option>
        <option value="Oboe">Oboe</option>
        <option value="Clarinet">Clarinet</option>
        <option value="French Horn">French Horn</option>
      </select>
      <br><br>



      <input type="submit" name = "submit" value = "Add Instrument">

    </form>
    </center>
    
    <center>
    <h4>Checkout Instrument</h4>
    <div>
    <!-- get data to add in -->
    <form id="form" action="checkoutInstrument.php" method="POST">
      <label>Serial Number</label><br><input 
        type="text" 
        id="serial_number" 
        pattern="[0-9]{1,6}"
        placeholder="Ex: 100001"
        name = "serial_number"
        maxlength = "6"
        required
        ><br><br>    

      <label>Email</label><br><input
        type="text"
        id="email"
        patter="^[^!-#-$-%-^-&-*-(-)-+-=][A-Z0-9+_.-]+@[A-Z0-9.-]+$"
        placeholder="example@gmail.com"
        name = "email"
        ><br><br>

	

      <input type="submit" name = "submit" value = "Checkout Instrument">

    </form>
    
    </center>
    </div>
    
    <center>
    <h4>Checkin Instrument</h4>
    <div>
    <!-- get data to add in -->
    <form id="form" action="checkInInstrument.php" method="POST">
      <label>Serial Number</label><br><input 
        type="text" 
        id="serial_number" 
        pattern="[0-9]{1,6}"
        placeholder="Ex: 100001"
        name = "serial_number"
        maxlength = "6"
        required
        ><br><br>    

	

      <input type="submit" name = "submit" value = "Check In Instrument">

    </form>
    
    </center>
    </div>
    
    <center>
    <h4>Delete Instrument</h4>
    <div>
    <!-- get data to add in -->
    <form id="form" action="deleteInstrument.php" method="POST">
      <label>Serial Number</label><br><input 
        type="text" 
        id="serial_number" 
        pattern="[0-9]{1,6}"
        placeholder="Ex: 100001"
        name = "serial_number"
        maxlength = "6"
        required
        ><br><br>    



      <input type="submit" name = "submit" value = "Delete Instrument">

    </form>
    </div>
    </center>
    
    
    </div>
        
        </div>
    </body>
</html>
