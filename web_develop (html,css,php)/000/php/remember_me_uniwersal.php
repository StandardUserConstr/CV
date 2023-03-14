<?php
   
   if(!isset($_COOKIE['remember_me'])) header('Location: ../index.php'); //nie jesteś uprawniony,przekierowanie;
   
   //start variables and includes:
   session_start();
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
		
		$user_id = strstr($_COOKIE['remember_me'],'U',1);
		if(!is_numeric($user_id))
		{
			setcookie("remember_me","",time()-1,'/');   
			header('Location: ../index.php');
		}
		$results = mysqli_query($db,"SELECT remember_me FROM users WHERE id=$user_id");
		if(mysqli_num_rows($results)<1)
		{
			mysqli_free_result($results);
			mysqli_close($db);
			setcookie("remember_me","",time()-1,'/');
			header('Location: ../index.php');
		}
		$row = mysqli_fetch_assoc($results);
		mysqli_free_result($results);
		if($row['remember_me']!=$_COOKIE['remember_me'])
		{
			mysqli_free_result($results);
			mysqli_close($db);
			setcookie("remember_me","",time()-1,'/');
			header('Location: ../index.php');
		}
		$results = mysqli_query($db,"SELECT * FROM users WHERE id=$user_id");
		$_SESSION = mysqli_fetch_assoc($results);
		session_regenerate_id();
	    unset($_SESSION['password']);
	    unset($_SESSION['remember_me']);
		mysqli_free_result($results);
		
		header('Location: ../cookie.php')
		exit();
	}
	catch(Exception $e)
	{
		echo $e->getMessage();
		exit();
	}
?>