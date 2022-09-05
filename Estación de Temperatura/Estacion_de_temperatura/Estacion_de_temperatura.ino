#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);

#define LEDVERDE 6
#define LEDAZUL 7
#define LEDROJO 5
#define DHTPIN 4
#define DHTTYPE DHT11


//.............Variables............. 
int Humedad;
int Temperaturac;
int Temperaturaf;
int IndiceC;




// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
//  pinMode(LDR, INPUT);
  pinMode(LEDVERDE,OUTPUT);
  pinMode(LEDAZUL,OUTPUT);
  pinMode(LEDROJO,OUTPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();

  
  lcd.print("Iniciado sistema");
  lcd.setCursor(0, 1);
  lcd.print("Comprobado LEDs");
  delay(3000);
  
  lcd.setCursor(0, 0);
  lcd.print("    LED Verde   ");
  lcd.setCursor(0, 1);  
  lcd.print("    Encendido   ");
  digitalWrite(LEDVERDE, 1);
  delay(2000);
  
  lcd.setCursor(0, 0);
  lcd.print("    LED  ROJO   ");
  lcd.setCursor(0, 1);  
  lcd.print("    Encendido  ");
  digitalWrite(LEDROJO, 1);
  digitalWrite(LEDVERDE, 0);
  delay(2000);
  
  lcd.setCursor(0, 0);
  lcd.print("    LED  AZUL   ");
  lcd.setCursor(0, 1);  
  lcd.print("    Encendido  ");
  digitalWrite(LEDROJO, 0);
  digitalWrite(LEDAZUL, 1);
  delay(2000);
  digitalWrite(LEDAZUL, 0);  
}

void loop() {
 
  // Leemos la humedad relativa
  Humedad = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  Temperaturac = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  Temperaturaf = dht.readTemperature(true);


  IndiceC = dht.computeHeatIndex(Temperaturac, Humedad, false);

  
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(Humedad) || isnan(Temperaturac) || isnan(Temperaturaf)) {
    lcd.setCursor(0, 0);
    lcd.print("Error obteniendo     ");
    lcd.setCursor(0, 1);
    lcd.print("    los datos          ");
    return;
  }
 
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  lcd.print("C:");
  lcd.print(Temperaturac);
  lcd.print(" ");
  lcd.setCursor(11, 0);
  lcd.print("F:");
  lcd.print(Temperaturaf);
  lcd.print("  ");  
  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print(Humedad);
  lcd.print("% ");
  
 lcd.setCursor(8, 1);
 lcd.print("IT:");
 lcd.print(IndiceC);
 lcd.print("C ");


if (Temperaturac >= 30 ) {
  digitalWrite(LEDROJO, HIGH);
  digitalWrite(LEDAZUL,LOW);
  digitalWrite(LEDVERDE, LOW);
  }
  if (Temperaturac <=29 && Temperaturac >=23){
  digitalWrite(LEDVERDE, HIGH);
  digitalWrite(LEDROJO, LOW);
  digitalWrite(LEDAZUL,LOW);
  }
  if (Temperaturac <=22) {
  digitalWrite(LEDAZUL, HIGH);
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDROJO, LOW);
  }

  delay(5000);
}
