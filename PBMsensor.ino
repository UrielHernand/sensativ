
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>



#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   


#define FIREBASE_HOST "sensative1-d550f-default-rtdb.firebaseio.com"  // URL de la BD, sin http:// 
#define FIREBASE_AUTH "53R3LmxdnMlEFOfEIrM7qUmQUxUYB7ZZx2R4uTsq"  // El secreto de la BD

// Conexión WiFi Alumnos_Biblioteca AlumnoUTT2015
#define WIFI_SSID "Alumnos_Biblioteca"
#define WIFI_PASSWORD "AlumnoUTT2015"


//  Variables
const int PulseWire = A0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 5;
// Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
int beatss = 0;


int sensorValue = analogRead(A0);

int resetBot = 16; //D0 pin de RST.




PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

bool measureBPM = false;  // Variable para habilitar/deshabilitar la medición de BPM
bool measurementStarted = false;  // Variable para realizar un seguimiento del estado de la medición
unsigned long startTime = 0;  // Tiempo de inicio
int beatCount = 0;  // Contador de latidos
bool antCommand = false;
void setup() {
  Serial.begin(115200);   // For Serial Monitor
  //Conexión Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando: ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado: ");
  Serial.println(WiFi.localIP());
  //Inicia la conexión a la BD
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Configure the PulseSensor object, by assigning our variables to it.
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  Serial.println("SENSOR DE PULSO CARDIACO - SENSATIVE💖 !");
}



void loop() {

  if (Firebase.failed()) {
    Serial.println("Error en la conexión:");
    Serial.print(Firebase.error());
    delay(1000);
    pinMode(resetBot, OUTPUT);
    delay(2000);
    pinMode(resetBot, INPUT);
    return;
  }






  bool command = Firebase.getBool("medir/medir"); // Lee el comando desde firebase
  if ( command !=  antCommand ) {
    antCommand = command;
    if (command == true) {
      if (!measurementStarted) {
        measureBPM = true;
        startTime = millis();
        beatCount = 0;
        measurementStarted = true;
        Serial.println("Iniciando medición del BPM por minuto...");
      }
    } else if (command == false) {
      measureBPM = false;
      measurementStarted = false;
      Serial.println("Deteniendo medición del BPM por minuto.");
    }
  }
  if (measureBPM) {
    int myBPM = pulseSensor.getBeatsPerMinute();  // Obtener el BPM en cada iteración del bucle
    beatss = analogRead(PulseWire);
    Serial.println(beatss);
    if (beatss > Threshold ) {  // Si se detectó un latido
      beatCount++;  // Incrementar el contador de latidos
    }
    if (millis() - startTime >= 59000) {  // Si ha transcurrido un minuto completo (60000 milisegundos)
      Serial.println("BPM: ");  // Imprimir la etiqueta "BPM: "
      Serial.println(myBPM);  // Imprimir el valor del BPM en el monitor serial
      // Si se detectaron latidos durante el minuto, mostrar el contador
      Serial.print("Latidos x: ");
      Serial.println(beatCount);
      int firebaseCount = beatCount ;
      Firebase.setInt("pul+so", firebaseCount);
      // Reiniciar el tiempo de inicio y el contador de latidos
      startTime = millis();
      beatCount = 0;
    }
  }

  delay(10);

}
