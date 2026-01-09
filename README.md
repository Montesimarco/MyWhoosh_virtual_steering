🚴‍♂️ MyWhoosh Bluetooth Smart Steering (ESP32-WROOM-32)
Questo progetto trasforma una scheda ESP32-WROOM-32 e un sensore MPU6050 in un sistema di sterzata intelligente per MyWhoosh (o Zwift). A differenza dei sistemi basati sull'angolo statico, questo dispositivo rileva l'impulso cinematico (un colpo secco dello sterzo), eliminando i problemi di deriva dei sensori economici e rendendo l'esperienza di gioco fluida e reattiva.
🌟 Caratteristiche principali
Zero Drift Technology: Utilizza la velocità angolare (Giroscopio Z) per rilevare il movimento. Non importa se il sensore "scivola" nel tempo, risponderà sempre solo ai tuoi comandi reali.
Modalità Burst (Raffica): Un singolo colpo di sterzo fisico invia una sequenza di 5 pressioni tasto (frecce direzionali) ogni 200ms, simulando una sterzata decisa e naturale nel software.
Connessione Bluetooth HID: Riconosciuto dal PC/Tablet come una tastiera standard. Nessun driver o software aggiuntivo necessario.
Bassa Sensibilità Calibrata: Ottimizzato per ignorare le vibrazioni del rullo e i movimenti involontari durante lo sforzo intenso.
Feedback Visivo: Due LED indicano in tempo reale l'attivazione della sterzata a destra o sinistra.
🛠 Hardware necessario
Componente	Descrizione
ESP32-WROOM-32	Microcontrollore con Bluetooth integrato
MPU6050	Accelerometro e Giroscopio a 6 assi
2x LED	Feedback visivo (es. Rosso per DX, Verde per SX)
2x Resistenze 220Ω	Per i LED
Cavi Jumper	Per i collegamenti
🔌 Collegamenti (Pinout)
MPU6050	ESP32 Pin	Note
VCC	3.3V	Alimentazione stabile
GND	GND	Terra comune
SCL	GPIO 22	Bus I2C
SDA	GPIO 21	Bus I2C
AD0	GND	Forza indirizzo I2C 0x68
LED	ESP32 Pin	Note
LED SX	GPIO 18	Attivo durante sterzata a sinistra
LED DX	GPIO 19	Attivo durante sterzata a destra
💻 Requisiti Software
Arduino IDE (Versione 1.8.19 o superiore)
Core ESP32 di Espressif (Versione 3.0.7 o superiore)
Librerie richieste:
MPU6050_light (di rfetick)
ESP32-BLE-Keyboard (di T-vK) con correzione .c_str() per Core 3.x
🚀 Istruzioni per l'uso
Montaggio: Fissa l'ESP32 e il sensore al centro del manubrio della tua bicicletta. Assicurati che il sensore sia ben saldo per evitare vibrazioni eccessive.
Calibrazione: All'accensione, tieni il manubrio fermo per 2 secondi. I LED lampeggeranno per indicare che la calibrazione degli offset è completata.
Pairing: Cerca "MyWhoosh Steering" nelle impostazioni Bluetooth del tuo dispositivo e connettiti.
In Gioco: Mentre pedali su MyWhoosh, dai un colpo deciso a destra o sinistra per cambiare traiettoria. Il sistema invierà automaticamente una raffica di 5 impulsi per garantire il cambio di corsia.
🔧 Parametri Personalizzabili
Nel codice puoi regolare i seguenti valori per adattarli al tuo stile:
SOGLIA_VELOCITA: Aumenta (es. 100) per rendere lo sterzo ancora meno sensibile.
NUM_IMPULSI: Cambia il numero di tasti inviati per ogni sterzata.
INTERVALLO_RAFFICA: Modifica la velocità della sterzata virtuale.
Progetto sviluppato per la community ciclistica virtuale - Gennaio 2026
