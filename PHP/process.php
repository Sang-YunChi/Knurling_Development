<?php 
header("Content-Type: text/html;charset=UTF-8"); 
$host = 'localhost'; 
$user = 'root'; 
$pw = 'apmsetup'; 
$dbName = 'test_new'; 
$mysqli = new mysqli($host, $user, $pw, $dbName); 
    if($mysqli){ 
        echo "MySQL successfully connected!<br/>"; 
        $rfid = $_GET['rfid']; 
        $name = $_GET['name'];
        $count = $_GET['count'];
        $weight = $_GET['weight'];
        echo "<br/>RFID = $rfid"; 
        echo ", "; 
        echo "name = $name<br/>";
        echo ", "; 
        echo "count = $count<br/>"; 
        echo ", "; 
        echo "weight = $weight<br/>"; 
        $query = "INSERT INTO test_table2 (rfid, name, count, weight) VALUES ('$rfid','$name','$count','$weight')"; 
        mysqli_query($mysqli,$query); 
        
        echo "</br>success!!"; } 
        
    else{ echo "MySQL could not be connected"; } 
    
mysqli_close($mysqli); 
?>
//
rfid varchar (primary key)
name varchar
count int
weight int
//
