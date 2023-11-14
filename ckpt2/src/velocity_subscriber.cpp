#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>

class control : public ros::NodeHandle
{
public:
    control()
    {
        std::cout << "Start to subscribe!" << std::endl;
        subscriber = this->subscribe<std_msgs::Int32MultiArray>("velocity", 
                                                                 10, &control::VelocityCallback, this);
        velocity.data.resize(2);
    }
    
    void VelocityCallback(const std_msgs::Int32MultiArray::ConstPtr& velocity_ptr)
    {
        velocity.data = velocity_ptr -> data;
        // std::cout<<"------------------------"<< std::endl;
        std::cout<<"right velocity from Arduino is "<< velocity.data[0] <<std::endl;
        std::cout<<"left velocity from Arduino is "<< velocity.data[1] <<std::endl;
    }
private:
    // ros::NodeHandle nh;
    ros::Subscriber subscriber;
    std_msgs::Int32MultiArray velocity;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "velocity_sublisher");
    auto node = std::make_shared<control>();
    ros::spin();
    return 0;
}
