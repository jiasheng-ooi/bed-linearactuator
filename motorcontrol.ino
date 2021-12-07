/**
 * Use of 2 DC motor and a L293D
 */

// Motor 1
const int PIN_ACTIVATE_3_4 = 2;
const int PIN_INPUT_3 = 3;
const int PIN_INPUT_4 = 4;

// Motor 2
const int PIN_ACTIVATE_1_2 = 8;
const int PIN_INPUT_1 = 9;
const int PIN_INPUT_2 = 10;

//Input
String a ="";
int current_height = 0;
int height_actuate = 0;
bool choice = false;

/**
 * Initialize the pins of a motor
 */
void initMotor(int activationPin, int pin1, int pin2)
{
    pinMode(activationPin, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    // Enable the motor driver
    analogWrite(activationPin, 150); 
}
//decide how long should motor be moved(degree of height acutuated)


int act_range(int potentio)
{
  int range = 0;
  range = 20000/potentio;  // reading from 0-1023
  return range;
}
 //error threshold for potentiometer to decided if motor should actuate
bool to_move(int now, int then)
{
  bool decision = false;
  int diff = abs(then-now);
  if (diff > 20)
  {
    decision = true;
  }
  return decision;
 }
 /**
 * Run a motor either clockwise or counter-clockwise
 */

void runMotor(int pin1, int pin2, bool clockwise )
{
    if (clockwise) {
        // Run the motor clockwise
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        
    } else {
        // Run the motor counter-clockwise
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        
    }
}



void stopMotor(int pin1, int pin2)
{
    
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
       
        
}

// Main functions

void setup()
{ 
    Serial.begin(9600);
    initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2);
    initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
}

void loop()
{
  //input height 
    int height = analogRead(A0);
    int direct = 0;
    int act_time = 0;
    direct = current_height - height;
    act_time = abs(act_range(direct));

    analogWrite(A2, 100);
    analogWrite(A3, 100);
     
    choice = to_move(height,current_height);
    Serial.println(direct);
    Serial.println(choice);
    
    if(height==current_height && choice == false)
    {
        stopMotor(PIN_INPUT_1, PIN_INPUT_2);
        stopMotor(PIN_INPUT_3, PIN_INPUT_4);
    }
    else if (height>current_height && choice == true) 
    {
        Serial.print("Height Actuating up to ");
        Serial.print(height);
        Serial.print("cm\n");
        runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
        runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
        delay(act_time);
        //reached
        Serial.print("Reached\n");
        stopMotor(PIN_INPUT_1, PIN_INPUT_2);
        stopMotor(PIN_INPUT_3, PIN_INPUT_4);
        current_height = height;
    }
    else if (height<current_height && choice == true)
    {
        Serial.print("Height Actuating down to ");
      Serial.print(height);
        Serial.print("cm\n");
        runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
      runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
      delay(act_time);
        //reached
        Serial.print("Reached\n");
        stopMotor(PIN_INPUT_1, PIN_INPUT_2);
        stopMotor(PIN_INPUT_3, PIN_INPUT_4);
        current_height = height;
        
    }
 
}
