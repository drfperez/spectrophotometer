const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int ldrPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int wavelength = 380; // Start at 380nm
  while (wavelength <= 780) { // Scan up to 780nm
    // Convert wavelength to RGB values
    int redValue = getRGBValue(wavelength, 'R');
    int greenValue = getRGBValue(wavelength, 'G');
    int blueValue = getRGBValue(wavelength, 'B');

    // Set RGB LED values
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);

    // Read LDR sensor value and print to serial monitor
    int ldrValue = analogRead(ldrPin);
    Serial.print("Wavelength: ");
    Serial.print(wavelength);
    Serial.print("nm, LDR Value: ");
    Serial.println(ldrValue);

    wavelength++; // Increment wavelength
    delay(100); // Delay for stability
  }
}

// Convert wavelength to RGB values
int getRGBValue(int wavelength, char color) {
  double gamma = 0.8;
  double factor = 0.1;
  double R, G, B;
  if (wavelength < 380 || wavelength > 780) {
    return 0;
  }
  if (wavelength >= 380 && wavelength < 440) {
    R = -(wavelength - 440) / (440 - 380);
    G = 0;
    B = 1;
  } else if (wavelength >= 440 && wavelength < 490) {
    R = 0;
    G = (wavelength - 440) / (490 - 440);
    B = 1;
  } else if (wavelength >= 490 && wavelength < 510) {
    R = 0;
    G = 1;
    B = -(wavelength - 510) / (510 - 490);
  } else if (wavelength >= 510 && wavelength < 580) {
    R = (wavelength - 510) / (580 - 510);
    G = 1;
    B = 0;
  } else if (wavelength >= 580 && wavelength < 645) {
    R = 1;
    G = -(wavelength - 645) / (645 - 580);
    B = 0.0;
  } else if (wavelength >= 645 && wavelength < 781) {
    R = 1;
    G = 0;
    B = 0;
  }
  if (color == 'R') {
    return 255 * pow(R, gamma);
  } else if (color == 'G') {
    return 255 * pow(G, gamma);
  } else if (color == 'B') {
    return 255 * pow(B, gamma);
  }
}
