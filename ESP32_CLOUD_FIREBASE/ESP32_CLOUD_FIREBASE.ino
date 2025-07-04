#include <WiFi.h>
#include <HTTPClient.h>

// ✅ Tus credenciales WiFi
const char* ssid = "TeleCentro-78e2";
const char* password = "EZM2MGYMGZMN";

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

    // ✅ Datos de ejemplo — aquí pondrás los valores reales de tus sensores
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

  delay(10000); // Espera 10 segundos
}