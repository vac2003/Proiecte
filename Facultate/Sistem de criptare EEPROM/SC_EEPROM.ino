#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <at24c256.h>
#include <string.h>

// Initializare LCD 1602 I2C cu adresa 0x27 cu 16 coloane si 2 linii.
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Initializare AT24C256.
AT24C256 eeprom(AT24C_ADDRESS_0);

// Optiune meniu.
int optiune_meniu = 0;

// Aici va fi optiune_aleasa utilizatorul in meniu.
String optiune_aleasa = "";

// Se retine valoarea de adaugat in eeprom.
String val_necriptata_de_adaugat = "";

int pozitie_cursor = 9;

// 2 - sterge, 3 - enter, 4-8 scrie cifra_criptata (nr_pin - 4) * 2 pentru o apasare sau ((nr_pin - 4) * 2) + 1 pentru doua apasari rapide.
const int vector_pini_butoane[] = {2, 3, 4, 5, 6, 7, 8};
const int nr_butoane = 7;

int stare_curenta_butoane[nr_butoane];
int stare_anterioara_butoane[nr_butoane];
unsigned long ultima_apasare_butoane[nr_butoane];
unsigned long ultimul_debounce[nr_butoane];

const unsigned long intarziere_debounce = 50;
const unsigned long fereastra_apasare_dubla = 400; // Timpul maxim in milisecunde in care utilizatorul poate apasa un buton de doua ori pentru a activa o alta functie

bool bool_o_apasare[nr_butoane]; // Flags for single presses of all buttons

void setup() {
  Serial.begin(9600); // Initialize Serial communication
  Wire.begin();

  uint8_t byteeprom = eeprom.read(0);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Bine ai venit!");

  // Initialize buttons
  for (int i = 0; i < nr_butoane; i++) {
    pinMode(vector_pini_butoane[i], INPUT); // Initializam pinii cu INPUT
    stare_curenta_butoane[i] = LOW;        // Initializam starea curenta cu LOW (OFF).
    stare_anterioara_butoane[i] = LOW;
    bool_o_apasare[i] = false;
  }

  delay(1000);
  
  afisare_meniu_optiuni();

}

void loop() {
  for (int i = 0; i < nr_butoane; i++) {
    VerificaCazuriButon(i);
  }
}

void VerificaCazuriButon(int poz_buton) 
{
  int citire_stare_buton = digitalRead(vector_pini_butoane[poz_buton]);

  if (citire_stare_buton != stare_anterioara_butoane[poz_buton]) 
  {
    ultimul_debounce[poz_buton] = millis();
  }

  if ((millis() - ultimul_debounce[poz_buton]) > intarziere_debounce) 
  {

    if (citire_stare_buton == HIGH && stare_curenta_butoane[poz_buton] == LOW) 
    {
      unsigned long timp_curent = millis();

      if (timp_curent - ultima_apasare_butoane[poz_buton] < fereastra_apasare_dubla) 
      {
        // S-a detectat o apasare dubla.
        ActiuniApasareDubla(poz_buton);
        bool_o_apasare[poz_buton] = false; // Devine fals pentru ca ActiuniApasareSimpla sa nu fie executata
      } 
      else 
      {
        bool_o_apasare[poz_buton] = true;
      }

      ultima_apasare_butoane[poz_buton] = timp_curent;
    }

    stare_curenta_butoane[poz_buton] = citire_stare_buton;
  }

  // Daca bool-ul este adevarat si utilizatorul a stat mai mult de 0.4 secunde sa apese de doua ori butonul atunci se execute ActiuniApasareSimpla.
  if (bool_o_apasare[poz_buton] && millis() - ultima_apasare_butoane[poz_buton] > fereastra_apasare_dubla) 
  {
    ActiuniApasareSimpla(poz_buton);
    bool_o_apasare[poz_buton] = false;
  }

  stare_anterioara_butoane[poz_buton] = citire_stare_buton;
}
//-----------------------------------------------
void ActiuniApasareSimpla(int poz_buton) 
{
  if (vector_pini_butoane[poz_buton] == 2) 
  {
    if (pozitie_cursor > 0)
    {
      lcd.setCursor(1, pozitie_cursor - 1);
      lcd.print(" ");
      lcd.setCursor(1, pozitie_cursor - 1);
      --pozitie_cursor;

      if (optiune_meniu == 0)
      {
        optiune_aleasa.remove(optiune_aleasa.length() - 1);
        Serial.println("Opt: " + optiune_aleasa);
      }
      else if (optiune_meniu == 1)
      {
        val_necriptata_de_adaugat.remove(val_necriptata_de_adaugat.length() - 1);
        Serial.println("VAL: " + val_necriptata_de_adaugat);
      }

    }
  } 

  else if (vector_pini_butoane[poz_buton] == 3) 
  {
    // PIN 3 ESTE ENTER.
    Serial.println(optiune_meniu);
    if (optiune_meniu == 0)
    {
      lcd.clear();

      if (optiune_aleasa == "1")
      {
        optiune_meniu = 1;
        afisare_lcd_adauga();
      }
      else if (optiune_aleasa == "2")
      {
        char readBuffer[64];

        CitesteTextCriptat_EEPROM(readBuffer, 0);

        lcd.clear();
        lcd.print("NR. CRIPTAT:");
        lcd.setCursor(0, 1);
        lcd.print(String(readBuffer));

        delay(2500);

        DecriptareText(readBuffer, 3);
        lcd.clear();
        lcd.print("NR. DECRIPTAT.:");
        lcd.setCursor(0, 1);
        lcd.print(readBuffer);

        delay(2500);

        afisare_meniu_optiuni();
      }
      else 
      {
        lcd.print("OPTIUNE GRESITA!");
        delay(1000);
        afisare_meniu_optiuni();
      }

    }
    else if (optiune_meniu == 1)
    {

      String val_criptata = CriptareText(val_necriptata_de_adaugat, 3);
      const char* lista_val_cr = val_criptata.c_str();
      StocareTextCriptat_EEPROM(lista_val_cr, 3, 0);

      lcd.clear();
      lcd.print("Numar adaugat.");

      delay(1500);

      optiune_meniu = 0;
      afisare_meniu_optiuni();
    }
    optiune_aleasa = "";
    val_necriptata_de_adaugat = "";
  } 
  else 
  {
    int val = (vector_pini_butoane[poz_buton] - 4) * 2;

    if (pozitie_cursor < 16)
    {
      pozitie_cursor++;
      lcd.print(val);

      if (optiune_meniu == 0)
      {
        optiune_aleasa = optiune_aleasa + String(val);
        Serial.println("Opt: " + optiune_aleasa);
      }
      else if (optiune_meniu == 1)
      {
        val_necriptata_de_adaugat = val_necriptata_de_adaugat + String(val);
        Serial.println("VAL: " + val_necriptata_de_adaugat);
      }
    }

    Serial.println(val);
  }
}

void ActiuniApasareDubla(int poz_buton) 
{
  if (vector_pini_butoane[poz_buton] == 2 || vector_pini_butoane[poz_buton] == 3) 
  {
    return;
  }

  int val = (vector_pini_butoane[poz_buton] - 4) * 2 + 1;


  if (pozitie_cursor < 16)
  {
    pozitie_cursor++;
    lcd.print(val);

    if (optiune_meniu == 0)
    {
      optiune_aleasa = optiune_aleasa + String(val);
      Serial.println("Opt: " + optiune_aleasa);
    }
    else if (optiune_meniu == 1)
    {
      val_necriptata_de_adaugat = val_necriptata_de_adaugat + String(val);
      Serial.println("VAL: " + val_necriptata_de_adaugat);
    }
  }

  Serial.println(val);
}

// Cifrul lui Caesar, algoritm de criptare simpla
String CriptareText(String val_necriptata, int permutare) 
{
    permutare = permutare % 10;

    if(permutare < 0) 
      permutare += 10;
    
    for(int i = 0; i < val_necriptata.length(); i++) 
    {
        int cifra_criptata = val_necriptata[i] - '0';
        cifra_criptata = (cifra_criptata + permutare) % 10;
        val_necriptata[i] = cifra_criptata + '0';
    }

    return val_necriptata;
}

void DecriptareText(char* val_criptata, int permutare) 
{
    permutare = permutare % 10;
    if(permutare < 0) permutare += 10;
    
    for(int i = 0; val_criptata[i] != '\0'; i++) 
    {
        int cifra_decriptata = val_criptata[i] - '0';
        cifra_decriptata = (cifra_decriptata - permutare + 10) % 10;
        val_criptata[i] = cifra_decriptata + '0';
    }
}

// Salveaza in EEPROM numerele scrise de utilizator (momentan nu se pot salva mai multe texte in eeprom).
void StocareTextCriptat_EEPROM(const char* data, int permutare, uint16_t adresa_mem) 
{
    
    char buffer[64];

    strncpy(buffer, data, sizeof(buffer) - 1);

    buffer[sizeof(buffer) - 1] = '\0';
    
    CriptareText(buffer, permutare);
    
    eeprom.put(adresa_mem, (uint8_t)permutare);
    
    uint8_t len = strlen(buffer);
    eeprom.put(adresa_mem + 1, len);
    
    for(uint8_t i = 0; i < len; i++) 
    {
        eeprom.put(adresa_mem + 2 + i, buffer[i]);
    }
}

void CitesteTextCriptat_EEPROM(char* buffer, uint16_t adresa_mem) 
{
    int permutare = eeprom.read(adresa_mem);
    
    uint8_t len = eeprom.read(adresa_mem + 1);
    
    for(uint8_t i = 0; i < len; i++) 
    {
        buffer[i] = eeprom.read(adresa_mem + 2 + i);
    }
    buffer[len] = '\0';
}

/*FUNCTII PENTRU LCD*/
void afisare_meniu_optiuni()
{
  lcd.clear();
  lcd.print("1,2/Adauga,Print");
  lcd.setCursor(0, 1);
  lcd.print("Optiune: ");
  pozitie_cursor = 9;
}
void afisare_lcd_adauga()
{
  lcd.clear();
  lcd.print("SCRIE NR: ");
  lcd.setCursor(0, 1);
}
void afisare_lcd_afisare()
{
  lcd.clear();
  lcd.print("NR. STOCAT ESTE:");
  lcd.setCursor(0, 1);
}