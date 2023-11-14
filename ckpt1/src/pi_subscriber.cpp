#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

class pi : public ros::NodeHandle
{
public:
    pi()
    {
        std::cout << "Start to subscribe!" << std::endl;
        subscriber = this->subscribe<std_msgs::Int32>("num", 10, &pi::MessageCallback, this);
    }
    
    void MessageCallback(const std_msgs::Int32::ConstPtr& msg_ptr)
    {
        ros::Rate rate(1);
        msg.data = msg_ptr -> data;
        msg.data = msg.data * 2;
        // std::cout<<"------------------------"<< std::endl;
        std::cout<<"message from Arduino is "<< msg.data <<std::endl;
        rate.sleep();
    }
private:
    // ros::NodeHandle nh;
    ros::Subscriber subscriber;
    std::string topic_name_multiple;
    std_msgs::Int32 msg;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pi_sublisher");
    auto node = std::make_shared<pi>();
    ros::spin();
    return 0;
}
