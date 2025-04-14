<?php
// Initializam sesiunea pentru a avea acces la variabilele globale (nume utilizator, email, rol).
session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
<title>Informaciones sobre España</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<!-- FISIERE CSS -->
<link rel="stylesheet" href="css/w3.css">
<link rel="stylesheet" href="css/index.css">
<link rel="stylesheet" href="css/carousel-index.css">
<link rel="stylesheet" href="css/sondaj.css">
<!-- FONTURI -->
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<link href="https://fonts.googleapis.com/css2?family=Playwrite+ES+Deco+Guides&display=swap" rel="stylesheet">
<link href="https://fonts.googleapis.com/css2?family=Playwrite+ES+Deco+Guides&family=Sour+Gummy:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
<link href="https://fonts.googleapis.com/css2?family=Oswald:wght@200..700&display=swap" rel="stylesheet">

<style>
body,h1,h2,h3,h4,h5,h6 {font-family: "Lato", sans-serif; z-index: 1}
.w3-bar,button {font-family: "Montserrat", sans-serif; position:sticky; top:0%; z-index:3}
.fa-anchor,.fa-coffee {font-size:200px}
</style>
</head>
<body>

<!-- Meniu -->
<div class="w3-bar w3-red w3-card w3-left-align w3-large">
  <a href="#">
    <img src="imagini/logo.png" class="w3-bar-item" height="50px" width="80px">
  </a>
  <a href="#" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Acasa</a>
  
  <?php if (isset($_SESSION['este_logat']) && $_SESSION['este_logat'] === TRUE && $_SESSION['rol'] == 'administrator'): ?>
    <a class="w3-bar-item w3-hide-small w3-padding-large">Bine ai venit, <?php echo $_SESSION['nume'] ?>!</a>
    <a href="php/deconectare_utilizator.php" class="w3-bar-item w3-button w3-padding-large w3-green w3-display-topright" style="right:200px">Deconectare</a>
    <a href="php/meniu_admin.php" class="w3-bar-item w3-button w3-padding-large w3-green w3-display-topright">Administrare</a>
  <?php elseif (isset($_SESSION['este_logat']) && $_SESSION['este_logat'] === TRUE && $_SESSION['rol'] == 'user'): ?>
    <a class="w3-bar-item w3-hide-small w3-padding-large">Bine ai venit, <?php echo $_SESSION['nume'] ?>!</a>
    <a href="php/deconectare_utilizator.php" class="w3-bar-item w3-button w3-padding-large w3-green w3-display-topright" style="right:200px">Deconectare</a>
  <?php else: ?>
    <a href="autentificare_inregistrare.php" class="w3-bar-item w3-button w3-padding-large w3-white w3-display-topright">Autentificare</a>
  <?php endif; ?>
</div>

<!-- Introducere -->
<div class="banner-container">
    <div class="introducere-container">
        <div class="introducere-container-1">
            <h1 align="center" class="font-oswald">Despre Spania</h1>
            <p class="text-introducere font-playwrite-regular background-rosu"><b>Spania</b>, situată în Peninsula Iberică din sud-vestul Europei, este o țară captivantă, cunoscută pentru istoria sa bogată, peisajele uimitoare și cultura dinamică. De la plajele mediteraneene însorite până la vârfurile înzăpezite ale Pirineilor, Spania oferă o geografie diversă care încântă orice călător.</p>
            <p class="text-introducere font-playwrite-regular background-galben">Cu un trecut fascinant, Spania a fost modelată de influențe romane, maure și creștine, evidente în arhitectura sa iconică, cum ar fi Alhambra din Granada, Sagrada Familia din Barcelona și străzile medievale din Toledo.</p>
            <p class="text-introducere font-playwrite-regular background-rosu">Cultura vibrantă a Spaniei este poate cel mai bine simbolizată de pasiunea sa pentru muzică, dans și sărbători. Ritmurile flamenco, festivalurile pline de viață, precum La Tomatina și San Fermín, și bucătăria de renume mondial - cu tapas, paella și vinuri gustoase - creează o experiență de neuitat pentru vizitatori.</p>
        </div>
    </div>
</div>

<!-- CAROUSEL PENTRU PLAJE -->
<?php include "php/afisare_slide_plaje.php"; ?>
<!-- CAROUSEL PENTRU TRADITII -->
<?php include "php/afisare_slide_traditii.php"; ?>

<hr style="height:2px; background-color:tomato">

<!-- FORMULAR SONDAJ -->
<div class="container-principal-sondaj">
          <div class="sondaj font-sour-gummy">

            <h2 class="font-sour-gummy"><b>Ți-ai făcut o opinie despre site? Spune-ne și nouă!</b></h2>


            <form action="php/adauga_opinie.php" method="POST">

              <!--Textbox pentru nume-->
              <label align="left"><b>Nume:</b></label>
              <input type="text" name="nume">
    
              <!--Textbox pentru prenume-->
              <label align="left"><b>Prenume:</b></label>
              <input type="text" name="prenume">

              <!--Textbox pentru email-->
              <label align="left"><b>Email:</b></label>
              <input type="text" name="email" required>

              <!--Textbox pentru opinie-->
              <label align="left"><b>Opinie:</b></label>
              <textarea type="text" name="opinie" rows="8" cols="50" required></textarea>
    
              <div class="sondaj-buton">
                <fieldset>
                  <button type="submit">TRIMITERE RĂSPUNS</button>
                  <button type="reset">RESETARE FORMULAR</button>
                </fieldset>
              </div>
            </form>

          </div>
</div>
<hr style="height:2px; background-color:tomato">
<!-- FUN FACTS! -->
<div class="container-principal font-sour-gummy">
  <h1 class="font-sour-gummy"><b>Stiai ca?</b></h1>

  <dl style="font-size: 20px;">

  <dt style="font-weight: 400;">Spaniola este a doua cea mai vorbită limbă maternă din lume?</dt>
  <dd>- Peste 460 de milioane de oameni din întreaga lume vorbesc spaniola ca limbă maternă, făcând-o una dintre cele mai vorbite limbi la nivel global.</dd>

  <dt style="font-weight: 400;">Găzduiește cel mai vechi restaurant din lume?</dt>
  <dd>- „Restaurante Botín” din Madrid, deschis în 1725, deține recordul Guinness pentru cel mai vechi restaurant din lume care funcționează fără întrerupere.</dd>

  <dt style="font-weight: 400;">Spania produce foarte mult ulei de măsline?</dt>
  <dd>- Spania este cel mai mare producător de ulei de măsline din lume, reprezentând aproape 50% din producția globală. Andaluzia este inima acestei industrii.</dd>

  <dt style="font-weight: 400;">Spania este a doua cea mai muntoasă țară din Europa?</dt>
  <dd>- După Elveția, Spania are cel mai muntos relief din Europa, cu lanțuri muntoase precum Pirineii, Sierra Nevada și Picos de Europa, care oferă priveliști uimitoare.</dd>

  <dt style="font-weight: 400;">Spania a fost prima țară care a colonizat Americile?</dt>
  <dd>- Călătoria lui Cristofor Columb din 1492, finanțată de Spania, a marcat începutul explorării și colonizării europene a Americilor.</dd>

  <dt style="font-weight: 400;">Catedrala „Sagrada Familia” nu este încă terminată?</dt>
  <dd>- Construcția catedralei Sagrada Familia din Barcelona, proiectată de Antoni Gaudí, a început în 1882 și este programată să fie finalizată în 2026.</dd>

  <dt style="font-weight: 400;">Spania este lider în turismul global?</dt>
  <dd>- Cu peste 80 de milioane de vizitatori anual, Spania este una dintre cele mai vizitate țări din lume, datorită diversității sale culturale și peisagistice.</dd>
</dl>
</div>

<!-- Footer -->
<footer class="w3-container w3-padding-64 w3-center w3-opacity">  
  <div class="w3-xlarge w3-padding-32">
    <i class="fa fa-facebook-official w3-hover-opacity"></i>
    <i class="fa fa-instagram w3-hover-opacity"></i>
    <i class="fa fa-snapchat w3-hover-opacity"></i>
    <i class="fa fa-pinterest-p w3-hover-opacity"></i>
    <i class="fa fa-twitter w3-hover-opacity"></i>
    <i class="fa fa-linkedin w3-hover-opacity"></i>
 </div>
</footer>

<script type="text/javascript" src="js/carousel.js"></script>

</body>
</html>