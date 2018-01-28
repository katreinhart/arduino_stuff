const int increment_btn_pin = 2;
const int decrement_btn_pin = 4;
const int debounce_delay = 50;

// globals
int counter = 0;
int increment_btn_state = HIGH;
int increment_btn_prev = HIGH;

int decrement_btn_state = HIGH;
int decrement_btn_prev = HIGH;

unsigned long increment_last_debounce_time = 0;
unsigned long decrement_last_debounce_time = 0;

void setup() {
  pinMode(increment_btn_pin, INPUT_PULLUP);
  pinMode(decrement_btn_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int increment_btn_read = digitalRead(increment_btn_pin);
  int decrement_btn_read = digitalRead(decrement_btn_pin);

  // Remember when btn changed states 
  if (increment_btn_read != increment_btn_prev) {
    increment_last_debounce_time = millis();
  }
  // Remember when btn changed states 
  if (decrement_btn_read != decrement_btn_prev) {
    decrement_last_debounce_time = millis();
  }

  // wait before chekcing again
  if ( millis() > (increment_last_debounce_time + debounce_delay)) {
    if( increment_btn_read != increment_btn_state) {
      increment_btn_state = increment_btn_read;
      if (increment_btn_state == LOW) {
        counter++;
        Serial.println(counter);
      }
    }
  }

  if ( millis() > (decrement_last_debounce_time + debounce_delay)) {
    if( decrement_btn_read != decrement_btn_state) {
      decrement_btn_state = decrement_btn_read;
      if (decrement_btn_state == LOW) {
        counter--;
        Serial.println(counter);
      }
    }
  }

  // Remember previous state
  increment_btn_prev = increment_btn_read;
  decrement_btn_prev = decrement_btn_read;
}
