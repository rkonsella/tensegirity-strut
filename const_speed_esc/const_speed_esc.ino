int STATE=1; //Not used to my knowledge
int Arming_Time=0;
int pin = 9;
//Enter value 1100us to Arm the ESC
//Enter value >=1200us to run Motor but max 2000us
int Pulse=1200; //adjust this parameter for speed >=1191  maybe <=2000

//Arm bldc within void setup()
//What is arming?
//This Arduino code tricks the esc into thinking it is receiving a signal from a
//RC controller like one would use for an RC car or plane or quadcopter.
//As such the first thing the ESC needs to learn is the throttle position
//That's what "arming the esc does"
//You are convincing the esc that you have moved your throttle stick to the bottom
//The bottom is then designated as a 1100 ms pulse from the arduino board.
//Every esc is differrent, for this case, this esc interprets a range of values 
//as throttle stick at the bottom
//Tests currently show that you can set the arm microsecond dely anywhere from 
//800 ms to 1190 ms outside this range the esc knows it is no longer in throttle
//low position.
//adjusting the delay(20-(Pulse/1000)) line appears to have no effect no idea why
//Once it knows where the bottom is, adjusting pulse changes speed 
//no current idea how pwm transfers to rpm on this motor tests on that still needed

void setup(){
  //initialize the digital pin as an output
  pinMode(pin,OUTPUT);
  
  //Will create a 1100s pulse to arm the ESC
  //The pulse will last for 20ms x 500counts = 10,000ms or 10 seconds
  for (Arming_Time = 0; Arming_Time < 500; Arming_Time+= 1)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(1100);
    digitalWrite(pin,LOW);
    delay(20-(Pulse/1000));
    }
}

//the loop routine runs over and over again forever:
void loop()
{
  //constant speed esc
  digitalWrite(pin,HIGH);
  delayMicroseconds(Pulse);
  digitalWrite(pin,LOW);
  delay(20-Pulse/1000);
  }

