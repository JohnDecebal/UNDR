#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <EEPROM.h>

const char* ssid = "UNDR AUTO";
const char* password = "undrauto";

WebServer server(80);

// Pin assignments
const int STEPPER1_PUL_PIN = 17;
const int STEPPER1_DIR_PIN = 18;
const int STEPPER2_PUL_PIN = 3;
const int STEPPER2_DIR_PIN = 9;
const int ENABLE_PIN_1 = 8;
const int ENABLE_PIN_2 = 10;
const int BUTTON_PIN = 11;

AccelStepper stepper1(1, STEPPER1_PUL_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(1, STEPPER2_PUL_PIN, STEPPER2_DIR_PIN);

// Variables
int lastButtonState = 0;
int maxSpeed1; // Variable to store the maximum speed for stepper1
int maxSpeed2; // Variable to store the maximum speed for stepper2

// EEPROM addresses
const int ADDR_RPM = 0;
const int ADDR_REVS = 2;
const int ADDR_BASKET_DEPTH = 4;
const int ADDR_SPEED = 6;
const int ADDR_DIRECTION = 8;

// History
const int MAX_HISTORY = 25;

struct HistoryItem {
  unsigned long id;
  int rpm;
  int revs;
  int depth;
  int speed;
  int direction;
};

HistoryItem history[MAX_HISTORY];
int historyCount = 0;

// EEPROM functions
void EEPROMWriteInt(int address, int value) {
  byte low = value & 0xFF;
  byte high = (value >> 8) & 0xFF;
  EEPROM.write(address, low);
  EEPROM.write(address + 1, high);
  EEPROM.commit();
}

int EEPROMReadInt(int address) {
  byte low = EEPROM.read(address);
  byte high = EEPROM.read(address + 1);
  return (high << 8) | low;
}

// Motor control functions
void liftPortafilter(int basketDepthValue, int speedValue) {
  maxSpeed1 = speedValue * (800 / 60); // Assuming 800 steps per revolution
  stepper1.setCurrentPosition(0);
  stepper1.setMaxSpeed(maxSpeed1);
  stepper1.setAcceleration(800 * (speedValue / 60));
  stepper1.runToNewPosition(40*basketDepthValue);
}

void spinDistributor(int rpmValue, int revsValue, int directionValue) {
  maxSpeed2 = rpmValue * (3200 / 60); // Assuming 3200 steps per revolution
  stepper2.setCurrentPosition(0);
  stepper2.setMaxSpeed(maxSpeed2);
  stepper2.setAcceleration(3200 * (rpmValue / 60));
  int targetPosition = directionValue == 0 ? 3200 * revsValue : -3200 * revsValue;
  stepper2.runToNewPosition(targetPosition);
}

void lowerPortafilter() {
  stepper1.runToNewPosition(0);
}

String css() {
  String styles = "<style>";
  styles += "body { background-color: #000; color: #fff; font-family: 'Inter', sans-serif; margin: 0; padding: 0; min-height: 100vh; display: flex; flex-direction: column; }";
  styles += ".container { max-width: 800px; margin: 0 auto; padding: 20px; flex-grow: 1; display: flex; flex-direction: column; justify-content: center; }";
  styles += "h1 { text-align: center; margin-top: 0; }";
  styles += "form { margin-top: 30px; }";
  styles += "label { display: block; margin-bottom: 10px; }";
  styles += "input[type='number'], select { width: 100%; padding: 8px; background-color: #fff; color: #000; border: none; border-radius: 4px; box-sizing: border-box; }";
  styles += "input[type='submit'], input[type='button'] { display: block; width: 100%; padding: 10px; margin-top: 20px; background-color: #fff; color: #000; border: none; border-radius: 4px; cursor: pointer; }";
  styles += "table { width: 100%; border-collapse: collapse; }";
  styles += "th, td { padding: 8px; text-align: left; border-bottom: 1px solid #fff; }";
  styles += "@media screen and (max-width: 600px) {";
  styles += "input[type='number'], select { padding: 12px; }";
  styles += "input[type='submit'], input[type='button'] { padding: 12px; }";
  styles += "}";
  styles += "</style>";
  return styles;
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<title>UNDR AUTO</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;700&display=swap' rel='stylesheet'>";
  html += css();
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>UNDR AUTO</h1>";
  html += "<form method='POST' action='/update'>";
  html += "<label for='rpm'>RPM:</label>";
  html += "<input type='number' id='rpm' name='rpm' value='" + String(EEPROMReadInt(ADDR_RPM)) + "' required>";
  html += "<label for='revs'>Revolutions:</label>";
  html += "<input type='number' id='revs' name='revs' value='" + String(EEPROMReadInt(ADDR_REVS)) + "' required>";
  html += "<label for='depth'>Basket Depth:</label>";
  html += "<input type='number' id='depth' name='depth' value='" + String(EEPROMReadInt(ADDR_BASKET_DEPTH)) + "' required>";
  html += "<label for='speed'>Speed:</label>";
  html += "<input type='number' id='speed' name='speed' value='" + String(EEPROMReadInt(ADDR_SPEED)) + "' required>";
  html += "<label for='direction'>Rotation Direction:</label>";
  html += "<select id='direction' name='direction'>";
  html += "<option value='0'";
  html += (EEPROMReadInt(ADDR_DIRECTION) == 0 ? " selected" : "");
  html += ">Clockwise</option>";
  html += "<option value='1'";
  html += (EEPROMReadInt(ADDR_DIRECTION) == 1 ? " selected" : "");
  html += ">Counterclockwise</option>";
  html += "</select>";
  html += "<input type='submit' value='Update'>";
  html += "</form>";
  html += "<form method='POST' action='/start'>";
  html += "<input type='submit' value='Start Distribution'>";
  html += "</form>";
  html += "<form method='GET' action='/manual'>";
  html += "<input type='submit' value='Manual Settings'>";
  html += "</form>";
  html += "<form method='GET' action='/history'>";
  html += "<input type='submit' value='View History'>";
  html += "</form>";
  html += "<form method='GET' action='/simulation'>";
  html += "<input type='submit' value='Simulation'>";
  html += "</form>";
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleUpdate() {
  if (server.hasArg("rpm")) {
    int rpmValue = server.arg("rpm").toInt();
    EEPROMWriteInt(ADDR_RPM, rpmValue);
  }
  if (server.hasArg("revs")) {
    int revsValue = server.arg("revs").toInt();
    EEPROMWriteInt(ADDR_REVS, revsValue);
  }
  if (server.hasArg("depth")) {
    int depthValue = server.arg("depth").toInt();
    EEPROMWriteInt(ADDR_BASKET_DEPTH, depthValue);
  }
  if (server.hasArg("speed")) {
    int speedValue = server.arg("speed").toInt();
    EEPROMWriteInt(ADDR_SPEED, speedValue);
  }
  if (server.hasArg("direction")) {
    int directionValue = server.arg("direction").toInt();
    EEPROMWriteInt(ADDR_DIRECTION, directionValue);
  }
  server.sendHeader("Location", "/");
  server.send(302);
}

void handleStart() {
  int rpmValue = EEPROMReadInt(ADDR_RPM);
  int revsValue = EEPROMReadInt(ADDR_REVS);
  int basketDepthValue = EEPROMReadInt(ADDR_BASKET_DEPTH);
  int speedValue = EEPROMReadInt(ADDR_SPEED);
  int directionValue = EEPROMReadInt(ADDR_DIRECTION);

  // Activate motors
  digitalWrite(ENABLE_PIN_1, LOW);
  digitalWrite(ENABLE_PIN_2, LOW);

  // Wait 0.5 seconds
  delay(500);

  // Lift portafilter
  liftPortafilter(basketDepthValue, speedValue);

  // Spin distributor
  spinDistributor(rpmValue, revsValue, directionValue);

  // Lower portafilter
  lowerPortafilter();

  // Deactivate motors
  digitalWrite(ENABLE_PIN_1, HIGH);
  digitalWrite(ENABLE_PIN_2, HIGH);

  // Add a new history item
  addHistoryItem(rpmValue, revsValue, basketDepthValue, speedValue, directionValue);

  server.sendHeader("Location", "/");
  server.send(302);
}

void handleManual() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<title>UNDR AUTO - Manual Settings</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;700&display=swap' rel='stylesheet'>";
  html += css();
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Manual Settings</h1>";
  html += "<form method='POST' action='/stepper1'>";
  html += "<input type='submit' name='direction' value='Up'>";
  html += "<input type='submit' name='direction' value='Down'>";
  html += "</form>";
  html += "<form method='POST' action='/stepper2'>";
  html += "<input type='submit' name='direction' value='Clockwise'>";
  html += "<input type='submit' name='direction' value='Counter Clockwise'>";
  html += "</form>";
  html += "<form method='GET' action='/'>";
  html += "<input type='submit' value='Back'>";
  html += "</form>";
  html += "</div>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleStepper1() {
  if (server.hasArg("direction")) {
    String direction = server.arg("direction");
    
    // Activate motor 1
    digitalWrite(ENABLE_PIN_1, LOW);
    
    if (direction == "Up") {
      int speedValue = EEPROMReadInt(ADDR_SPEED);
      maxSpeed1 = speedValue * (800 / 60);
      stepper1.setCurrentPosition(0);
      stepper1.setMaxSpeed(maxSpeed1);
      stepper1.setAcceleration(800 * (speedValue / 60));
      stepper1.runToNewPosition(100); // Move stepper 1 up by 100 steps
    } else if (direction == "Down") {
      int speedValue = EEPROMReadInt(ADDR_SPEED);
      maxSpeed1 = speedValue * (800 / 60);
      stepper1.setCurrentPosition(0);
      stepper1.setMaxSpeed(maxSpeed1);
      stepper1.setAcceleration(800 * (speedValue / 60));
      stepper1.runToNewPosition(-100); // Move stepper 1 down by 100 steps
    }
    
    // Deactivate motor 1
    digitalWrite(ENABLE_PIN_1, HIGH);
  }
  server.sendHeader("Location", "/manual");
  server.send(302);
}

void handleStepper2() {
  if (server.hasArg("direction")) {
    String direction = server.arg("direction");
    
    // Activate motor 2
    digitalWrite(ENABLE_PIN_2, LOW);
    
    if (direction == "Clockwise") {
      stepper2.setCurrentPosition(0);
      stepper2.setAcceleration(3200);
      stepper2.runToNewPosition(100); // Spin stepper 2 clockwise by 100 steps
    } else if (direction == "Counter Clockwise") {
      stepper2.setCurrentPosition(0);
      stepper2.setAcceleration(3200);
      stepper2.runToNewPosition(-100); // Spin stepper 2 counter clockwise by 100 steps
    }
    
    // Deactivate motor 2
    digitalWrite(ENABLE_PIN_2, HIGH);
  }
  server.sendHeader("Location", "/manual");
  server.send(302);
}

void handleSimulation() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<title>UNDR AUTO - Simulation</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;700&display=swap' rel='stylesheet'>";
  html += css();
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Simulation</h1>";
  html += "<canvas id='simulationCanvas' width='600' height='600'></canvas>";
  html += "<div>";
  for (int i = 0; i < 6; i++) {
    html += "<label><input type='checkbox' id='slot" + String(i) + "' checked> Slot " + String(i + 1) + "</label><br>";
  }
  html += "</div>";
  html += "<form method='GET' action='/'>";
  html += "<input type='submit' value='Back'>";
  html += "</form>";
  html += "</div>";
  html += "<script>";
  html += "const canvas = document.getElementById('simulationCanvas');";
  html += "const ctx = canvas.getContext('2d');";
  html += "const centerX = canvas.width / 2;";
  html += "const centerY = canvas.height / 2;";
  html += "const outerRadius = 250;";
  html += "const innerRadius = 129;";
  html += "const slotRadius = 17.2;";
  html += "const slotPositions = [";
  html += "  { x: 0, y: -innerRadius + slotRadius },";
  html += "  { x: (innerRadius - slotRadius) * Math.cos(Math.PI / 3), y: -(innerRadius - slotRadius) * Math.sin(Math.PI / 3) },";
  html += "  { x: (innerRadius - slotRadius) * Math.cos(Math.PI / 3), y: (innerRadius - slotRadius) * Math.sin(Math.PI / 3) },";
  html += "  { x: 0, y: innerRadius - slotRadius },";
  html += "  { x: -(innerRadius - slotRadius) * Math.cos(Math.PI / 3), y: (innerRadius - slotRadius) * Math.sin(Math.PI / 3) },";
  html += "  { x: -(innerRadius - slotRadius) * Math.cos(Math.PI / 3), y: -(innerRadius - slotRadius) * Math.sin(Math.PI / 3) },";
  html += "];";
  html += "let angle = 0;";
  html += "function drawSimulation() {";
  html += "  ctx.clearRect(0, 0, canvas.width, canvas.height);";
  html += "  ctx.beginPath();";
  html += "  ctx.arc(centerX, centerY, outerRadius, 0, Math.PI * 2);";
  html += "  ctx.strokeStyle = '#ffffff';";
  html += "  ctx.lineWidth = 2;";
  html += "  ctx.stroke();";
  html += "  ctx.beginPath();";
  html += "  ctx.arc(centerX + outerRadius - innerRadius + innerRadius * Math.cos(angle), centerY + innerRadius * Math.sin(angle), innerRadius, 0, Math.PI * 2);";
  html += "  ctx.strokeStyle = '#ffffff';";
  html += "  ctx.lineWidth = 2;";
  html += "  ctx.stroke();";
  html += "  for (let i = 0; i < slotPositions.length; i++) {";
  html += "    if (document.getElementById('slot' + i).checked) {";
  html += "      const slot = slotPositions[i];";
  html += "      const rotatedSlot = rotatePoint(slot, angle);";
  html += "      ctx.beginPath();";
  html += "      ctx.arc(centerX + outerRadius - innerRadius + rotatedSlot.x, centerY + rotatedSlot.y, slotRadius, 0, Math.PI * 2);";
  html += "      ctx.fillStyle = '#ffffff';";
  html += "      ctx.fill();";
  html += "    }";
  html += "  }";
  html += "  angle += 0.02;";
  html += "  requestAnimationFrame(drawSimulation);";
  html += "}";
  html += "function rotatePoint(point, angle) {";
  html += "  const rotatedX = point.x * Math.cos(angle) - point.y * Math.sin(angle);";
  html += "  const rotatedY = point.x * Math.sin(angle) + point.y * Math.cos(angle);";
  html += "  return { x: rotatedX, y: rotatedY };";
  html += "}";
  html += "drawSimulation();";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void saveHistory() {
  EEPROM.write(512, historyCount);
  for (int i = 0; i < historyCount; i++) {
    EEPROM.put(514 + i * sizeof(HistoryItem), history[i]);
  }
  EEPROM.commit();
}

void loadHistory() {
  historyCount = EEPROM.read(512);
  if (historyCount > MAX_HISTORY) {
    historyCount = MAX_HISTORY;
  }
  for (int i = 0; i < historyCount; i++) {
    EEPROM.get(514 + i * sizeof(HistoryItem), history[i]);
  }
}

void addHistoryItem(int rpm, int revs, int depth, int speed, int direction) {
  if (historyCount >= MAX_HISTORY) {
    for (int i = 1; i < MAX_HISTORY; i++) {
      history[i - 1] = history[i];
    }
    historyCount--;
  }

  HistoryItem newItem = {
    millis(),
    rpm,
    revs,
    depth,
    speed,
    direction
  };
  history[historyCount] = newItem;
  historyCount++;

  saveHistory();
}

void handleHistory() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<title>UNDR AUTO - History</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;700&display=swap' rel='stylesheet'>";
  html += css();
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>History</h1>";
  html += "<table>";
  html += "<thead><tr><th>Timestamp</th><th>RPM</th><th>Revolutions</th><th>Depth</th><th>Speed</th><th>Direction</th></tr></thead>";
  html += "<tbody>";

  for (int i = 0; i < historyCount; i++) {
    html += "<tr>";
    html += "<td>" + String(history[i].id) + "</td>";
    html += "<td>" + String(history[i].rpm) + "</td>";
    html += "<td>" + String(history[i].revs) + "</td>";
    html += "<td>" + String(history[i].depth) + "</td>";
    html += "<td>" + String(history[i].speed) + "</td>";
    html += "<td>" + String(history[i].direction == 0 ? "Clockwise" : "Counterclockwise") + "</td>";
    html += "</tr>";
  }

  html += "</tbody></table>";
  html += "<form method='GET' action='/'>";
  html += "<input type='submit' value='Back'>";
  html += "</form>";
  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  // Initialize EEPROM
  EEPROM.begin(512);

  // Initialize Serial communication
  Serial.begin(115200);

  // Create Wi-Fi access point
  WiFi.softAP(ssid, password);

  // Assign a static IP address to the ESP32-S3
  IPAddress local_IP(192, 168, 1, 100);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Print the IP address of the ESP32-S3
  Serial.print("Access Point IP address: ");
  Serial.println(local_IP);

  // Set up the web server routes
  server.on("/", handleRoot);
  server.on("/update", handleUpdate);
  server.on("/start", handleStart);
  server.on("/manual", handleManual);
  server.on("/stepper1", handleStepper1);
  server.on("/stepper2", handleStepper2);
  server.on("/history", handleHistory);
  server.on("/simulation", handleSimulation);

  // Start the web server
  server.begin();

  stepper1.setMaxSpeed(12000); // Initial value, will be updated based on speed
  stepper2.setMaxSpeed(12000); // Initial value, will be updated based on RPM

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ENABLE_PIN_1, OUTPUT);
  pinMode(ENABLE_PIN_2, OUTPUT);
  digitalWrite(ENABLE_PIN_1, HIGH);
  digitalWrite(ENABLE_PIN_2, HIGH);

  loadHistory();
}

void loop() {
  // Handle web server requests
  server.handleClient();

  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      int rpmValue = EEPROMReadInt(ADDR_RPM);
      int revsValue = EEPROMReadInt(ADDR_REVS);
      int basketDepthValue = EEPROMReadInt(ADDR_BASKET_DEPTH);
      int speedValue = EEPROMReadInt(ADDR_SPEED);
      int directionValue = EEPROMReadInt(ADDR_DIRECTION);

      // Activate motors
      digitalWrite(ENABLE_PIN_1, LOW);
      digitalWrite(ENABLE_PIN_2, LOW);

      // Wait 0.5 seconds
      delay(500);

      // Lift portafilter
      liftPortafilter(basketDepthValue, speedValue);

      // Spin distributor
      spinDistributor(rpmValue, revsValue, directionValue);

      // Lower portafilter
      lowerPortafilter();

      // Deactivate motors
      digitalWrite(ENABLE_PIN_1, HIGH);
      digitalWrite(ENABLE_PIN_2, HIGH);

      // Add a new history item
      addHistoryItem(rpmValue, revsValue, basketDepthValue, speedValue, directionValue);
    }

    delay(50);
  }

  lastButtonState = buttonState;
}