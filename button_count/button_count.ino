const int btn_pin = 2;
const int led_pin = 6;

int count = 0;
int btn_prev;

void setup() {
  // configure pins
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);

  Serial.begin(9600);
  // set initial LED state
  digitalWrite(led_pin, LOW);
}

void loop() {
  int btn_state;

  // read button state
  btn_state = digitalRead(btn_pin);

  // flash LED on rising edge 
  if ((btn_prev == LOW) && (btn_state == HIGH)) {
    count ++;
    Serial.println(count);
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    
  }

  // remember button state
  btn_prev = btn_state;
}
