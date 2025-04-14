<?php

$subiect = "Detalii Opinie Informatii Spania";
$continut =
"
Va multumim, $nume $pren! Mai jos ai detaliile pe care ni le-ai oferit:\r\n

Numele: '$nume'\r\n
Prenumele: '$pren'\r\n
Email: '$email'\r\n
Mesaj: '$opinie'\r\n
";
$headers = "From: gamecomunity777@gmail.com";

if (mail($email, $subiect, $continut, $headers))
{
    echo "<br>Emailul a fost trimis!";
}
else
    echo "Eroare! Email-ul NU a putut fi trimis!";

?>