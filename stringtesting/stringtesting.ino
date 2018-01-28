void setup() {
  // put your setup code here, to run once:

  char thing1[8] = "hello";
  char thing2[8] = "hello";

  int sLen = strlen(thing1);
  for(int s=0; s<sLen; s++)
  {
     Serial.print("thing1[");
     Serial.print(s);
     Serial.print("] is {");
     Serial.print(thing1[s]);
     Serial.print("} which has an ascii value of ");
     Serial.println(thing1[s], DEC);
  }
  sLen = strlen(thing2);
  for(int s=0; s<sLen; s++)
  {
     Serial.print("thing2[");
     Serial.print(s);
     Serial.print("] is {");
     Serial.print(thing2[s]);
     Serial.print("} which has an ascii value of ");
     Serial.println(thing2[s], DEC);
  }

  if(thing1 == thing2) {
    Serial.println(F("Things are teh same"));
  } else {
    Serial.println(F("Things are not the same"));
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
