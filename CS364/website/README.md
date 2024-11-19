# Williamsburg Youth Orchestra Attendance System

## Project Overview
This project is a web-based attendance and administration system designed for the Williamsburg Youth Orchestra. It is built using **HTML**, **CSS**, and **JavaScript**, with backend support in **PHP** and an integrated **SQL database**. The system facilitates logging attendance for rehearsals, managing user data, and tracking instrument check-in/out activities.

## Features

### General Features
- **Responsive Design**: The system utilizes responsive HTML and CSS layouts to provide an accessible interface on various devices.
- **Dynamic Validation**: JavaScript ensures form validation on the client side before submission.
- **Database Integration**: SQL database stores user information, attendance records, and instrument details.

### User-Specific Features
- **Login and Authentication**: Users can log in using their credentials. User roles (admin/member) determine access levels.
- **Attendance Tracking**: Members can check in/out for rehearsals and log instrument usage.

### Admin Features
- **CRUD Operations**: Administrators have access to create, read, update, and delete records for:
  - Members
  - Rehearsals
  - Instruments
- **Member Record Display**: A structured table showcases user details such as name, contact info, instrument, and attendance stats.
- **Form Handling**: Includes a user-friendly form to add new members.

## Code Explanation

### HTML Structure
The system's HTML provides the main structure of the application. Key elements include:
- **Navigation Bar**: Links for switching between Login, Admin, and Member pages.
- **Table for Records**: Displays member data dynamically in a user-friendly layout.
- **Form for Adding Members**: Inputs for collecting user details such as name, email, and instrument.

### Backend and Database
While the front end showcases static records for demonstration, PHP scripts will handle dynamic interactions:

- **Login Authentication: Verify user credentials against stored data.
- **SQL Operations: Insert, update, and delete member, rehearsal, and instrument records.
- ** Attendance and Instrument Logs: Maintain comprehensive logs for administrative oversight.
