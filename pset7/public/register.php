<?php 

	//configuration 
	require("../includes/config.php");

	//if user reached page via GET ( as by clicking a link or via redirect)
	if ($_SERVER["REQUEST_METHOD"] == "GET")
	{
		//else render form 
		render("register_form.php", ["title" => "register"]);
	}

	//else if user reached page via POST (as by submitting a form via POST)
	else if ($_SERVER["REQUEST_METHOD"] == "POST")
	{
		if (empty($_POST["username"]))
		{
			apologize("Please enter the username");	
		}
		else if (empty($_POST["password"]))
		{
			apologize("Please enter the password");	
		}
		else if (($_POST["password"]) != ($_POST["confirmation"]))
		{
			apologize("Passwords don't match");	
		}
	if (!empty(($_POST["username"])))
	{
		query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
	
		if (query !== false)
		{
			$rows = query("SELECT LAST_INSERT_ID() AS id");
			$id = $rows[0]["id"];
			$_SESSION["id"];
			redirect("index.php");
		}
		
		
	}
}

?>
