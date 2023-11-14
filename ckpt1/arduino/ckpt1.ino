#include<ros.h>
#include<std_msgs/Int32.h>

ros::NodeHandle nh;
std_msgs::Int32 msg;

ros::Publisher publisher("multiple", &msg);
ros::Subscriber<std_msgs::Int32> subscriber("num", &messageCb);

void messageCb(const std_msgs::Int32& received_msg)
{   
    	msg.data = received_msg.data*2;
			publisher.publish(&msg);
}
	
void setup()
{
    	nh.initNode();
    	nh.advertise(publisher);
    	nh.subscribe(subscriber);
}

void loop()
{
    	nh.spinOnce();
    	delay(1);
}
