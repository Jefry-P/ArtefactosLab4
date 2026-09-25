#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Configuración de los dos pines táctiles de la ESP32
const int TOUCH_PIN_1 = 4;   // Sensor táctil 1 (T0)
const int TOUCH_PIN_2 = 14;  // Sensor táctil 2 (T6)

// El valor disminuye al tocarlo; menor a 30 significa que está presionado
const int UMBRAL_TOUCH = 950;

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("Error al iniciar la pantalla OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
}

void loop() {

  // Lee el valor de ambos sensores táctiles
  int valorTouch1 = touchRead(TOUCH_PIN_1);
  int valorTouch2 = touchRead(TOUCH_PIN_2);

  display.clearDisplay();

  // Título principal
  display.setTextSize(1);
  display.setCursor(26, 5);
  display.println("ESP32 DUAL TOUCH");

  // Evaluación de los estados
  if(valorTouch1 < UMBRAL_TOUCH && valorTouch2 < UMBRAL_TOUCH){
      display.setCursor(20, 28);
      display.println("BOTON 1 y 2 ACTIVADO");
      display.fillCircle(60, 52, 5, SH110X_WHITE);

  }
  else if (valorTouch1 < UMBRAL_TOUCH) {
    // Si se activa el Botón 1
    display.setCursor(20, 28);
    display.println("BOTON 1 ACTIVADO");
    
    // Dibuja un círculo indicador a la izquierda
    display.fillCircle(20, 52, 5, SH110X_WHITE);
  }
  else if (valorTouch2 < UMBRAL_TOUCH) {
    // Si se activa el Botón 2
    display.setCursor(20, 28);
    display.println("BOTON 2 ACTIVADO");
    
    // Dibuja un círculo indicador a la derecha
    display.fillCircle(105, 52, 5, SH110X_WHITE);
  } else {
    // Si ninguno está siendo tocado
    display.setCursor(20, 28);
    display.println("ESPERANDO TOQUE...");
    
    // Dibuja ambos círculos vacíos (solo contorno) en espera
    display.drawCircle(20, 52, 5, SH110X_WHITE);
    display.drawCircle(105, 52, 5, SH110X_WHITE);
  }

  display.display();

  delay(100);
}
