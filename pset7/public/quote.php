<?php
require("../includes/config.php"); 
if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_in.php", ["title" => "Quote"]);
    }
 else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
      
	$stock = lookup($_POST["symbol"]);
	render("quote_out.php", ["stock" => $stock, "title" => "Quote"]);
}
?>
