<?php

include "clasa_plaje.php";

function get_vector_plaje($rez)
{
  $pj = array();
  while ($data = $rez->fetch_assoc())
  {
    $plaja = new Plaja($data["ID"], $data["Denumire"], $data["CaleImagine"]);
    $pj[] = $plaja;
  }
  return $pj;
}

$conexiune = mysqli_connect('localhost','root','','bd_spania');

// Verificam daca conexiunea a esuat.
if ($conexiune->connect_error) 
{
    die('Conexiune esuata! Nu s-a putut conecta la baza de date!: '.$conexiune->connect_error); // die termina script-ul precum un return 0;
}

$interogare = 'SELECT * FROM plaje';
$rezultat = $conexiune->query($interogare);

echo
"
<div class='w3-row-padding w3-padding-64 w3-container w3-border-top w3-border-bottom'>
  <div class='w3-content background-plaja'>
    <h1 align='center' class='font-oswald background-header-plaja'>Plaje</h1>
    <div class='slideshow-container'>
";

$plaje = get_vector_plaje($rezultat);

foreach ($plaje as $p)
{
  $p->afisare_slide_plaje();
}

echo
"
<!-- Butoanele de redare -->
    <a class='prev' onclick='plusSlides(-1, 0)'>&#10094;</a>
    <a class='next' onclick='plusSlides(1, 0)'>&#10095;</a>
  </div>

  <br>

  <!-- DE REPARAT The dots/circles DE REPARAT
  <div style='text-align:center'>
    <span class='dot' onclick='currentSlide(1, 0)'></span>
    <span class='dot' onclick='currentSlide(2, 0)'></span>
    <span class='dot' onclick='currentSlide(3, 0)'></span>
  </div> -->
  
</div>
";

?>