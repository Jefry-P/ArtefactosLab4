const int TOUCH_PIN = 4; // Cambia el número según el pin táctil que uses

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println("PRUEBA SENSOR TOUCH");
  Serial.println();
}

void loop() {

  // Lee el valor del sensor táctil integrado
  int valorTouch = touchRead(TOUCH_PIN); 

  Serial.print("Valor Touch: ");
  Serial.println(valorTouch); // Imprime el valor y da un salto de línea

  delay(200);
}
