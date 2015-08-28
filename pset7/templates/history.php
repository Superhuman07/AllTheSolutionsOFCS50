<table class="table table-striped-2">

    <thead>
        <tr>
            <th>Transaction</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>
    <?php
	    foreach ($history as $row)	
        {   
            echo("<tr>");
            echo("<td>" . $row["Tran"] . "</td>");
            echo("<td>" . $row["Date/Time"] . "</td>");
            echo("<td>" . $row["Symbol"] . "</td>");
	    echo("<td>" . $row["Shares"] . "</td>");
            echo("<td>$" . number_format($row["Price"], 2) . "</td>");
            echo("<td>$" . number_format($row["Total"], 2) . "</td>");
            echo("</tr>");
        }
    ?>

    <tr>
        <td colspan="4">CASH</td>
        <td>$<?=number_format($users[0]["cash"], 2)?></td>
    </tr>

    </tbody>

</table>
