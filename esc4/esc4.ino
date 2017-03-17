int STATE = 1;
int Arming_Time = 0;
int pin = 6;
//Enter value 1100us to Arm the ESC
//Enter value >=1200us to run Motor but max 2000us
int Pulse = 2000;
bool go = false;

//Arm bldc within void setup()
void setup() {
  //initialize the digital pin as an output
  pinMode(pin, OUTPUT);
  //Will create a 1100s pulse to arm the ESC
  //The pulse will last for 20ms x 500counts = 10,000ms or 10 seconds
  for (Arming_Time = 0; Arming_Time < 500; Arming_Time += 1)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(1100);
    digitalWrite(pin, LOW);
    delay(20 - (Pulse / 2000));
    delayMicroseconds(1100);
    digitalWrite(pin, LOW);
    delay(20 - (Pulse / 1000));
  }
}

//the loop routine runs over and over again forever:
void loop()
{
  for ( Pulse = 1150; Pulse <= 1400; Pulse += 1)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(pin, LOW);
    delay(20 - (Pulse / 1000));
  }
  for (Pulse = 1400; Pulse >= 1150; Pulse -= 1)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(Pulse);
    digitalWrite(pin, LOW);
    delay(20 - (Pulse / 1000));
  }

}


