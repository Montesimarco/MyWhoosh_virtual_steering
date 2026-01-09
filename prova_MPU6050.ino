/*********
Pin I2C di default: Su questa scheda i pin standard sono GPIO 21 (SDA) e GPIO 22 (SCL)
PinMode: Nel setup() ho impostato i pin 18 e 19 come output.
Logica LED:
Quando sterzi a sinistra, il LED SX si accende insieme all'invio del tasto 'A'.
Quando sterzi a destra, il LED DX si accende insieme all'invio del tasto 'D'.
Al centro, entrambi i LED si spengono.
Feedback Stato Bluetooth: Se la tastiera non è ancora connessa al PC, ho aggiunto un lampeggio lento di entrambi i LED (500ms) per avvisarti che il dispositivo è in attesa di pairing.
Test Iniziale: All'accensione i LED si accendono per mezzo secondo, così sai subito se i collegamenti elettrici sono corretti.
LED Sinistro: Anodo (gamba lunga) al GPIO 18, Catodo (gamba corta) a GND tramite una resistenza da 220Ω.
LED Destro: Anodo (gamba lunga) al GPIO 19, Catodo (gamba corta) a GND tramite una resistenza da 220Ω.

Consiglio Hardware: Se i salti continuano, aggiungi un condensatore da 100nF tra i pin VCC e GND del sensore MPU6050. 
Questo pulisce l'alimentazione quando il Bluetooth dell'ESP32 assorbe picchi di corrente.

*********/

#include <Wire.h>
#include <MPU6050_light.h>
#include <BleKeyboard.h>

// --- CONFIGURAZIONE PIN ---
#define I2C_SDA 21
#define I2C_SCL 22
#define PIN_LED_SX 18  
#define PIN_LED_DX 19  

// --- PARAMETRI SENSIBILITÀ ---
#define SOGLIA_VELOCITA 60.0   
#define DEBOUNCE_STERZO 4000   // Aumentato per coprire la durata della raffica (5x200ms = 1000ms)

// --- PARAMETRI RAFFICA ---
#define NUM_IMPULSI 60          // Quanti tasti inviare per ogni colpo
#define INTERVALLO_RAFFICA 50 // Millisecondi tra un tasto e l'altro della raffica

MPU6050 mpu(Wire);
BleKeyboard bleKeyboard("MyWhoosh Steering", "Espressif", 100);

// Variabili di stato per la raffica
unsigned long lastActionTime = 0;
unsigned long lastBurstTime = 0;
int impulsiRimanenti = 0;
uint16_t tastoDaInviare = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED_SX, OUTPUT);
  pinMode(PIN_LED_DX, OUTPUT);
  
  Wire.begin(I2C_SDA, I2C_SCL, 100000);
  if (mpu.begin() != 0) {
    Serial.println("Errore MPU6050!");
    while (1);
  }
  
  Serial.println("Calibrazione...");
  mpu.calcOffsets(); 
  bleKeyboard.begin();
  Serial.println("Sistema Pronto per 2026. Modalità: RAFFICA 5x");
}

void loop() {
  mpu.update();
  float velZ = mpu.getGyroZ(); 
  unsigned long now = millis();

  if (bleKeyboard.isConnected()) {
    
    // 1. RILEVAMENTO NUOVO COLPO (Solo se non c'è una raffica in corso)
    if (impulsiRimanenti == 0 && (now - lastActionTime > DEBOUNCE_STERZO)) {
      
      if (velZ > SOGLIA_VELOCITA) { // Colpo a SINISTRA
        tastoDaInviare = KEY_LEFT_ARROW;
        impulsiRimanenti = NUM_IMPULSI;
        lastActionTime = now;
        digitalWrite(PIN_LED_SX, HIGH);
        Serial.println("\n>>> RILEVATO COLPO SX: Avvio Raffica 5x <<<");
      } 
      else if (velZ < -SOGLIA_VELOCITA) { // Colpo a DESTRA
        tastoDaInviare = KEY_RIGHT_ARROW;
        impulsiRimanenti = NUM_IMPULSI;
        lastActionTime = now;
        digitalWrite(PIN_LED_DX, HIGH);
        Serial.println("\n>>> RILEVATO COLPO DX: Avvio Raffica 5x <<<");
      }
    }

    // 2. GESTIONE DELLA RAFFICA (Esegue gli invii temporizzati)
    if (impulsiRimanenti > 0) {
      if (now - lastBurstTime >= INTERVALLO_RAFFICA) {
        bleKeyboard.write(tastoDaInviare);
        impulsiRimanenti--;
        lastBurstTime = now;
        
        Serial.print("Invio tasto [");
        Serial.print(NUM_IMPULSI - impulsiRimanenti);
        Serial.println("/5]");
      }
    } else {
      // Spegnimento LED quando la raffica è finita
      digitalWrite(PIN_LED_SX, LOW);
      digitalWrite(PIN_LED_DX, LOW);
    }

  } else {
    // Lampeggio attesa Bluetooth
    digitalWrite(PIN_LED_SX, (now / 500) % 2);
    digitalWrite(PIN_LED_DX, (now / 500) % 2);
  }
}
