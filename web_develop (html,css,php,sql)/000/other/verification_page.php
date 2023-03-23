<?php
	if(!isset($_GET['verify_email'])) header('Location: ../index.php');  //nie jesteś uprawniony,przekierowanie;
	
   //start variables and includes:
   mysqli_report(MYSQLI_REPORT_STRICT);
   $config_database = include $_SERVER['DOCUMENT_ROOT'].'/base/config_database.php';
   //====================================================================
   
    try
	{
		//connect to database:
		$db = mysqli_connect($config_database['server'],
		                     $config_database['username'],
							 $config_database['password'],
							 $config_database['database']); 
	    $db -> set_charset("utf8mb4"); 
		//==============================================================
		
		$token = $_GET['verify_email'];
		$results = mysqli_query($db,"SELECT id FROM users WHERE activation_code='$token'");
		if(mysqli_num_rows($results)<1)
		{
			mysqli_free_result($results);
			mysqli_close($db);
			header('Location: ../index.php');
			exit();
		}
		$row = mysqli_fetch_row($results);
		mysqli_free_result($results);
		$results = mysqli_query($db,"UPDATE users SET activation_code='activated' WHERE id='$row[0]'");
		mysqli_close($db);
	}
	catch(Exception $e)
	{
		echo $e->getMessage();
		exit();
	}

?>

<!DOCTYPE html>
<html>
	<head>
	</head>
	<body>
	<p>Konto zweryfikowane</p>
	<p>Możesz zalogować się teraz na swoje konto</p>
	<p><a href="../login_site.php">Logowanie</a></p>
	</body>
</html>