#include <TimerOne.h>
#include "kernel.h"  

#include "drv_sensor.h"

const uint8_t process1LedPins[4] = {22, 23, 24, 25};

#define MOTION_SENSOR_PIN 8
#define BUZZER_PIN        7
#define RED_LED_PIN       9

char processo1(void);
char processo2(void);
process p1,p2;

driver *sensorMoviment;

void setup() {
  Serial.begin(9600);
  
  uint8_t sensorPin = MOTION_SENSOR_PIN;
  sensorMoviment = getSensorDriver();
  sensorMoviment->initFunc(&sensorPin);

  for (int i = 0; i < 4; i++) {
    pinMode(process1LedPins[i], OUTPUT);
    digitalWrite(process1LedPins[i], LOW);
  }
  
  pinMode(BUZZER_PIN, OUTPUT);              
  pinMode(RED_LED_PIN, OUTPUT);             
  digitalWrite(RED_LED_PIN, LOW);           

  kernelInit();

  p1 = {processo1, 1, 0};
  p2 = {processo2, 2, 0};

  if(kernelAddProc(&p1) == SUCCESS) {
    Serial.println("Processo 1 adicionado");
  }
  
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(tick);
  
  kernelLoop();
}

void tick(){
  kernelTick();
}

char processo1(void) {
  
  static uint8_t ledIndex = 0;      
  static uint8_t tickCounter = 0;   
  static bool firstCall = true;     

  if(firstCall) {
    // Na inicialização do processo, acende o primeiro LED (pino 22)
    digitalWrite(process1LedPins[ledIndex], HIGH);
    firstCall = false;
    return REPEAT;
  }
  
  tickCounter++;  // Incrementa a cada tick (1 segundo)
  
  if(tickCounter >= 2) {  // Se se passaram 2 segundos desde a última ação...
    ledIndex++;         // Passa para o próximo LED
    tickCounter = 0;    // Reseta o contador
    
    if(ledIndex <= 3) {
      
      digitalWrite(process1LedPins[ledIndex], HIGH);
    }
    else if(ledIndex == 4) { // modificar para == 4, ou inserir no IF
      
      for (int i = 0; i < 4; i++){ // apagar luzes
         digitalWrite(process1LedPins[i], LOW);
      
      }
      
      ledIndex = 0;
      tickCounter = 0;
      firstCall = true;
      
      if(kernelAddProc(&p2) == SUCCESS) {
         Serial.println("Processo 2 iniciado");
      }
      
      return SUCCESS;  
    }
  }
  
  return REPEAT;  
}

char processo2(void) {
  static uint8_t tickCounter = 0;    
  static bool motionDetected = false;  

  uint8_t sensorPin = MOTION_SENSOR_PIN;
  if(!motionDetected && (sensorMoviment->funcoes[SENSOR_READ](&sensorPin) == HIGH)) {
    motionDetected = true;
    digitalWrite(RED_LED_PIN, HIGH);         
    tone(BUZZER_PIN, 1000, 200);               
    Serial.println("Movimento detectado!");
  }
  
  if(motionDetected) {
    tickCounter++;
    if(tickCounter >= 3) {
      digitalWrite(RED_LED_PIN, LOW);  
      tickCounter = 0;
      motionDetected = false;
      
      if(kernelAddProc(&p1) == SUCCESS) {
         Serial.println("Processo 1 reiniciado após movimento");
      }
      return SUCCESS;
    }
  }
  else {
    
    tickCounter++;
    if(tickCounter >= 4) {
      tickCounter = 0;
      digitalWrite(RED_LED_PIN, LOW);  
      Serial.println("Nenhum movimento detectado. Reiniciando Processo 1.");
      if(kernelAddProc(&p1) == SUCCESS) {
         Serial.println("Processo 1 reiniciado após movimento");
      }
      return SUCCESS;
    }
  }
  return REPEAT;
  
}

void loop() {
}
