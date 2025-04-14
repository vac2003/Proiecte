<!DOCTYPE html>
<html lang="en">
    <head>
        <title>Informaciones sobre España</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="../css/w3.css">
        <link rel="stylesheet" href="../css/index.css">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    </head>

    <body>

        <!--Meniu-->
        <div class="w3-bar w3-red w3-card w3-left-align w3-large">
            <a class="w3-bar-item w3-button w3-hide-medium w3-hide-large w3-right w3-padding-large w3-hover-white w3-large w3-red" href="javascript:void(0);" onclick="myFunction()" title="Toggle Navigation Menu"><i class="fa fa-bars"></i></a>
            <a href="../index.php">
              <img src="../imagini/logo.png" class="w3-bar-item" height="50px" width="80px">
            </a>
            <a href="#" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Acasa</a>
          </div>
    </body>
</html>

<?php
session_start();

$nume_utilizator = $_POST["nume_utilizator"];
$email = $_POST["email"];
$parola = $_POST["parola_reg"];
$parola_hash = password_hash($parola, PASSWORD_BCRYPT);

// Adauga noul utilizator in tabela uilizatori, bd: bd_spania

$conexiune = mysqli_connect("localhost","root","","bd_spania");

// Verificam daca conexiunea a esuat.
if ($conexiune->connect_error) 
{
    die("Conexiune esuata! Nu s-a putut conecta la baza de date!: ".$conexiune->connect_error); // die termina script-ul precum un return 0;
}

$interogare = "INSERT INTO utilizatori(NumeUtilizator,Parola,Email,Rol) VALUES ('$nume_utilizator', '$parola_hash', '$email', 'user')";

// Se incearca adaugarea noului utilizator si afisarea unui mesaj corespunzator situatiei.
if ($conexiune->query($interogare) === TRUE)
{
    echo "Utilizatorul a fost inregistrat cu success!";
    include 'inregistrare_trimite_mail.php'; // Trimite mail cu detaliile contului.

    header("refresh:3; url=../index.php");
}
else
    echo "Eroare!".$conexiune->error;

$conexiune->close();

?>