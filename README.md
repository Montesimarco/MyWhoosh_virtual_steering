<h1 align="center">🚴‍♂️ MyWhoosh Bluetooth Smart Steering</h1>

<p align="center">
  <img src="img.shields.io" alt="ESP32">
  <img src="img.shields.io" alt="Bluetooth HID">
  <img src="img.shields.io" alt="Status">
</p>

<p align="center">
  <strong>Trasforma il tuo manubrio in un controller intelligente per MyWhoosh, Zwift e simulatori di ciclismo.</strong>
  <br>
  Elimina la deriva del sensore grazie alla tecnologia a impulsi cinetici.
</p>

<hr>

<h2>🌟 Caratteristiche Principali</h2>
<ul>
  <li><strong>Tecnologia Anti-Deriva:</strong> Utilizza la velocità angolare (Giroscopio Z) per reagire solo ai movimenti bruschi. Ignora la deriva termica tipica dei sensori MPU6050.</li>
  <li><strong>Modalità Raffica (Burst 5x):</strong> Un singolo colpo fisico invia una sequenza di 50 impulsi (frecce direzionali) ogni 50ms per una sterzata fluida in gioco.</li>
  <li><strong>Bassa Sensibilità Calibrata:</strong> Ottimizzato per filtrare le vibrazioni del rullo e i movimenti involontari durante il fuorisella.</li>
  <li><strong>Feedback Visivo:</strong> 2 LED integrati per confermare l'invio dei comandi a destra e sinistra.</li>
</ul>

<h2>🛠️ Hardware Necessario</h2>
<table width="100%">
  <tr>
    <th>Componente</th>
    <th>Quantità</th>
    <th>Funzione</th>
  </tr>
  <tr>
    <td><b>ESP32-WROOM-32</b></td>
    <td>1</td>
    <td>Microcontrollore con Bluetooth HID</td>
  </tr>
  <tr>
    <td><b>MPU6050 (GY-521)</b></td>
    <td>1</td>
    <td>Accelerometro + Giroscopio</td>
  </tr>
  <tr>
    <td><b>LED</b></td>
    <td>2</td>
    <td>Feedback SX (Verde) / DX (Rosso)</td>
  </tr>
  <tr>
    <td><b>Resistenze 220Ω</b></td>
    <td>2</td>
    <td>Protezione LED</td>
  </tr>
</table>

<h2>🔌 Schema di Collegamento</h2>
<pre>
<b>MPU6050</b>      <b>ESP32 Pin</b>
VCC     -->  3.3V
GND     -->  GND
SCL     -->  GPIO 22
SDA     -->  GPIO 21
AD0     -->  GND (Indirizzo 0x68)

<b>LED</b>          <b>ESP32 Pin</b>
LED SX  -->  GPIO 18
LED DX  -->  GPIO 19
</pre>

<h2>💻 Requisiti Software</h2>
<p>Il progetto è testato con <b>Arduino ESP32 Core v3.0.7</b> o superiore (Gennaio 2026). Richiede le seguenti librerie:</p>
<ul>
  <li><a href="github.com">MPU6050_light</a> (rfetick)</li>
  <li><a href="github.com">ESP32-BLE-Keyboard</a> (T-vK)</li>
</ul>

<blockquote>
  <b>⚠️ NOTA PER IL 2026:</b> Se ricevi l'errore <i>"cannot convert std::string to String"</i>, correggi il file <code>BleKeyboard.cpp</code> aggiungendo <code>.c_str()</code> alle chiamate <code>init()</code> e <code>setValue()</code>.
</blockquote>

<h2>🚀 Guida Rapida</h2>
<ol>
  <li>Carica lo sketch tramite Arduino IDE selezionando <b>"ESP32 Dev Module"</b>.</li>
  <li>Fissa il sensore al centro del manubrio in modo stabile.</li>
  <li>All'accensione, tieni il manubrio fermo per 2 secondi (calibrazione automatica).</li>
  <li>Associa il dispositivo al PC/Tablet cercando <b>"MyWhoosh Steering"</b> nelle impostazioni Bluetooth.</li>
  <li>In gioco, dai un colpo deciso a sinistra o destra per cambiare traiettoria.</li>
</ol>

<h2>⚙️ Parametri Personalizzabili</h2>
<p>Puoi regolare la sensibilità modificando queste righe nel codice:</p>
<code style="background: #333; color: #fff; padding: 5px;">#define SOGLIA_VELOCITA 80.0</code> &nbsp; <i>(Aumenta per meno sensibilità)</i><br>
<code style="background: #333; color: #fff; padding: 5px;">#define INTERVALLO_RAFFICA 200</code> &nbsp; <i>(Velocità della raffica in ms)</i>

<hr>

<p align="center">
  Sviluppato per la community dei ciclisti virtuali. <br>
  Distribuito sotto Licenza MIT.
</p>
