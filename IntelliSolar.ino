#include <Wire.h>
#include <Servo.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- DHT ----------
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---------- Servo ----------
Servo servo;

// ---------- Pins ----------
const int leftLDR = A0;
const int rightLDR = A1;

#define SERVO_PIN 9
#define BUZZER_PIN 8
#define RELAY_PIN 7

// ---------- Variables ----------
int servoAngle = 90;
const int threshold = 50;

float previousTemp = -100;

bool buzzerDone = false;

void setup()
{
  Serial.begin(9600);

  servo.attach(SERVO_PIN);
  servo.write(servoAngle);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);     // Relay OFF (Active LOW)

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED Failed");
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop()
{
  // =========================
  // Solar Tracking
  // =========================

  int left = analogRead(leftLDR);
  int right = analogRead(rightLDR);

  if (left > right + threshold)
  {
    servoAngle--;

    if (servoAngle < 60)
      servoAngle = 60;

    servo.write(servoAngle);
  }

  else if (right > left + threshold)
  {
    servoAngle++;

    if (servoAngle > 120)
      servoAngle = 120;

    servo.write(servoAngle);
  }

  // =========================
  // Temperature
  // =========================

  float temp = dht.readTemperature();

  if (!isnan(temp))
  {
    // Update OLED only if temperature changes

    if (temp != previousTemp)
    {
      display.clearDisplay();

      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);

      display.setCursor(0,0);
      display.println("Temp");

      display.setCursor(0,25);
      display.print(temp);
      display.print((char)247);
      display.println("C");

      display.display();

      Serial.print("Temperature : ");
      Serial.print(temp);
      Serial.println(" C");

      previousTemp = temp;
    }

    // =========================
    // Relay + Buzzer
    // =========================

    if (temp >= 25)
    {
      digitalWrite(RELAY_PIN, LOW);     // Relay ON

      if (!buzzerDone)
      {
        tone(BUZZER_PIN, 1000);
        delay(500);
        noTone(BUZZER_PIN);

        buzzerDone = true;
      }
    }
    else
    {
      digitalWrite(RELAY_PIN, HIGH);    // Relay OFF

      buzzerDone = false;
    }
  }

  delay(100);
}