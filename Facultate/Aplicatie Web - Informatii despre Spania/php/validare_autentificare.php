<?php
session_start();

$conexiune = mysqli_connect("localhost","root","","bd_spania");

$email = mysqli_real_escape_string($conexiune, $_POST["email"]);
$parola = mysqli_real_escape_string($conexiune, $_POST["parola"]);

// Verificam daca conexiunea a esuat.
if ($conexiune->connect_error) 
{
    die("Conexiune esuata! Nu s-a putut conecta la baza de date!: ".$conexiune->connect_error); // die termina script-ul precum un return 0;
}

$interogare = "SELECT * FROM utilizatori WHERE Email = '$email'";
$rezultat = $conexiune->query($interogare);

if ($rezultat->num_rows == 1)
{
    $utilizator = $rezultat->fetch_assoc();

    $_SESSION['nume'] = $utilizator["NumeUtilizator"];
    $_SESSION['rol'] = $utilizator["Rol"];
    $_SESSION['este_logat'] = TRUE;

    header("refresh:2; url=../index.php");
    echo "Bine ai venit, ", $_SESSION['nume'], "!";
}
else
    echo "Email si/sau parola incorecte!";
?>