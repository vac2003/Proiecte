<?php

include "clasa_traditie.php";

function get_vector_traditii($rez)
{
  $tr = array();
  while ($data = $rez->fetch_assoc())
  {
    $traditie = new Traditie($data["ID"], $data["Denumire"], $data["CaleImagine"]);
    $tr[] = $traditie;
  }
  return $tr;
}

$conexiune = mysqli_connect('localhost','root','','bd_spania');

// Verificam daca conexiunea a esuat.
if ($conexiune->connect_error) 
{
    die('Conexiune esuata! Nu s-a putut conecta la baza de date!: '.$conexiune->connect_error); // die termina script-ul precum un return 0;
}

$interogare = 'SELECT * FROM traditii';
$rezultat = $conexiune->query($interogare);

echo
"
<div class='w3-row-padding w3-padding-64 w3-container w3-border-top w3-border-bottom'>
  <div class='w3-content'>
    <h1 align='center' class='font-oswald background-header-plaja'>Traditii</h1>
    <div class='slideshow-container'>
";

$traditii = get_vector_traditii($rezultat);

foreach ($traditii as $t)
{
  $t->afisare_slide_traditie();
}

echo
"
<!-- Butoanele de redare -->
    <a class='prev' onclick='plusSlides(-1, 1)'>&#10094;</a>
    <a class='next' onclick='plusSlides(1, 1)'>&#10095;</a>
  </div>

  <br>

  <!-- DE REPARAT The dots/circles DE REPARAT
  <div style='text-align:center'>
    <span class='dot' onclick='currentSlide(1, 1)'></span>
    <span class='dot' onclick='currentSlide(2, 1)'></span>
    <span class='dot' onclick='currentSlide(3, 1)'></span>
  </div> -->
</div>
";

?>