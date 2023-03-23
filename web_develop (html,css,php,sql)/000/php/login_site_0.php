<?php
   //jesli uzytkownik nie wypelnil formularza to go przenies do:
   if(!isset($_POST["submit"]))  header('Location: ../login_site.php');
   //====================================================================
   
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
		
		
	   //konwersja znaków dodana przez wzgląd na kompatybilność z danymi które użytkownik podał w momencie rejestracji
	   $login = stripslashes($_POST['login']);                           //usuwa znaki '//' i przekształca je na '/'
	   $login = htmlentities($login, ENT_QUOTES | ENT_IGNORE, "UTF-8");  //html'owe encje przekształca na inne znaki by owe encje nie zostały zinterpretowane przez html'a jako kod;
	   $login = mysqli_real_escape_string($db,$login);                   //dodaje lewe ukośniki do tych znaków: NUL (ASCII 0), \n, \r, \, ', ", and Control-Z  żeby zabezpieczyć baze dane;
	   $password = stripslashes($_POST['password']);
	   //===============================================================
	   
	   $results = mysqli_query($db,"SELECT password,activation_code,id FROM users WHERE username='$login' OR email='$login'");
	   if(mysqli_num_rows($results)<1)
	   {
		    mysqli_free_result($results);   //zwalnianie pamieci z obiektu mysqli_result (bo ten obiekt nie zwalnia automatycznie pamieci i po stronie serwera niepotrzebnie by ram był zajety);
	        mysqli_close($db);             //zamykanie połączenia z bazą (ponowne połączenie z bazą gdy nie jest ona zamknieta może spowodować błędy);
			$_SESSION["error"] = "Niepoprawny login lub hasło";   //niepoprawny login;
			header('Location: ../login_site.php');
			exit();                          //musi być tutaj exit bo funkcja header zachowuje sie dziwnie jak nie ma exit po niej (czytałem na forum że różnie bywa);
	   }
	   $row = mysqli_fetch_assoc($results);
	   if (!password_verify($password,$row['password']))
	   {
		    mysqli_free_result($results);
	        mysqli_close($db);
			$_SESSION["error"] = "Niepoprawny login lub hasło";   //niepoprawne hasło;
			header('Location: ../login_site.php');
			exit();
	   }
	   if($row['activation_code']!='activated')
	   {
		    mysqli_free_result($results);
	        mysqli_close($db);
			$_SESSION["error"] = "link weryfikacyjny został wysłany na podany email";   //nieaktywowane konto;
			header('Location: ../index.php');
			exit();
	   }
	   mysqli_free_result($results);
	   if(isset($_POST['checkbox']))                               //wykonywanie działań jeśli checkbox jest zaznaczony
	   {
		   $remember_me_main = $row['id'].'U'.bin2hex(random_bytes(20));          //generowanie losowego klucza (dodanie id by szybciej mozna było przechwycić klucz przy porównywaniu);
		   $results = mysqli_query($db,"UPDATE users SET remember_me = '".$remember_me_main."' WHERE username='$login' OR email='$login'"); //wstawianie klucza do bazy danych użytkownika
		   setcookie("remember_me",$remember_me_main,time()+3600*24*30*12*15,'/');                   //wstawianie klucza jako ciasteczko by móc porównać klucz przechowywany w bazie danych;
	   }
	   else mysqli_query($db,"UPDATE users SET remember_me = '0' WHERE username='$login' OR email='$login'");   //w przeciwnym wypadku wstaw do "remember_me" 0;
	   $results = mysqli_query($db,"SELECT * FROM users WHERE username='$login' OR email='$login'");
	   $_SESSION = mysqli_fetch_assoc($results);                                                      //PRZYPISANIE WSZYSTKICH DANYCH UŻYTKOWNIKA DO POJEMNIKA $_SESSION
	   session_regenerate_id();                  //niszczenie identyfikatora sesji i stworzenie nowego (zapobiega próbom przechwycenia klucza,warto dodać to po "zalogowaniu sie")
	   unset($_SESSION['password']);
	   unset($_SESSION['remember_me']); 
	   mysqli_free_result($results);             
	   mysqli_close($db);
	   
	   header('Location: ../index.php');                //TUTAJ PRZEKIEROWANIE PO UDANYM LOGOWANIU;
	   exit();
	}
	catch(Exception $e)
	{
		echo $e->getMessage();
		exit();
	}
	//======================================================================
	
   

    



?>

