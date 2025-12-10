<?php
// Database connection settings
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "test_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Function to get user data based on the provided username
function getUserData($username) {
    global $conn;

    // Construct the SQL query without sanitization
    $sql = $conn->prepare("SELECT * FROM users WHERE username = '?'");
    $sql->bind_param("s", $username);
    
    // Execute the query
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        // Output data of each row
        while ($row = $result->fetch_assoc()) {
            echo "Username: " . $row["username"] . " - Email: " . $row["email"] . "<br>";
        }
    } else {
        echo "No user found.<br>";
    }
}

// Simulating user input (could be from a form)
$userInput = $_GET['username'] ?? '';

// Calling the function with unsanitized input
getUserData($userInput);

// Closing the connection
$conn->close();
?>