<?php
// Name: superGlobal.php
// Author: Cody R. Drisko (crdrisko)
// Date: 07/23/2019-20:14:27
// Description: Demonstrating the use of PHP's Superglobal Variables
// Website: http://localhost:8003/superGlobal.php
?>

<?php
    foreach ($_SERVER as $var => $value) {
        echo "$var => $value <br />";
    }
?>
