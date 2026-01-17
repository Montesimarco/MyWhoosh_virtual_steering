/*********
Pin I2C di default: Su questa scheda i pin standard sono GPIO 21 (SDA) e GPIO 22 (SCL)
PinMode: Nel setup() ho impostato i pin 18 e 19 come output.
Logica LED:
Quando sterzi a sinistra, il LED SX si accende insieme all'invio del tasto '>'.
Quando sterzi a destra, il LED DX si accende insieme all'invio del tasto '<'.
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

// --- PARAMETRI STERZATA ---
#define SOGLIA_VELOCITA   50.0     // Sensibilità colpo
#define DURATA_PRESSIONE  1250     // Durata pressione tasto
#define DEBOUNCE_STERZO   2500     // Tempo minimo tra due sterzate

MPU6050 mpu(Wire);
BleKeyboard bleKeyboard("MyWhoosh Steering", "Espressif", 100);

// --- VARIABILI DI STATO ---
unsigned long lastActionTime = 0;
bool sterzataInCorso = false;
uint16_t tastoAttivo = 0;

// --- FILTRO VELOCITÀ ---
float velZ_filtrata = 0.0;
const float filtroAlpha = 0.20;   // 20% nuovo valore, 80% precedente

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
  Serial.println("Sistema Pronto (Sterzata 1.25s)");
}

void loop() {
  mpu.update();
  unsigned long now = millis();

  // --- FILTRO SULLA VELOCITÀ Z ---
  float velZ = mpu.getGyroZ();
  velZ_filtrata = velZ_filtrata * (1.0 - filtroAlpha) + velZ * filtroAlpha;

  // --- SE BLE NON È CONNESSO ---
  if (!bleKeyboard.isConnected()) {
    bool blink = (now / 500) % 2;
    digitalWrite(PIN_LED_SX, blink);
    digitalWrite(PIN_LED_DX, blink);
    return;
  }

  // --- RILEVAMENTO COLPO ---
  if (!sterzataInCorso && (now - lastActionTime > DEBOUNCE_STERZO)) {

    if (velZ_filtrata > SOGLIA_VELOCITA) {
      // Sterzata SX
      tastoAttivo = KEY_LEFT_ARROW;
      bleKeyboard.press(tastoAttivo);
      sterzataInCorso = true;
      lastActionTime = now;
      digitalWrite(PIN_LED_SX, HIGH);
      Serial.println(">>> STERZATA SX");
    }
    else if (velZ_filtrata < -SOGLIA_VELOCITA) {
      // Sterzata DX
      tastoAttivo = KEY_RIGHT_ARROW;
      bleKeyboard.press(tastoAttivo);
      sterzataInCorso = true;
      lastActionTime = now;
      digitalWrite(PIN_LED_DX, HIGH);
      Serial.println(">>> STERZATA DX");
    }
  }

  // --- RILASCIO AUTOMATICO ---
  if (sterzataInCorso && (now - lastActionTime >= DURATA_PRESSIONE)) {
    bleKeyboard.release(tastoAttivo);
    sterzataInCorso = false;
    digitalWrite(PIN_LED_SX, LOW);
    digitalWrite(PIN_LED_DX, LOW);
    Serial.println(">>> FINE STERZATA");
  }
}
