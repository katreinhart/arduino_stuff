const int red_led_pin = 11;
const int grn_led_pin = 10;
const int yel_led_pin = 9;

void setup() {
  pinMode(red_led_pin, OUTPUT);
  pinMode(grn_led_pin, OUTPUT);
  pinMode(yel_led_pin, OUTPUT);
}

void loop() {
  // Stores the PWM duty cycles
  int brightness_1;
  int brightness_2;
  int brightness_3;

  // Increases LED brightness t different times
  for(int i=0; i < 395; i++){
    // Store brightness levels
    brightness_1 = i;
    brightness_2 = i - 70;
    brightness_3 = i - 140;

    // Limit brightness to between 0 and 255
    if(brightness_1 < 0){
      brightness_1 = 0;
    } else if(brightness_1 > 255){
      brightness_1 = 255;
    }
    
    if(brightness_2 < 0){
      brightness_2 = 0;
    } else if(brightness_2 > 255){
      brightness_2 = 255;
    }
    
    if(brightness_3 < 0){
      brightness_3 = 0;
    } else if(brightness_3 > 255){
      brightness_3 = 255;
    }

    // Set LED brightness levels
    analogWrite(red_led_pin, brightness_1);
    analogWrite(grn_led_pin, brightness_2);
    analogWrite(yel_led_pin, brightness_3);

    delay(20);
  }
}
