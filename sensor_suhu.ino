#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const int buzzer = 3;
const float batasSuhu = 30.0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  dht.begin();

  Serial.println("=== MONITORING SUHU ===");
}

void loop() {
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Sensor gagal dibaca!");
    noTone(buzzer);
    delay(2000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  if (suhu >= batasSuhu) {
    tone(buzzer, 1000);
    Serial.println("PERINGATAN! SUHU TINGGI!");
  } else {
    noTone(buzzer);
    Serial.println("Suhu normal.");
  }

  Serial.println("--------------------");
  delay(2000);
}