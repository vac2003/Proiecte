<?php

$id = $_POST["id"];

$conexiune = mysqli_connect("localhost","root","","bd_spania");

// Verificam daca conexiunea a esuat.
if ($conexiune->connect_error) 
{
    die("Conexiune esuata! Nu s-a putut conecta la baza de date!: ".$conexiune->connect_error); // die termina script-ul precum un return 0;
}

$interogare = "DELETE FROM utilizatori WHERE ID='$id'";

// Se incearca stergerea utilizatorului si afisarea unui mesaj corespunzator situatiei.
if ($conexiune->query($interogare) === TRUE)
{
    echo "Utilizatorul a fost sters cu success!";

    header("refresh:3; url=../index.php");
}
else
    echo "Eroare!".$conexiune->error;

$conexiune->close();

?>