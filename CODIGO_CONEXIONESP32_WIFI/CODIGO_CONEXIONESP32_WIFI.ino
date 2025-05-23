#include <WiFi.h>  

const char nombreRed = "TU_SSID";       
const char claveRed  = "TU_CONTRASEÑA"; 

void setup() {
  Serial.begin(115200);  

  WiFi.begin(nombreRed, claveRed);

  Serial.print("Conectando a WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());  
}

void loop() {

}
