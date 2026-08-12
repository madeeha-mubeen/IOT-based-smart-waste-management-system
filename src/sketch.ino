#define BLYNK_TEMPLATE_ID "TMPL3Ee-3m9ow"
#define BLYNK_TEMPLATE_NAME "IoT Based Smart Waste Management System"
#define BLYNK_AUTH_TOKEN "rWJkD5-TglvcFW5qESVtxgb0Pyxao_gT"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Pins
#define trigPin1 13    // Object detection ultrasonic
#define echoPin1 14
#define trigPin2 18    // reserved (not used in simulation)
#define echoPin2 19

// Blynk Virtual pins
#define V_OBJ_DIST V1     // distance from object sensor
#define V_FILL_LVL V2     // simulated fill percentage
#define V_LOCATION V5     // Location datastream (Map widget)

// Bin info
const String TRUCK_1_NUMBER = "+919911223344";
const String TRUCK_2_NUMBER = "+918855667788";
const String DUSTBIN_ID = "Dustbin_No1";
const double BIN_LAT = 12.9716;
const double BIN_LON = 77.5946;

LiquidCrystal_I2C lcd(0x27, 20, 4);

// alert / state flags
bool alert75Sent = false;
bool alert95Sent = false;
bool overflowPrinted = false;
bool waitingForCollection = false;

// simulated fill percentage 0–100
int simFill = 0;
unsigned long lastFillUpdate = 0;   // last time value changed
unsigned long holdDuration   = 0;   // ms to keep current value
unsigned long collectionStartTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  Serial.print("Connecting WiFi...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Dustbin");
  lcd.setCursor(0, 1);
  lcd.print(DUSTBIN_ID);
  lcd.setCursor(0, 2);
  lcd.print("Loc: ");
  lcd.print(BIN_LAT, 4);
  lcd.print(",");
  lcd.print(BIN_LON, 4);

  Blynk.begin(auth, ssid, pass);
  delay(3000);

  // random seed so simulation looks different every run
  long seed = micros() ^ WiFi.RSSI();
  randomSeed(seed);

  simFill = 0;
  lastFillUpdate = millis();
  holdDuration   = random(1500, 4000); // 1.5–4 s hold time

  // send fixed location once so Map widget shows the bin
  Blynk.virtualWrite(V_LOCATION, BIN_LON, BIN_LAT);
}

void loop() {
  Blynk.run();

  float objDistance = measureDistance(trigPin1, echoPin1);
  unsigned long now = millis();

  // 1) Simulated fill: random dwell + random step
  if (!waitingForCollection && simFill < 100) {
    if (now - lastFillUpdate >= holdDuration) {
      lastFillUpdate = now;

      int step = random(1, 11); // 1–10 %
      simFill += step;
      if (simFill > 100) simFill = 100;

      // new random dwell time for this value
      holdDuration = random(1500, 4000);
    }
  }

  // 2) Overflow message at 100%
  if (simFill == 100 && !overflowPrinted) {
    Serial.println();
    Serial.println("***** WARNING: BIN OVERFLOW *****");
    Serial.println("Bin has reached 100% capacity. Garbage is overflowing.");
    Serial.print("Location: ");
    Serial.print(BIN_LAT, 4);
    Serial.print(",");
    Serial.println(BIN_LON, 4);
    Serial.println("*********************************");
    Serial.println();
    overflowPrinted = true;
  }

  // 3) After 95% alert, start timer simulating truck coming
  if (alert95Sent && !waitingForCollection) {
    waitingForCollection = true;
    collectionStartTime = now;
  }

  // 4) After 8 seconds, simulate collection and reset
  if (waitingForCollection && (now - collectionStartTime > 8000)) {
    simulateCollection();
  }

  updateDisplay(objDistance, simFill);
  updateBlynk(objDistance, simFill);
  checkAlerts(simFill);

  delay(300);
}

float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 25.0;
  return duration * 0.034 / 2;
}

void updateDisplay(float objDist, int fillPct) {
  lcd.clear();

  // line 0: bin ID
  lcd.setCursor(0, 0);
  lcd.print(DUSTBIN_ID);

  // line 1: fill %
  lcd.setCursor(0, 1);
  lcd.print("Fill: ");
  lcd.print(fillPct);
  lcd.print("%");

  // line 2: status
  lcd.setCursor(0, 2);
  if (fillPct < 50)       lcd.print("Status: OK       ");
  else if (fillPct < 75)  lcd.print("Status: Moderate ");
  else if (fillPct < 95)  lcd.print("Status: Almost   ");
  else if (fillPct < 100) lcd.print("Status: Critical ");
  else                    lcd.print("Status: OVERFLOW ");

  // line 3: fixed location
  lcd.setCursor(0, 3);
  lcd.print("Loc:12.9716,77.5946");

  // Serial output: fill level in cm + percentage
  const float BIN_DEPTH_CM = 40.0;           // bin height in cm
  float fillHeightCm = (fillPct / 100.0) * BIN_DEPTH_CM;

  Serial.print("Fill level: ");
  Serial.print(fillHeightCm, 1);
  Serial.print(" cm | Fill: ");
  Serial.print(fillPct);
  Serial.println(" %");
}

void updateBlynk(float objDist, int fillPct) {
  Blynk.virtualWrite(V_OBJ_DIST, objDist);
  Blynk.virtualWrite(V_FILL_LVL, fillPct);
}

void checkAlerts(int fillPercentage) {
  if (fillPercentage >= 75 && !alert75Sent) {
    sendAlert75(fillPercentage);
    alert75Sent = true;
  }

  if (fillPercentage >= 95 && !alert95Sent) {
    sendAlert95(fillPercentage);
    alert95Sent = true;
  }
}

// Simulate truck emptied the bin and restart from 0
void simulateCollection() {
  Serial.println();
  Serial.println("##### GARBAGE COLLECTED #####");
  Serial.println("Garbage truck has emptied the bin.");
  Serial.println("Bin is now EMPTY (0%). Filling cycle restarts.");
  Serial.println("##############################");
  Serial.println();

  simFill = 0;
  alert75Sent = false;
  alert95Sent = false;
  overflowPrinted = false;
  waitingForCollection = false;
  lastFillUpdate = millis();
  holdDuration   = random(1500, 4000);
}

void sendAlert75(int fillLevel) {
  String mapsLink = "https://maps.google.com/?q=" +
                    String(BIN_LAT, 6) + "," + String(BIN_LON, 6);
  String message  = DUSTBIN_ID + " 75% FULL (" + String(fillLevel) +
                    "%). Nearest garbage collector (Truck 1) requested. " +
                    mapsLink;

  Serial.println();
  Serial.println("--- ALERT: 75% LEVEL REACHED ---");
  Serial.println("Truck 1 is notified to collect this bin.");
  Serial.print("Fill: ");
  Serial.print(fillLevel);
  Serial.println(" %");
  Serial.print("Maps: ");
  Serial.println(mapsLink);
  Serial.println("--------------------------------");
  Serial.println();

  Blynk.logEvent("alert_75", message);
}

void sendAlert95(int fillLevel) {
  String mapsLink = "https://maps.google.com/?q=" +
                    String(BIN_LAT, 6) + "," + String(BIN_LON, 6);
  String message  = "Critical: " + DUSTBIN_ID + " " + String(fillLevel) +
                    "% FULL. Immediate collection needed. " + mapsLink;

  Serial.println();
  Serial.println("=== FINAL ALERT: 95% LEVEL ===");
  Serial.println("All available garbage collectors (Truck 1 & 2) notified.");
  Serial.print("Fill: ");
  Serial.print(fillLevel);
  Serial.println(" %");
  Serial.print("Maps: ");
  Serial.println(mapsLink);
  Serial.println("================================");
  Serial.println();

  Blynk.logEvent("alert_95", message);
}
