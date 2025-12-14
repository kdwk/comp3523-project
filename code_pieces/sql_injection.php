<?php
// Database connection settings
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "test_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

function getUserData($username) {
    global $conn;

    $sql = "SELECT * FROM users WHERE username = $username";
    
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            echo "Username: " . $row["username"] . " - Email: " . $row["email"] . "<br>";
        }
    } else {
        echo "No user found.<br>";
    }
}

$userInput = $_GET['username'] ?? '';

getUserData($userInput);

$conn->close();
?>