const int pinSensor = 32; // Define el pin GPIO32 de ESP32-S3 como la entrada del sensor TMP36

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial
}

void loop() {
  int sensorValue = analogRead(pinSensor); // Lee el valor analógico del sensor
  float voltage = sensorValue * (3.3 / 4095.0); // Convierte el valor a voltaje (ESP32-S3 opera a 3.3V y tiene una resolución ADC de 12 bits)
  float temperatureC = (voltage - 0.5) * 100; // Convierte el voltaje a temperatura en grados Celsius
  
  Serial.print("Temperatura: ");
  Serial.print(temperatureC);
  Serial.println("°C");

  delay(1000); // Espera 1 segundo antes de tomar otra lectura
}
