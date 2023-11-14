// include
#include<ros.h>
#include<std_msgs/Int32.h>

// pins
#define EnA 5
#define EnB 6
#define In1 8
#define In2 9
#define In3 10
#define In4 11
#define In5 7  // ball
#define In6 12 // left
#define In7 13 // right
#define Light A5 // light

// ros
ros::NodeHandle nh;
std_msgs::Int32 light;
ros::Publisher publisher("light_feedback", &light);

// flags and time 
int finding = 0;
int right_collision,left_collision = 0;
int finding_ball = 0;
int find_ball = 0;
int find_ball_sec = 0;
int catch_ball = 0;

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
    move_robot(105,100);
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
    move_robot(100,0);
}

void right_spin()
{
    move_robot(0,100);
}

void robot_stop()
{
    move_robot(0,0);
}

void collision()
{
    int sec = 0;
    while(sec <= 10)
    {
        backward();
        sec++;
        delay(100);
    }
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

void setup()
{
    //ros
    nh.initNode();
    nh.advertise(publisher);
    Serial.begin(57600);

    //pin
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
    pinMode(In5, INPUT);
    pinMode(In6, INPUT);
    pinMode(In7, INPUT);
    pinMode(Light ,INPUT);
  
    //flags
    finding = 1;
    right_collision = 0;
    left_collision = 0;
    finding_ball = 0;
    find_ball = 0;
    find_ball_sec = 0;
    catch_ball = 0;
}

void loop()
{
    int ball_press = digitalRead(In5);
    int left_press = digitalRead(In6);
    int right_press = digitalRead(In7);
    int light_data = analogRead(Light);
    
    //ball touch sensors
    if (ball_press == LOW)
    {
        catch_ball = 1;
    }

    //left touch sensor
    if(left_press == LOW)
    {
        left_collision = 1;
    }

    //right touch sensor
    if(right_press == LOW)
    {
        right_collision = 1;
    }
    
    //light sensor
    if(light_data < 250)
    {
        find_ball = 1;
    }

    //counting finding ball time
    if(finding_ball == 1)
    {
        find_ball_sec++;
        if(find_ball_sec == 100)
        {
            find_ball = 1;
            find_ball_sec = 0;
        }
    }
  
    //whole finding process
    if(catch_ball == 1)
    {
        robot_stop();
    }
    else
    {
        if(finding == 1 && right_collision == 0 && left_collision == 0)
        {
            foward();
        }
        else if(finding == 1 && right_collision == 1 && left_collision == 0)
        {
            find_ball = 0;
            robot_pause();
            collision();
            robot_pause();
            finding = 0;
            finding_ball = 1;
        }
        else if(finding == 1 && right_collision == 0 && left_collision == 1)
        { 
            find_ball = 0;
            robot_pause();
            collision();
            robot_pause();
            finding = 0;
            finding_ball = 1;
        }
        else if(finding == 1 && right_collision == 1 && left_collision == 1)
        {
            find_ball = 0;
            robot_pause();
            collision();
            robot_pause();
            finding = 0;
            finding_ball = 1;
        }
        else if(finding == 0 && right_collision == 1 && left_collision == 0)
        {
            left_spin();
            if(find_ball == 1)
            {
                robot_pause();
                finding = 1;
                right_collision = 0;
                left_collision = 0;
                finding_ball = 0;
            }
        }
        else if(finding == 0 && right_collision == 0 && left_collision == 1)
        {
            left_spin();
            if(find_ball == 1)
            {
                robot_pause();
                finding = 1;
                right_collision = 0;
                left_collision = 0;
                finding_ball = 0;
            }
        }
        else if(finding == 0 && right_collision == 1 && left_collision == 1)
        {
            left_spin();
            if(find_ball == 1)
            {
                robot_pause();
                finding = 1;
                right_collision = 0;
                left_collision = 0;
                finding_ball = 0;
            }
        }
    }
    delay(100); // unit is ms => delay 0.1sec => 10HZ
}
