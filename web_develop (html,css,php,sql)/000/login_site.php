<?php
	session_start();
	//przekierowanie do innej strony jeśli użytkownik jest zalogowany
	if(isset($_SESSION['id'])) header('Location: index.php');
	else if(isset($_COOKIE['remember_me'])) include "php/remember_me_uniwersal.php" ;  //w środku mechanizm sprawdzający klucz ciastka i przekierowywujący na daną strone; 
	//===================================================================

?>
<!DOCTYPE html>
<html lang="pl">
	<head>
		<link rel="stylesheet" href="css/login_site_0.css">
	</head>
		<body>
			<form method="post" action="php/login_site_0.php">
			    <div class="write_area">
					<label>Login/Email:</label>
					<input type="text" name="login" placeholder="login" required />
				</div>
				<div class="write_area">
				    <label>Password:</label>
					<input type="password" name="password" placeholder="password" required />
				</div>
				<input type="checkbox" name="checkbox" id="remember_me"> <label>Zapamiętaj mnie</label> </input>
							 
				 
                 
				<div id="button_submit">
					<input type="submit" name="submit" value="Login" />
                </div>
				<?php
					if(isset($_SESSION["error"]))                                     //KONTROLA WPISANIA NIEPOPRAWNYCH DANYCH
					{
						echo '<div id="error">'.$_SESSION["error"].'</div>';
						session_destroy();
					}
				?>
			</form>
		</body>
</html>