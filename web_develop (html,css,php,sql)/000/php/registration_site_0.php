<?php
   //jesli uzytkownik nie wypelnil formularza to go przenies do:
   if(!isset($_POST["submit"]))  header('Location: ../login_site.php');
   //====================================================================
   
   
   //start variables and includes:
   session_start();
   mysqli_report(MYSQLI_REPORT_STRICT);
   $config_database = include $_SERVER['DOCUMENT_ROOT'].'/base/config_database.php';
   //====================================================================
   
   
   //kontrola błędów i walidacja danych;
   //dane używane później;
   $user_date = $_POST['Rok_urodzenia'].'-'.$_POST['Miesiac_urodzenia'].'-'.$_POST['Dzien_urodzenia'];  //sformatowana data urodzenia użytkownika;
   $user_name = $_POST['Nazwa_uzytkownika'];
   $user_password = $_POST['password'];
   $user_email = $_POST['Email']; 
   if (!filter_var($user_email, FILTER_VALIDATE_EMAIL))                 //to tak na wszelki wypadek (wiem ze w html'u już zaszała walidacja prawdopodobnie;
   {
		$_SESSION["error"] = "Niepoprawny adres email";
		header('Location: ../index.php');
		exit();
   }
   
   //============================================================================
   $date_check = strtotime($user_date);
    
   if(time()<strtotime('+18 years',$date_check))                                 //sprawdzanie wieku
   {
	    if($_POST['Plec']==1) $_SESSION["error"] = "Jesteś zbyt młody by się móc zarejestrować";
		else $_SESSION["error"] = "Jesteś zbyt młoda by się móc zarejestrować";
	   	header('Location: ../index.php');
		exit();
	   
	   
   }
   if(!preg_match('/^\w{5,}$/',$user_name)) //skopiowane z neta bo nie chciałem tracić czasu; wzór na walidacje (czy przechodzi czy nie);
	{
	    $_SESSION["error"] = "Nazwa użytkownika nie może posiadać: <br/>- znaków specjalnych (w tym polskich liter) <br/>- musi mieć przynajmniej długości 5-ciu znaków<br/>";
	}
   if($user_password!=$_POST['password_confirm'])            //sprawdzanie czy oba hasła są takie same
   {
	   	if(isset($_SESSION["error"])) $_SESSION["error"] .= "<br/>Wpisane hasła różnią się od siebie";
		else $_SESSION["error"] = "Wpisane hasła różnią się od siebie";
		header('Location: ../index.php');
		exit();
   }
   if (!preg_match("#.*^(?=.{8,})(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*\W).*$#",$user_password)) //tez skopiowane z neta
   {
	    if(isset($_SESSION["error"])) $_SESSION["error"] .= "<br/>Hasło musi posiadać przynajmniej: <br/>- 8 znaków w tym jedną dużą litere/
		<br/>jeden znak specjalny/<br/>jedną małą litere/<br/>jedną liczbę";
		else $_SESSION["error"] = "Hasło musi posiadać przynajmniej: <br/>- 8 znaków w tym jedną dużą litere/
		<br/>jeden znak specjalny/<br/>jedną małą litere/<br/>jedną liczbę";
		header('Location: ../index.php');
		exit();
   }
   if(isset($_SESSION["error"]))
   {
	   	header('Location: ../index.php');
		exit();
   }
   //=====================================================================
   
    try
	{
		//connect to database:
		$db = mysqli_connect($config_database['server'],
		                     $config_database['username'],
							 $config_database['password'],
							 $config_database['database']); 
	    $db -> set_charset("utf8mb4");
		//=====================================================
		
       //konwersja znaków
	   $user_name = stripslashes($user_name);                           //usuwa znaki '//' i przekształca je na '/'
	   $user_name = htmlentities($user_name, ENT_QUOTES | ENT_IGNORE, "UTF-8");  //html'owe encje przekształca na inne znaki by owe encje nie zostały zinterpretowane przez html'a jako kod;
	   $user_name = mysqli_real_escape_string($db,$user_name);                   //dodaje lewe ukośniki do tych znaków: NUL (ASCII 0), \n, \r, \, ', ", and Control-Z  żeby zabezpieczyć baze dane;
	   $user_password = stripslashes($user_password);
	   //===============================================================
	   
	   //sprawdzanie czy username i email są już w bazie danych
	   $results = mysqli_query($db,"SELECT id FROM users WHERE username='$user_name'");
	   if(mysqli_num_rows($results)>0)
	   {
		    mysqli_free_result($results);
	        mysqli_close($db);
			$_SESSION["error"] = "Użytkownik o takiej nazwie już istnieje";
			header('Location: ../index.php');
			exit();
	   }
	   mysqli_free_result($results);
	   $results = mysqli_query($db,"SELECT id FROM users WHERE email='$user_email'");
	   if(mysqli_num_rows($results)>0)
	   {
		   	mysqli_free_result($results);
	        mysqli_close($db);
			$_SESSION["error"] = "Konto zostało już zarejestrowane na ten adres email";
			header('Location: ../index.php');
			exit();
	   }
	   mysqli_free_result($results);
	   //===============================================================
	   
	   //dodawanie użytkownika do bazy danych
	   $user_password = password_hash($user_password,PASSWORD_DEFAULT);
	   $adress_ip = $_SERVER['REMOTE_ADDR'];
	   $actual_date = date('Y-m-d H:i:s');
	   $user_gender = $_POST['Plec'];
	   $activation_key = bin2hex(random_bytes(30));
	   $results = mysqli_query($db,"INSERT INTO users VALUES (NULL,'$user_name','$user_email','$user_password','$adress_ip',
	   '$actual_date',0,0,'sciezka_do_pliku/image/image.webp','',0,'$user_gender','$user_date',100,0,0,'$actual_date',0,'','','','$activation_key',0,0,'no')");
	   if($results!=1)
	   {
		   	mysqli_free_result($results);
	        mysqli_close($db);
			$_SESSION["error"] = "Nieznany problem";
			header('Location: ../index.php');
			exit();
	   }
	   //================================================================
	   
	   //wysłanie maila z kluczem
		$subject  = 'Prośba o weryfikacje email\'a';
		$message  = '
			<html>
			<head>
			<title>Verify your email</title>
			</head>
			<body>
			<p>Po udanej rejestracji na stronie: <b>lodgeofdesire.com</b></p>
			<p>zweryfikuj swój email: <b>'.$user_email.'</b> klikając w link:
			<a href="http://localhost/other/verification_page.php?verify_email='.$activation_key.'">Verify email</a>
			</body>
			</html>
			';
		
		$headers  = "Reply-To: Name <name@example.com>"."\r\n";
		$headers .= "Return-Path: Name <name@example.com>"."\r\n";
		$headers .= "From: Name <name@example.com>"."\r\n";
		$headers .= "MIME-Version: 1.0"."\r\n";
		$headers .= "Content-type: text/html; charset=utf8"."\r\n";
		$headers .= "X-Priority: 3"."\r\n";
		$headers .= "X-Mailer: PHP".phpversion();


		mail($user_email, $subject, $message, $headers);
	   
	   //================================================================
	   
	   mysqli_close($db);
	   header('Location: ../other/registration_successfully.php');
	   exit();
	}
	catch(Exception $e)
	{
		echo $e->getMessage();
		exit();
	}

?>