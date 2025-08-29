#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>   // Para manejar fecha/hora NTP

// 🔹 Credenciales WiFi
const char* ssid = "Martin's Galaxy S21 FE 5G";
const char* password = "MarSaku07";


// 🔹 URL de tu servidor Node.js
const char* serverUrl = "https://servidor-compostera.onrender.com/lectura";

// 🔹 Prototipo de función
String getTimeStamp();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Iniciando ESP32...");

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP asignada: ");
  Serial.println(WiFi.localIP());

  // Configurar NTP para hora correcta
  configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // UTC
  Serial.println("Sincronizando hora con NTP...");
  delay(2000);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String timestamp = getTimeStamp(); // Obtener timestamp ISO8601

    // JSON con timestamp y valores fijos
    String json = "{";
    json += "\"timestamp\":\"" + timestamp + "\",";
    json += "\"temperatura\":30.5,";
    json += "\"humedad\":60,";
    json += "\"ph\":7.2";
    json += "}";

    Serial.println("Enviando JSON:");
    Serial.println(json);

    int httpResponseCode = http.POST(json);

    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);

    String payload = http.getString();
    Serial.println("Respuesta del servidor:");
    Serial.println(payload);

    http.end();
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(10000); // Espera 10 segundos antes de enviar otra lectura
}

// === Función para obtener timestamp ISO8601 ===
String getTimeStamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Error al obtener tiempo NTP");
    return "1970-01-01T00:00:00"; // fallback
  }
  char buffer[25];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", &timeinfo);
  return String(buffer);
}