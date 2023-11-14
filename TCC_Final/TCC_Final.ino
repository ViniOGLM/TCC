/*************************************************************
TCC By: Felipe Marostega e Vinicius Golim
Versão: 2.0 
link do repositório do GitHub: https://github.com/ViniOGLM/TCC.git
Broker e dashboard: Blynk
Simulador: https://wokwi.com/projects/377791125355616257
Library: Blynk \ LiquidCrystal I2C \ HCSR04 \ ESP32Servo
*************************************************************/

/* Preencha as informações do Blynk Device Info Aqui */
#define BLYNK_TEMPLATE_ID           "TMPL2sYyoDfry"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "VWlfdcmVjkmNSjR2buM9dHaa3glkkd9I"
#define BLYNK_PRINT Serial
 
#define sala 4                  // V0
#define quarto 23               // V1
#define quarto2 19              // V2
#define cozinha 5               // V3
#define banheiro 18             // V5
#define fitaled 33              // V7
#define pino_trigger 27         // V4
#define pino_echo 34            // V4
#define buzzer 13               // Sem pino virtual
#define chuva 35                // V8
#define SERVO_PIN 26            // Sem pino virtual
#define ledinterno 2            // Sem pino virtual
#define ventiladores 25         // V6
#define LDR 32

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>
#include <ESP32Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
UltraSonicDistanceSensor distanceSensor(pino_trigger, pino_echo); //Conexao RCW-001 ou HC-SR04
Servo servoMotor;

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
                        Comando quarto 1
****************************************************************/
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(quarto,value);
}
/****************************************************************
                        Comando quarto 2
****************************************************************/
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(quarto2,value);
}
/****************************************************************
                        Comando cozinha
****************************************************************/
BLYNK_WRITE(V3)
{
  int value = param.asInt();
  digitalWrite(cozinha,value);
}
/****************************************************************
                        Comando banheiro
****************************************************************/
BLYNK_WRITE(V5)
{
  int value = param.asInt();
  digitalWrite(banheiro,value);
}
/****************************************************************
                        Comando varanda
****************************************************************/
BLYNK_WRITE(V7)
{
  int value = param.asInt();
  digitalWrite(fitaled,value);
}
/****************************************************************
                        Comando ventiladores
****************************************************************/
BLYNK_WRITE(V6)
{
  int value = param.asInt();
  digitalWrite(ventiladores,value);
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
  pinMode(quarto, OUTPUT);       //Define como saída
  pinMode(quarto2, OUTPUT);      //Define como saída
  pinMode(fitaled, OUTPUT);      //Define como saída
  pinMode(buzzer, OUTPUT);       //Define como saída
  pinMode(sala, OUTPUT);         //Define como saída
  pinMode(cozinha, OUTPUT);      //Define como saída
  pinMode(banheiro, OUTPUT);     //Define como saída
  pinMode(ledinterno, OUTPUT);   //Define como saída
  pinMode(ventiladores, OUTPUT); //Define como saída
  pinMode(chuva, INPUT);         //Define como entrada
  pinMode(LDR, INPUT);           //Define como entrada

  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
  Blynk.virtualWrite(V7, 0);

  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin

  timer.setInterval(100L, myTimerEvent);

//Rotina LCD Após conexão com servidor
  lcd.init();                     // Inicia o LCD
  delay(500);                     // atraso de meio segundo
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

}

void loop()
{
/****************************************************************
                      Sensor LDR
****************************************************************/

int analogValueldr = analogRead(LDR);
Serial.print("LDR: ");
Serial.println(analogValueldr);

    if(analogValueldr > 0)
    {
      digitalWrite(2, HIGH);
    }
    else
      digitalWrite(2, LOW);

/****************************************************************
                      Sensor ultrassônico
****************************************************************/
    //Serial.print("Distancia: ");
    //Serial.print(distanceSensor.measureDistanceCm());
    //Serial.println(" cm");

    if(distanceSensor.measureDistanceCm() <= 28)
    {
      //Serial.println("Status do Buzzer: ON");
      digitalWrite(buzzer, HIGH);
      Blynk.virtualWrite(V4, 1);
    }
    else
    {
      //Serial.println("Status do Buzzer: OFF");
      digitalWrite(buzzer, LOW);
      Blynk.virtualWrite(V4, 0);
    }
/****************************************************************
                         Chuva
****************************************************************/
 /* Armazena os valores de leitura */
  val_a = analogRead(chuva);
  //Serial.print("Valor sensor chuva analog: ");
  //Serial.println(val_a);
    if (val_a < 2500)
    {
          int pos = 180;
          servoMotor.write(pos);
          Blynk.virtualWrite(V8, 1);
          Blynk.virtualWrite(V9, 1);
    }
  else
  {
        int pos = 0;
        servoMotor.write(pos);
        Blynk.virtualWrite(V8, 0);
        Blynk.virtualWrite(V9, 0);
  }
  Blynk.run();
  timer.run();
}
