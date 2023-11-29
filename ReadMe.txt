==================================================================================================================

TCC By: Felipe Marostega e Vinicius Golim
Controle supervisório da maquete didática usando IoT, através do broker blynk e microcontrolador ESP32
Versão: 2.0 
link do repositório do GitHub: https://github.com/ViniOGLM/TCC.git
Broker e dashboard: https://blynk.io/
Library: WiFi.h \ WiFiClient.h \ BlynkSimpleEsp32.hv \ LiquidCrystal_I2C.h \ HCSR04.h \ ESP32Servo.h

=================================================================================================================

PinoOut e pinIn do projeto:
sala                     Pino fisíco da ESP32: 04    ||  Pino Virtual do Blynk: V0
quarto                   Pino fisíco da ESP32: 23    ||  Pino Virtual do Blynk: V1
quarto2                  Pino fisíco da ESP32: 19    ||  Pino Virtual do Blynk: V2
cozinha                  Pino fisíco da ESP32: 05    ||  Pino Virtual do Blynk: V3
banheiro                 Pino fisíco da ESP32: 18    ||  Pino Virtual do Blynk: V5
ldr                      Pino fisíco da ESP32: 32    ||  Pino Virtual do Blynk: Sem pino virtual
Varanda                  Pino fisíco da ESP32: 33    ||  Pino Virtual do Blynk: V7
pino_trigger             Pino fisíco da ESP32: 27    ||  Pino Virtual do Blynk: V4
pino_echo                Pino fisíco da ESP32: 34    ||  Pino Virtual do Blynk: V4
buzzer                   Pino fisíco da ESP32: 13    ||  Pino Virtual do Blynk: Sem pino virtual
chuva                    Pino fisíco da ESP32: 35    ||  Pino Virtual do Blynk: V8
Janela cozinha e sala    Pino fisíco da ESP32: 26    ||  Pino Virtual do Blynk: V9
ledinterno               Pino fisíco da ESP32: 02    ||  Pino Virtual do Blynk: Sem pino virtual
Ventiladores             Pino fisíco da ESP32: 25    ||  Pino Virtual do Blynk: V6
