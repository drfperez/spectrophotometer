#include <Adafruit_NeoPixel.h>

const int pinSensor = 32; // Sensor TMP36 connectat a GPIO32
const int pinLED = 13; // LED RGB connectat al GPIO13 (aquest pin varia segons la teva placa)

#define NUM_PIXELS 1 // Només tenim un LED RGB
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, pinLED, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Inicialitzar la comunicació serial
  pixels.begin(); // Inicialitzar el LED RGB
}

void loop() {
  for (int colorValue = 0; colorValue <= 255; colorValue++) {
    int sensorValue = analogRead(pinSensor); // Llegir el valor del sensor
    float voltage = sensorValue * (3.3 / 4095.0); // Convertir el valor a voltatge (3.3V, resolució ADC de 12 bits)
    float temperatureC = (voltage - 0.5) * 100; // Convertir el voltatge a temperatura en graus Celsius
    
    // Mapejar la temperatura a valors de color (r, g, b) per a l'LED RGB
    int color = map(temperatureC, 0, 100, 0, 255); // Escalar la temperatura al rang de colors (0-255)
    
    // Encendre l'LED amb el color corresponent
    pixels.setPixelColor(0, Wheel(colorValue)); // Configurar el color de l'LED basat en la variable de bucle
    pixels.show(); // Actualitzar el LED amb el color nou
    
    // Mostrem el valor de color, temps i temperatura per la consola serial
    Serial.print("Color: ");
    Serial.print(colorValue);
    Serial.print(", Temperatura: ");
    Serial.print(temperatureC);
    Serial.println("°C");

    delay(1000); // Esperar 1 segon abans de passar al següent color
  }
}

// Funció per generar un color d'arc iris
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
