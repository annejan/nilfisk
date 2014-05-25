/**
 *  Nilfisk stepper motor power unit
 */
 
 #include <Stepper.h>
 
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

int power = 0;
int rcvpower = 0;
int steps = 0;

int maxpower = 1600;
int minpower = 0;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

void setup()                    // run once, when the sketch starts
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  Serial.begin(9600);           // set up Serial library at 9600 bps

  Serial.println();
  Serial.println("Nilfisk v 0.1");
  Serial.println("Welcome, please enter speed step (1000 is full scale)");
  Serial.println();
  Serial.println("Nilfisk: "); 
  Serial.println();
  motor.setSpeed(20);
}

void loop()
{   // send data only when you receive data:
  while (Serial.available() > 0) {
     // read the power
                rcvpower = Serial.parseInt();

                if (rcvpower == 0) {
                    Serial.println("Zero received");
                } else if(rcvpower > maxpower) {
                    Serial.print("Too high: ");
                    Serial.println(rcvpower, DEC);
                } else if (rcvpower < minpower) {
                    Serial.print("Too low: ");
                    Serial.println(rcvpower, DEC);
                } else {
                  // say what you got:
                    Serial.print("I received: ");
                    Serial.println(rcvpower, DEC);
                    Serial.print("Steps: ");
                    
                    if (rcvpower > power) {
                      steps = rcvpower-power;
                    } else if (rcvpower < power) {
                      steps = -(power-rcvpower);
                    } else {
                      steps = 0;
                    }
                    power=rcvpower;
                    Serial.println(steps, DEC);
                    motor.step(-steps*amp);
                }
        }
}
