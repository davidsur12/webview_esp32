#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//#include <"pagina.h">

const char *ssid = "ESP32-AP";
const char *password = "123456789";      // Añade ibreria

AsyncWebServer server(80);
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

const int btn1 = 21 ;

String paginaHTML = R"(
<!DOCTYPE html>
<html>
<head>
  <title>Mi Página Web ESP32</title>
</head>
<body>
  <h1>Hola desde ESP32</h1>
</body>
</html>
)";
  
void setup() {
    tft.begin();
  tft.setRotation(0);  // landscape

  tft.fillScreen(TFT_BLACK);

  // Swap the colour byte order when rendering
  tft.setSwapBytes(true);


pinMode(btn1, INPUT_PULLUP);//boton1

    Serial.begin(115200);
Serial.println("Punto de acceso iniciado");
  // Configurar el ESP32 como punto de acceso
  WiFi.softAP(ssid, password);

  Serial.println("Punto de acceso iniciado");
  IPAddress ip = WiFi.softAPIP();
  Serial.print("Dirección IP del AP: ");
  Serial.println(ip);
  // Rutas del servidor web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", paginaHTML);
  });

  // Iniciar el servidor
  server.begin();


}

void loop() {

   int estadoBoton = digitalRead(btn1);

  // Imprime el estado del botón en el puerto serie
  Serial.println(estadoBoton);

  delay(100);

}
