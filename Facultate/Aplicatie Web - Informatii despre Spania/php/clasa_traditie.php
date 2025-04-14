<?php

class Traditie
{
    var $ID;
    var $nume;
    var $cale_img;

    function __construct($ID, $N, $CI)
    {
        $this->ID = $ID;
        $this->nume = $N;
        $this->cale_img = $CI;
    }

    function afisare_slide_traditie()
    {
        echo
        "
            <div class='slide_traditie2 fade'>
                <div class='numbertext'>$this->ID / 6</div>
                <a href='autentificare_inregistrare.php'><img src='$this->cale_img' style='width:100%; height:550px; object-fit:cover'></a>
                <div class='text font-oswald background-negru'>'$this->nume'</div>
            </div>
        ";
    }
}

?>