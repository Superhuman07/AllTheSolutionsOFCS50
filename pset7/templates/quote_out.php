<?php
if (($stock) !== false)
	{
		print("Price of symbol ".$_POST["symbol"]." is ". "$". number_format($stock["price"], 2,'.', ''));
	}
	else
	{
		apologize("Please enter the correct symbol");
	}
?>
