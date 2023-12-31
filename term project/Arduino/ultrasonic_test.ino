// include
#include<ros.h>
#include<std_msgs/Int32.h>

//ultra sonic sensor pin
#define trig 3
#define echo 2
#define In5 7

// ros
ros::NodeHandle nh;
std_msgs::Int32 distance;
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
    pinMode(echo, INPUT);
    Serial.begin(9600);

    //distance
    distance.data = 0;
}

void loop()
{
    int target_press = digitalRead(In5);
    front_distance = sr04(trig,echo) * 0.017;
    distance.data = front_distance;
    publisher.publish(&distance);
    Serial.print("Front distance in CM:");
    Serial.println(front_distance);
    delay(1000);
}
