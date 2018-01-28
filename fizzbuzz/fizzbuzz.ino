const int fizz = 12;
const int buzz = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(fizz, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Starting fizzbuzz");

  for(int i=1; i<=100; i++){
    if(i % 5 == 0 && i % 3 == 0){
      digitalWrite(fizz, HIGH);
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(fizz, LOW);
      digitalWrite(buzz, LOW);
    } else if (i % 5 == 0) {
      digitalWrite(fizz, HIGH);
      delay(500);
      digitalWrite(fizz, LOW);
    } else if (i % 3 == 0) {
      digitalWrite(buzz, HIGH);
      delay(500);
      digitalWrite(buzz, LOW);
    } else {
      Serial.println(i);
    }
  }
}
