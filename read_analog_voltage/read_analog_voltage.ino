const int ain_pin = A0;

int last_read = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(ain_pin);

  if (val != last_read){
    float voltage = val * 5.0 / 1023;

    Serial.println(voltage);
    last_read = val;
  }
}
