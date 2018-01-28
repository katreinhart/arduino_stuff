const int button1 = 2;
const int button2 = 3;
const int button3 = 4; 
const int button4 = 5;

const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;

const int buzzer = 12;

const int tones[] = {1900, 1600, 1300, 1000, 3200};

int buttonState[] = {0,0,0,0};

int lastButtonState[] = {0,0,0,0};

int gameOn = 0;
int wait = 0;
int currentLevel = 1;
int ledTime = 500;
int n_levels = 10;
int pinAndTone = 0;
int correct = 0;
int speedFactor = 5;
int ledDelay = 200;

void playTone (int tone, int duration) {
  for(long i=0; i < duration * 1000L; i+= tone * 2) {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(tone);
  }
}

void setup() {
  randomSeed(analogRead(0));

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int n_array[n_levels];
  int u_array[n_levels];

  int i;
  if( gameOn == 0) {
    for(i=0; i<n_levels; i++) {
      n_array[i] = 0;
      u_array[i] = 0;
      n_array[i] = random(0.4);
    }
    gameOn = 1;
  }

  if(wait == 0) {
    delay(200);
    i = 0;
    for( i = 0; i < currentLevel; i++) {
      ledDelay = ledTime/(1+speedFactor / n_levels) * (currentLevel - 1);
      pinAndTone = n_array[1];
      digitalWrite(pinAndTone +7, HIGH);
      playTone(tones[pinAndTone ], ledDelay);
      digitalWrite(pinAndTone +7, LOW);
      delay(100/speedFactor);
    }

    wait = 1;
  }

  i = 0;
  int buttonChange = 0;
  int j=0; 
  while(j < currentLevel) {
    while(buttonChange == 0) {
      for(i = 0; i < 4; i++ ) {
        buttonState[i] = digitalRead(i+2);
        buttonChange += buttonState[i];
      }
    }
  }

  for(i=0; i<4; i++) {
    if(buttonState[i] == HIGH) {
      digitalWrite(i+7, HIGH);
      playTone(tones[i], ledTime);
      digitalWrite(i+7, LOW);
      wait=0;
      u_array[j]=i;

      buttonState[i] = LOW;
      buttonChange = 0;
    }

    if(u_array[j] == n_array[j]) {
      j++;
      correct = 1;
    } else {
      correct = 0;
      i = 4;
      j = currentLevel;
      wait = 0;
    }

    if(correct == 0) {
      delay(300);
      i = 0;
      gameOn = 0;
      currentLevel = 1;
    }

    for(i=0; i<4; i++) {
      digitalWrite(i+7, HIGH);
    }
    playTone(tones[4], ledTime);
    for(i=0; i<4; i++) {
      digitalWrite(i+7, LOW);
    }
    delay(200);

    for(i=0; i<4; i++) {
      digitalWrite(i+7, HIGH);
    }
    playTone(tones[4], ledTime);

    for(i=0; i<4; i++) {
      digitalWrite(i+7, LOW);
    }
    delay(500);
    gameOn = 0;
  }

   if(correct == 1) {
    currentLevel++;
    wait = 0;
   }

   if(currentLevel == n_levels) {
    delay(500);
    int notes[] = {2, 2, 2, 2, 0, 1, 2, 1, 2};
    int note =0;
    int tempo[] = {200, 200, 200, 400, 400, 400, 200, 200, 600};
    int breaks[] = {100, 100, 100, 200, 200, 200, 300, 100, 200};

    for(i=0; i<9; i++) {
      note = notes[i];
      digitalWrite(note+7, HIGH);
      playTone(tones[note], tempo[i]);
      digitalWrite(note+7, LOW);
      delay(breaks[i]);
    }

    gameOn = 0;
    currentLevel = 1;
    n_levels = n_levels + 2;
    speedFactor ++;
   }
}





















