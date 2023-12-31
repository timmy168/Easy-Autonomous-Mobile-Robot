// include
#include<ros.h>
#include<std_msgs/Int32MultiArray.h>

//ultra sonic sensor pin
#define trig 3
#define front_echo 2
#define left_echo 4
#define right_echo 13
#define In5 7

// ros
ros::NodeHandle nh;
std_msgs::Int32MultiArray distance;
ros::Publisher publisher("distance", &distance);

// flags and distance
int front_distance = 0, left_distance = 0, right_distance = 0;

int sr04(int trig_pin, int echo_pin)
{
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    return pulseIn(echo_pin, HIGH);
}

void setup()
{
    //ros
    nh.initNode();
    nh.advertise(publisher);
    
    //pin
    pinMode(trig, OUTPUT);
    pinMode(front_echo, INPUT);
    pinMode(left_echo, INPUT);
    pinMode(right_echo, INPUT);
    Serial.begin(9600);

    //distance
    distance.data[0] = 0;
    distance.data[1] = 0;
    distance.data[2] = 0;
}

void loop()
{
    int target_press = digitalRead(In5);
    front_distance = sr04(trig,front_echo) * 0.017;
    delay(60);
    left_distance = sr04(trig,left_echo) * 0.017;
    delay(60);
    right_distance = sr04(trig,right_echo) * 0.017;
    delay(60);
    distance.data[0] = front_distance;
    distance.data[1] = left_distance;
    distance.data[2] = right_distance;
    publisher.publish(&distance);
    Serial.print("Front distance in CM:");
    Serial.println(front_distance);
    Serial.print("Left distance in CM:");
    Serial.println(left_distance);
    Serial.print("Right distance in CM:");
    Serial.println(right_distance);
    delay(1000);
}
