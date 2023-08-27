#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6c93au1kM"
#define BLYNK_TEMPLATE_NAME "Tertanam"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//deskripsi pin
#define DHTPIN D6  
#define DHTTYPE DHT11 
#define trig D8
#define echo D7
#define buzzer D1
#define pump D5

char auth[] = "9sE4MidQJqHFnkqYUD591eWYkRmrOLSQ";
char ssid[] = "Blank";
char pass[] = "";

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pump, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensorSK);
  timer.setInterval(1000L, sendSensorJ);
}

void loop(){ //Perulangan Program
  Blynk.run();
  timer.run();
}

void sendSensorSK() {
  // Baca suhu dan kelembaban dari sensor DHT11
 float h = dht.readHumidity();
 float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;}

  //cetak
  Serial.print("KELEMBAPAN: "); Serial.println(h);
  Serial.print("SUHU      : "); Serial.println(t);

  if (h > 80) {  // Jika kelembaban lebih dari 80%, aktifkan pompa
    digitalWrite(pump, HIGH);
    Serial.println("Menghidupkan pompa air");
    delay(5000);  // Pompa akan aktif selama 5 detik
    digitalWrite(pump, LOW);
    Serial.println("Mematikan pompa air");
  }
  
  Blynk.virtualWrite(V4, t);  // Widget Value Display untuk suhu
  Blynk.virtualWrite(V5, h);     // Widget Value Display untuk kelembaban
}

void sendSensorJ() {
  // Baca jarak dari sensor ultrasonik
  long duration, jarak;
  digitalWrite(trig, LOW);
  delayMicroseconds(3);
  digitalWrite(trig, HIGH);
  delayMicroseconds(12);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  jarak = (duration / 2) / 29.1;
   if (jarak < 30) {  // Jarak kurang dari 30 cm, aktifkan buzzer
    digitalWrite(buzzer, HIGH);
    delay(1000);  // Bunyikan buzzer selama 100 ms
    digitalWrite(buzzer, LOW);
  }

  //cetak
  Serial.print("JARAK: "); Serial.print(jarak); Serial.println(" CM");

  Blynk.virtualWrite(V10, jarak);        // Widget Value Display untuk jarak
}


// #define BLYNK_PRINT Serial

// #define BLYNK_TEMPLATE_ID "TMPL6c93au1kM"
// #define BLYNK_TEMPLATE_NAME "Tertanam"

// #include <DHT.h>
// #include <ESP8266WiFi.h>
// #include <BlynkSimpleEsp8266.h>

// #define DHTPIN D6  
// #define DHTTYPE DHT11 
// #define trig D8
// #define echo D7

// char auth[] = "9sE4MidQJqHFnkqYUD591eWYkRmrOLSQ";
// char ssid[] = "Blank";
// char pass[] = "";

// BlynkTimer timer;
// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600);
//   pinMode(trig, OUTPUT);
//   pinMode(echo, INPUT);
//   Blynk.begin(auth, ssid, pass);
//   dht.begin();
// }

// void loop() {
//   Blynk.run();
//   timer.run();

//   // Baca suhu dan kelembaban dari sensor DHT11
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();
//   Serial.print("SUHU :"); Serial.print(temperature);
//   Serial.print("KELEMBAPAN :"); Serial.print(humidity);

//   // Baca jarak dari sensor ultrasonik
//   long duration, jarak;
//   digitalWrite(trig, LOW);
//   delayMicroseconds(3);
//   digitalWrite(trig, HIGH);
//   delayMicroseconds(12);
//   digitalWrite(trig, LOW);
//   duration = pulseIn(echo, HIGH);
//   jarak = (duration / 2) / 29.1;
//   Serial.print("JARAK: "); Serial.print(jarak); Serial.println(" CM");
//   Blynk.virtualWrite(V10, jarak);        // Widget Value Display untuk jarak
//   Blynk.virtualWrite(V4, temperature);  // Widget Value Display untuk suhu
//   Blynk.virtualWrite(V5, humidity);     // Widget Value Display untuk kelembaban
 
//   delay(1000);
// }