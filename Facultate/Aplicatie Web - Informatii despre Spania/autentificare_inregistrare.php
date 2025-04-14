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
        <!-- FONTURI -->
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
        <link href="https://fonts.googleapis.com/css2?family=Playwrite+ES+Deco+Guides&display=swap" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css2?family=Playwrite+ES+Deco+Guides&family=Sour+Gummy:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css2?family=Oswald:wght@200..700&display=swap" rel="stylesheet">
    </head>

    <body>

        <!--Meniu-->
        <div class="w3-bar w3-red w3-card w3-left-align w3-large">
            <a href="index.php">
              <img src="imagini/logo.png" class="w3-bar-item" height="50px" width="80px">
            </a>
            <a href="index.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Acasa</a>
            
            <a href="php/meniu_admin.php" class="w3-bar-item w3-button w3-padding-large w3-green w3-display-topright">Administrare</a>

        </div>

        <!--Div-uri pentru aranjarea formularului de autentificare, separatorul vertical si formularul de inregistrare-->
        <div class="container-autentificare-principal">
          <div class="container-autentificare-secundar font-sour-gummy">
            <h2 class="font-sour-gummy"><b>Ai deja un cont?</b></h2>
            <!--Formular AUTENTIFICARE-->
            <form action="php/validare_autentificare.php" method="POST">

              <!--Textbox pentru email-->
              <label align="left"><b>Email:</b></label>
              <input type="text" name="email" placeholder="Exemplu: mail@gmail.com" required>
    
              <!--Textbox pentru parola-->
              <label align="left"><b>Parola:</b></label>
              <input type="password" name="parola" placeholder="********" required>
    
              <div class="container-autentificare-secundar-buton">
                <fieldset>
                  <button type="submit">CONECTARE</button>
                  <button type="reset">RESETARE FORMULAR</button>
                </fieldset>
              </div>
            </form>
          </div>

          <div class="autentificare-linie-verticala">
            <label></label>
          </div>

          <div class="container-autentificare-secundar font-sour-gummy">
            <h2 class="font-sour-gummy"><b>Inregistrează-te!</b></h2>
            <!--Formular INREGISTRARE-->
            <form action="php/inregistrare.php" method="POST">

              <!--Textbox pentru nume de utilizator-->
              <label align="left"><b>Nume de utilizator:</b></label>
              <input type="text" name="nume_utilizator" placeholder="Exemplu: horia_tudor" required>

              <!--Textbox pentru email-->
              <label align="left"><b>Email:</b></label>
              <input type="text" name="email" placeholder="Exemplu: mail@gmail.com" required>
    
              <!--Textbox pentru parola-->
              <label align="left"><b>Parola:</b></label>
              <input type="password" id="parola" name="parola_reg" placeholder="********" onkeyup="confirmare_parola" required>

              <!--Textbox pentru confirmare parola-->
              <label align="left"><b>Confirmare Parola:</b></label>
              <input type="password" id="parola_confirmare" name="parola_confirmare_reg" placeholder="********" onkeyup="confirmare_parola" required>
    
              <fieldset>
                <button type="submit">ÎNREGISTRARE</button>
                <button type="reset">RESETARE FORMULAR</button>
              </fieldset>
            </form>
          </div>

      </div>

      <script type="text/javascript" src="js/validare_parola.js"></script>
    </body>
</html>