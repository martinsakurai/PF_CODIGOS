#include <WiFi.h>
#include <HTTPClient.h>

// ✅ Tus credenciales WiFi
const char* ssid = "MECA-IoT";
const char* password = "IoT$2025";

// ✅ URL de tu servidor Node.js (ajusta IP/puerto)
const char* serverUrl = "https://servidor-compostera.onrender.com/lectura"; // CAMBIA por tu IP local o dominio
const int pinFc28 = 32;
int lecturaFC28;
float humedadSuelo;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(pinFc28, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    lecturaFC28 = analogRead(pinFc28);
    humedadSuelo = map(lecturaFC28, 0, 4095, 100, 0);

    // ✅ Datos de ejemplo — aquí pondrás los valores reales de tus sensores
    String json = 
      R"({
        "temperatura": 30.5,
        "humedad": 60,
        "ph": 7.2,
        "humedadSuelo": )" + String(humedadSuelo) + R"(
      })";

    int httpResponseCode = http.POST(json);

    Serial.print("Código de respuesta: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println(payload);

    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(10000); // Espera 10 segundos
}