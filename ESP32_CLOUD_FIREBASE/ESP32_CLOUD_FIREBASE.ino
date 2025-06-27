#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TeleCentro-78e2"; //guardo id y contraseña en dos variables
const char* password = "EZM2MGYMGZMN";

// URL de tu Firestore (ajustá con tu proyecto)
const char* FIREBASE_HOST = "https://firestore.googleapis.com/v1/projects/compostapp-462805/databases/default/documents/sensores"; // defino la URL, creo una coleccion en la cual se van a subir estos datos random

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password); // me conecto a wifi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado.");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(FIREBASE_HOST);  // comienzo una solicitud HTTP usando la URL que defini antes del FireStore
    http.addHeader("Content-Type", "application/json");

    // este es un documento tipo JSON donde los campos "temperatura", "humedad" y "ph" son de tipo "double"
    String json = R"(
      {
        "fields": {
          "temperatura": { "doubleValue": 30.5 },
          "humedad": { "doubleValue": 60 },
          "ph": { "doubleValue": 7.2 }
        }
      }
    )";

    int httpResponseCode = http.POST(json); //envio la peticion con el json al servidor
    Serial.print("Código de respuesta: "); // muestra el codigo de respuesta. lo ideal es que sea 200 o 201, pero si tira -1 o 401 es que hay algo mal
    Serial.println(httpResponseCode);

    http.end(); //finalizo la conexion
  }
}

void loop() {}