<?php

$subiect = "CONT CREAT SITE INFORMATII SPANIA";
$continut =
"
Bine ai venit, '$nume_utilizator'!\r\n

INFORMATII FORMULAR:\r\n

Nume de utilizator: '$nume_utilizator'\r\n
Email: '$email'\r\n
";
$headers = "From: gamecomunity777@gmail.com";

if (mail($email, $subiect, $continut, $headers))
{
    echo "<br>Emailul a fost trimis!";
}
else
    echo "Eroare! Email-ul NU a putut fi trimis!";

?>