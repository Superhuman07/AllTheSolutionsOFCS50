<?php
    // configuration
    require("../includes/config.php"); 
	
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
	// validate submission
	if (empty($_POST["password"]))
	{
		apologize("Enter a new password");
	}
	else if (empty($_POST["confirmation"]))
	{
		apologize("Enter password confirmation");
	}
	else if($_POST["password"] != $_POST["confirmation"])
	{
		apologize("Passwords are not equal! Try again!");
	}
	// create new encrypted password
	$hash = crypt($_POST["password"]);
	$id = $_SESSION["id"];
			
	// update the account to the new password
	query("UPDATE users SET hash='$hash' WHERE id=$id"); 
			render("changed.php");
     }
	else
	{
		render("change_password.php", ["title" => "Password"]);
	}
?>
