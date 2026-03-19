#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ135_PIN A0
#define BUZZER 8

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(MQ135_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int airQuality = analogRead(MQ135_PIN);
  
  Serial.print("Air Quality: "); Serial.println(airQuality);
  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C");
  Serial.print("  Humidity: "); Serial.println(humidity);
  
  // OLED Display
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Air Quality: "); display.println(airQuality);
  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Humidity: "); display.print(humidity); display.println(" %");
  
  // Warning condition
  if (airQuality > 300) {
    display.setTextColor(WHITE);
    display.println("  Pollution High!");
    digitalWrite(BUZZER, HIGH);
  } else {
    display.println("Air OK :)");
    digitalWrite(BUZZER, LOW);
  }
  
  display.display();
  delay(2000);
}
