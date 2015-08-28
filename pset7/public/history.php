<?php
require("../includes/config.php"); 

    // query user's portfolio
    $rows =	query("SELECT * FROM trans WHERE id = ?", $_SESSION["id"]);	
	// create new array to store all info for portfolio table
	$history = [];
	// for each of user's stocks
	foreach ($rows as $row)	
    {   
        // lookup stock info at row
        $status["Tran"] = $row["Tran"];
 	$status["Date/Time"] = $row["Date/Time"];
        
        // add shares to the row
        $status["Shares"] = $row["Shares"];
        
        // add total price to the row
        $status["Symbol"] = $row["Symbol"];
        $status["Price"] = $row["Price"];
	$status["Total"] = $row["Price"] * $row["Shares"];
        // save the row in the new array
        $history[] = $status;
    }
    
    // query cash for template
    $users = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    // render portfolio (pass in new portfolio table and cash)
    render("history.php", ["title" => "History", "history"=> $history, "users" => $users]);

?>
