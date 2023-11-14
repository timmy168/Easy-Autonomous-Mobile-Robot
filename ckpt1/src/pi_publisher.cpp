#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>

class pi : public ros::NodeHandle
{
public:
    pi()
    {
        publisher = this->advertise<std_msgs::Int32>("num", 10);
        msg.data = 1;
    }

    void publishMessage()
    {
        publisher.publish(msg);
        std::cout<<"user's input is "<< msg.data <<std::endl;
    }
    std_msgs::Int32 msg;
private:
    ros::NodeHandle nh;
    ros::Publisher publisher;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pi_publisher");
    ros::NodeHandle nh;
    auto node = std::make_shared<pi>();
    while (ros::ok())
    {
        int input;   
        // std::cout << "----------------------------------------" << std::endl;
        // std::cout << "Enter user's input or enter -1 to quit: " << std::endl;
        std::cin >> input;
        if(input == -1) ros::shutdown();
        else node->msg.data = input;
        node->publishMessage();
    }

    ros::spin();
    return 0;
}
