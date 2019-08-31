<?php
// Name: hereDoc.php - (Example 3.4)
// Author: Cody R. Drisko (crdrisko)
// Date: 08/29/2019-08:31:51
// Description:
// Website: http://localhost:8003/hereDoc.php
?>

<?php
$website = "http://www.romatermini.it";
echo <<<EXCERPT
<p>Rome's central train station, known as <a href = "$website">Roma Termini</a>, 
was built in 1867. Because it had fallen into severe disrepair in the late 20th century, 
the government knew that considerable resources were required to rehabilitate the station 
prior to the 50-year <i>Giubileo</i>.</p>
EXCERPT;
?>