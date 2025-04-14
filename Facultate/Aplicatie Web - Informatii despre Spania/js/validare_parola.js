var parola = document.getElementById("parola");
var parola_conf = document.getElementById("parola_confirmare");

// La apasarea butonului INREGISTRARE in "autentificare_inregistrare.html" nu se va executa scriptul "inregistrare.php" daca parolele nu coincid.
// PS: functia este getElementById nu Elements.
function validare_parola(){
    if(parola.value != parola_conf.value) {
      parola_conf.setCustomValidity("Parolele nu coincid!");
    } else {
      parola_conf.setCustomValidity('');
    }
  }
  
  parola.onkeyup = validare_parola;
  parola_conf.onkeyup = validare_parola;
