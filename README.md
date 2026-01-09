Pin I2C di default: Su questa scheda i pin standard sono GPIO 21 (SDA) e GPIO 22 (SCL)
PinMode: Nel setup() ho impostato i pin 18 e 19 come output.
Logica LED:
Quando sterzi a sinistra, il LED SX si accende insieme all'invio del tasto 'freccia sx'.
Quando sterzi a destra, il LED DX si accende insieme all'invio del tasto 'freccia dx'.
Al centro, entrambi i LED si spengono.
Feedback Stato Bluetooth: Se la tastiera non è ancora connessa al PC, ho aggiunto un lampeggio lento di entrambi i LED (500ms) per avvisarti che il dispositivo è in attesa di pairing.
Test Iniziale: All'accensione i LED si accendono per mezzo secondo, così sai subito se i collegamenti elettrici sono corretti.
LED Sinistro: Anodo (gamba lunga) al GPIO 18, Catodo (gamba corta) a GND tramite una resistenza da 220Ω.
LED Destro: Anodo (gamba lunga) al GPIO 19, Catodo (gamba corta) a GND tramite una resistenza da 220Ω.

Consiglio Hardware: Se i salti continuano, aggiungi un condensatore da 100nF tra i pin VCC e GND del sensore MPU6050. 
Questo pulisce l'alimentazione quando il Bluetooth dell'ESP32 assorbe picchi di corrente.
