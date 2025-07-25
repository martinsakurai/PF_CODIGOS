#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Martin's Galaxy S21 FE 5G";
const char* password = "MarSaku07";

// ✅ URL de tu servidor Node.js (ajusta IP/puerto)
const char* serverUrl = "https://servidor-compostera.onrender.com/lectura"; // CAMBIA por tu IP local o dominio

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

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

    String json = R"(
      {
        "temperatura": 30.5,
        "humedad": 60,
        "ph": 7.2
      }
    )";

    int httpResponseCode = http.POST(json);

    Serial.print("Código de respuesta: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println(payload);

    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(10000); 
}