<?php
// Name: amortize.php - (Example 4-1)
// Author: Cody R. Drisko (crdrisko)
// Date: 09/01/2019-12:26:42
// Description:
// Website: http://localhost:8004/amortize.php
?>

<?php
// The Payment Calculator Function amortizationTable() - (Listing 4-1)
function amortizationTable($paymentNumber, $periodicPayment, $balance, $monthlyInterest)
{
	static $table = array();

	// Calculate payment interest
	$paymentInterest = round($balance * $monthlyInterest, 2);

	// Calculate payment principal
	$paymentPrincipal = round($periodicPayment - $paymentInterest, 2);

	// Deduct principal from remaining balance
	$newBalance = round($balance - $paymentPrincipal, 2);

	// If new balance < monthly payment, set to zero 
	if ($newBalance < $paymentPrincipal) {
		$newBalance = 0;
	}
	$table[] = [ $paymentNumber,
	  number_format($newBalance, 2),
	  number_format($periodicPayment, 2),
	  number_format($paymentPrincipal, 2),
	  number_format($paymentInterest, 2) ];
	
	  // If balance not yet zero, recursively call amortizationTable()
	  if ($newBalance > 0) {
		$paymentNumber++;
		amortizationTable($paymentNumber, $periodicPayment, $newBalance, $monthlyInterest);
	  }

	  return $table;
}

// A Payment Schedule Calculator Using Recurion - (Listing 4-2)
$balance = 10000.00; 															// Loan balance

$interestRate = .0575; 															// Loan interest rate

$monthlyInterest = $interestRate / 12; 											// Monthly interest rate

$termLength = 5; 																// Term length of the loan, in years

$paymentsPerYear = 12; 															// Number of payments per year

$paymentNumber = 1; 															// Pay iteration

$totalPayments = $termLength * $paymentsPerYear; 								// Determine total number of payments

$intCalc = 1 + $interestRate / $paymentsPerYear; 								// Determine interest component of periodic payment

$periodicPayment = $balance * pow($intCalc, $totalPayments) * ($intCalc - 1)  	// Determine periodic payment
	/ (pow($intCalc, $totalPayments) - 1);

$periodicPayment = round($periodicPayment, 2); 									// Round periodic payment to two decimals

$rows = amortizationTable($paymentNumber, $periodicPayment, $balance, $monthlyInterest);

echo "<table>"; 																// Create table
echo "<tr>
  <th>Payment Number</th><th>Loan Balance</th><th>Payment</th><th>Principal</th><th>Interest</th>
</tr>";

foreach($rows as $row) {
	printf("<tr><td>%d</td>", $row[0]);
	printf("<td>%s</td>", $row[1]);
	printf("<td>%s</td>", $row[2]);
	printf("<td>%s</td>", $row[3]);
	printf("<td>%s</td></tr>", $row[4]);
}

echo "</table>"; 																// Close table
?>