/*************************************************************
TCC By: Felipe Marostega e Vinicius Golim
Versão: 1.3
link do repositório do GitHub: https://github.com/ViniOGLM/TCC.git
Broker e dashboard: Blynk
Simulador: https://wokwi.com/projects/377791125355616257
Library: Blynk \ LiquidCrystal I2C \ HCSR04
*************************************************************/

/* Preencha as informações do Blynk Device Info Aqui */
#define BLYNK_TEMPLATE_ID           "TMPL2sYyoDfry"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "VWlfdcmVjkmNSjR2buM9dHaa3glkkd9I"
#define BLYNK_PRINT Serial
#define ledA 4
#define ledB 2
#define ldr 34
#define fitaled 12
#define pino_trigger 5
#define pino_echo 18
#define buzzer 13

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
UltraSonicDistanceSensor distanceSensor(pino_trigger, pino_echo); //Conexao RCW-001 ou HC-SR04

int show=0;

// Insira aqui suas informações do Wifi
char ssid[] = "ESP32 GOLIM";
char pass[] = "Vvgolimoliveira";
BlynkTimer timer;

/****************************************************************
                        Comando ledA
****************************************************************/
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(ledA,value);
}

/****************************************************************
                        Comando ledB
****************************************************************/
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(ledB,value);
}

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  //Definição de pinos
  pinMode(4, OUTPUT);            //Define o píno 4 como saída
  pinMode(2, OUTPUT);            //Define o píno 2 como saída
  pinMode(ldr, INPUT);           //Define o pino 35 como entrada
  pinMode(fitaled, OUTPUT);      //Define o píno 12 como saída
  pinMode(buzzer, OUTPUT);       //Define o píno 13 como saída

  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(100L, leituraAnalogica);

//Rotina LCD Após conexão com servidor
  lcd.init();                      // Inicia o LCD
  delay(500);                    // atraso de meio segundo
  lcd.clear();                    // limpa a tela
  lcd.backlight();                // Liga a luz de fundo do LCD
  lcd.setCursor(0,0);             // Define o cursor na coluna 1, linha 1
  lcd.print("TCC IoT");           // Print a message to the LCD.
  lcd.setCursor(0,1);             // Define o cursor na coluna 1, linha 2.+
  lcd.print("Felipe e Golim");    // Imprimi a menssagem no display
  delay(1000);              
  lcd.clear();                    // limpa a tela
}

//Da ESP32 para o Blynk
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

//Da ESP32 para o Blynk
void leituraAnalogica()
{
  int ldrValue=analogRead(ldr);
  ldrValue=map(ldrValue,0,4095,0,200);
  Serial.print("LDR: ");
  Serial.println(ldrValue);
  if(ldrValue > 20)
  {
    digitalWrite(fitaled, HIGH);
    }
  else
  {
    digitalWrite(fitaled, LOW);
  }
  Blynk.virtualWrite(V5, millis() / 1000);
}

void loop()
{
  Blynk.run();
  timer.run();
      //Efetua a leitura da distancia em centimetros
    Serial.print("Distancia: ");
    Serial.print(distanceSensor.measureDistanceCm());
    Serial.println(" cm");
    delay(500);

    if(distanceSensor.measureDistanceCm() <= 10)
    {
      Serial.println("Status: ON");
      digitalWrite(buzzer, HIGH);
    }
    else
    {
      Serial.println("Status: OFF");
      digitalWrite(buzzer, LOW);
    }
}
