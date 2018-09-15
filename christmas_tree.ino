#define LEDS_NUMBER 4

#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define BUTTON 7

#define OFF_MODE 0
#define ON_MODE 1
#define BLINK_MODE 2

unsigned int buttonMode = OFF_MODE;

struct Led {
  unsigned long currentMillis;
  unsigned long previousMillis;
  unsigned int interval;
  unsigned int state;
};

Led *leds = new Led[LEDS_NUMBER];

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  for (int i = LED1; i <= LED4; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);   
  }
  randomSeed(analogRead(0));
}

void loop() {
  changeButtonMode();

  switch (buttonMode) {
    case OFF_MODE: 
            turnOffLeds(); 
            break;
    case ON_MODE: 
            turnOnLeds(); 
            break;
    case BLINK_MODE: 
            blinkLeds(); 
            break;
    default: 
            turnOffLeds(); 
            break;
  }
}

void changeButtonMode() {
  if (digitalRead(BUTTON) == LOW) {
    delay(20);
    while (digitalRead(BUTTON) == LOW);
    buttonMode = (buttonMode + 1) % 3;
    delay(20);
  }
}

void turnOffLeds() {
  for (int i = LED1; i <= LED4; i++) {
    digitalWrite(i, LOW);   
  }
}

void turnOnLeds() {
  for (int i = LED1; i <= LED4; i++) {
    digitalWrite(i, HIGH);   
  }
}

void blinkLeds() {
  initLeds();
  int i = 0;
  while (buttonMode == BLINK_MODE) {
    leds[i].currentMillis = millis();
    if (leds[i].currentMillis - leds[i].previousMillis >= leds[i].interval) {
      leds[i].previousMillis = leds[i].currentMillis;
      leds[i].state = revertState(leds[i].state);
      digitalWrite(i + LEDS_NUMBER - 1, leds[i].state);
    }
    i = (i + 1) % LEDS_NUMBER;
    changeButtonMode();
  }
}

void initLeds() {
  for (int i = 0; i < LEDS_NUMBER; i++) {
    leds[i].interval = random(500, 2000);
    leds[i].previousMillis = 0;
    leds[i].state = (random(1000) < 500) ? LOW : HIGH;
    digitalWrite(i + LEDS_NUMBER - 1, leds[i].state);
  }
}

int revertState(unsigned int state) {
  return (state == HIGH) ? LOW : HIGH;
}

