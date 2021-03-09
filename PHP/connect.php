<?php


$conn = mysqli_connect("localhost","root","apmsetup","test_new");
if (mysqli_connect_errno()){
    echo 'connect failed!<br>reason :'  . mysqli_connect_error();
}

$result = mysqli_query($conn,'SELECT * FROM test_table2 ORDER BY count DESC limit 1');
echo '<table border="1"> <tr> <th>rfid</th> <th>name</th> <th>count</th> <th>weight</th> </tr>';
$n = 1;
while($row = mysqli_fetch_array($result)){
    echo '<tr>';
    echo '<td>' . $row["rfid"] . '</td>';
    echo '<td>' . $row["name"] . '</td>';
    echo '<td>' . $row["count"] . '</td>';
    echo '<td>' . $row["weight"] . '</td>';
    echo '</tr>';
    $n++;
}
echo "</table>";
mysqli_close($conn);

?>
