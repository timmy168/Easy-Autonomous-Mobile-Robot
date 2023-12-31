// pins
//ultra sonic sensor pin
#define trig 3
#define front_echo 2
#define right_echo 4
#define left_echo 13
//motor pins
#define EnA 5
#define EnB 6
#define In1 8
#define In2 9
#define In3 10
#define In4 11
#define In5 7  // target

// flags and distance
int get_target = 0;
int front_distance = 0, left_distance = 0, right_distance = 0;

// Ultrasonic sensor
int sr04(int trig_pin, int echo_pin)
{
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    return pulseIn(echo_pin, HIGH);
}

//robot motor control
void move_robot(int right,int left)
{ 
    if(right>0)
    {
        digitalWrite(In1, LOW);
        digitalWrite(In2, HIGH);
    }
    else
    {
        digitalWrite(In1, HIGH);
        digitalWrite(In2, LOW); 
        right *= -1;
    }
    if(left>0)
    {
        digitalWrite(In3, LOW);
        digitalWrite(In4, HIGH);
    }
    else
    {
        digitalWrite(In3, HIGH);
        digitalWrite(In4, LOW);
        left *= -1; 
    }  
    analogWrite(EnA, right);
    analogWrite(EnB, left);
}

void foward()
{
    move_robot(150,148);
}

void backward()
{
    move_robot(-105,-100);
}

void right()
{
    move_robot(100,135);
}

void left()
{
    move_robot(135,100);
}

void left_spin()
{  
    move_robot(125,-120);
}

void right_spin()
{
    move_robot(-120,125);
}

void robot_stop()
{
    move_robot(0,0);
}

void robot_pause()
{
    int sec = 0;
    while(sec <= 10)
    {
        robot_stop();
        sec++;
        delay(100);
    }
}

void sr04_foward(int front_distance, int right_distance, int left_distance)
{
    int compensate = 0;
    float Kp = 2;
    if(right_distance > left_distance)
    {
        if( (right_distance - left_distance) > 20) Kp = 0.2;
        compensate = (right_distance - left_distance) * Kp;
        move_robot(150 , 148 + compensate);
    }
    if(left_distance > right_distance)
    {
        if( (left_distance - right_distance) > 20) Kp = 0.2;
        compensate = (left_distance - right_distance) * Kp;
        move_robot(150 + compensate, 148);
    }
}

void explore(int front_distance, int right_distance, int left_distance)
{
    front_distance = sr04(trig,front_echo) * 0.017;
    delay(60);
    left_distance = sr04(trig,left_echo) * 0.017;
    delay(60);
    right_distance = sr04(trig,right_echo) * 0.017;
    delay(60);
    
    if(front_distance < 0) front_distance * -1;
    if(right_distance < 0) right_distance * -1;
    if(left_distance < 0) left_distance * -1;
    
    if(front_distance > 100) front_distance = 100;
    if(right_distance > 30) right_distance = 30;
    if(left_distance > 30) left_distance = 30;
    
    Serial.print("Front distance in CM:");
    Serial.println(front_distance);
    Serial.print("Right distance in CM:");
    Serial.println(right_distance);
    Serial.print("Left distance in CM:");
    Serial.println(left_distance);
    
    if(front_distance < 16)
    {
        robot_pause();
        if(right_distance > left_distance)
        {
            while(1)
            {
                int right_spin_front_distance = sr04(trig,front_echo) * 0.017;
                right_spin();
                if(right_spin_front_distance > 85) break;
            }
            //for(int i=0;i<3;i++)
            //{
               //left_spin();
               //delay(100);
            //}
        }
        else if(left_distance > right_distance)
        {
            while(1)
            {
                int left_spin_front_distance = sr04(trig,front_echo) * 0.017;
                left_spin();
                if(left_spin_front_distance > 85) break;
            }
            //for(int i=0;i<3;i++)
            //{
               //right_spin();
               //delay(100);
            //}
        }
    }
    else
    {
        //foward();
        sr04_foward(front_distance,right_distance,left_distance);
    }
}

// setup and loop
void setup()
{
    //pin
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(In5, INPUT);
    pinMode(trig, OUTPUT);
    pinMode(front_echo, INPUT);
    pinMode(left_echo, INPUT);
    pinMode(right_echo, INPUT);
    Serial.begin(9600);
  
    //flags
    get_target = 0;
}

void loop()
{
    int target_press = digitalRead(In5);

    //ball touch sensors
    if (target_press == LOW)
    {
        get_target = 1;
    }
  
    //whole exploring process
    if(get_target == 1)
    {
        robot_stop();
    }
    else
    {
        explore(front_distance,right_distance,left_distance);
    }
    delay(60); // unit is ms => delay 0.1sec => 10HZ
}
