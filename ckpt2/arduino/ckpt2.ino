#include<ros.h>
#include<std_msgs/Int32MultiArray.h>

#define EnA 5
#define EnB 6
#define In1 8
#define In2 9
#define In3 10
#define In4 11

ros::NodeHandle nh; 
std_msgs::Int32MultiArray velocity;
ros::Publisher publisher("velocity_feedback", &velocity);
int pwm_r,pwm_l;

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
  }  
  analogWrite(EnA, right);
  analogWrite(EnB, left);
}

void velocityCb(const std_msgs::Int32MultiArray& received_velocity)
{   
    velocity.data = received_velocity.data;
    pwm_r = velocity.data[0];
    pwm_l = velocity.data[1];
    publisher.publish(&velocity);
    
}

ros::Subscriber<std_msgs::Int32MultiArray> subscriber("velocity", &velocityCb);

void setup()
{
    nh.initNode();
    nh.advertise(publisher);
    nh.subscribe(subscriber);
    Serial.begin(57600);
    pinMode(EnA, OUTPUT);
    pinMode(EnB, OUTPUT);
    pinMode(In1, OUTPUT);
    pinMode(In2, OUTPUT);
    pinMode(In3, OUTPUT);
    pinMode(In4, OUTPUT);
}

void loop()
{
  move_robot(pwm_r,pwm_l);
  nh.spinOnce();
  delay(100);
}
