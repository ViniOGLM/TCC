/*************************************************************
TCC By: Felipe Marostega e Vinicius Golim
Versão: 1.8
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
 
#define sala 4                  // V0
#define quarto 2                // V1
#define quarto2 20              // V2
#define cozinha 17              // V3
#define banheiro 16             // V5
#define ldr 34                  // V6
#define fitaled 12              // V7
#define pino_trigger 5          // V4
#define pino_echo 18            // V4
#define buzzer 13               // Sem pino virtual
#define chuva 35                // V8

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
UltraSonicDistanceSensor distanceSensor(pino_trigger, pino_echo); //Conexao RCW-001 ou HC-SR04

int show=0;
int val_a = 0;   /* Armazena leitura do pino analógico */

// Insira aqui suas informações do Wifi
char ssid[] = "ESP32 GOLIM";
char pass[] = "Vvgolimoliveira";
BlynkTimer timer;

/****************************************************************
                        Comando sala
****************************************************************/
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(sala,value);
}

/****************************************************************
                        Comando quarto
****************************************************************/
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(quarto,value);
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
  pinMode(chuva, INPUT);


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
  /****************************************************************
                      Sensor ultrassônico
****************************************************************/
    Serial.print("Distancia: ");
    Serial.print(distanceSensor.measureDistanceCm());
    Serial.println(" cm");
    delay(500);

    if(distanceSensor.measureDistanceCm() <= 21)
    {
      Serial.println("Status do Buzzer: ON");
      digitalWrite(buzzer, HIGH);
      Blynk.virtualWrite(V4, 255);
    }
    else
    {
      Serial.println("Status do Buzzer: OFF");
      digitalWrite(buzzer, LOW);
      Blynk.virtualWrite(V4, 0);
    }
/****************************************************************
                         Chuva
****************************************************************/
 /* Armazena os valores de leitura */
  val_a = analogRead(chuva);

  Serial.println(val_a);
  /* Se a leitura analógica for menor que 300 */
  if ( val_a < 2000)
  {
      digitalWrite(quarto, HIGH);
  }
  else
      digitalWrite(quarto, LOW);
}
