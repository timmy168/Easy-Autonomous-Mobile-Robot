#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>

class control : public ros::NodeHandle
{
public:
    control()
    {
        publisher = this->advertise<std_msgs::Int32MultiArray>("velocity", 10);
        velocity.data.resize(2); //0 for right, 1 for left
        velocity.data[0] = 0;
        velocity.data[1] = 0;
    }
    void setVelocity(int right, int left)
    {
        velocity.data[0] = right;
        velocity.data[1] = left;
    }
    void publishVelocity()
    {
        publisher.publish(velocity); 
        std::cout<<"user's right is "<< velocity.data[0] <<std::endl;
        std::cout<<"user's left is "<< velocity.data[1] <<std::endl;
    }
private:
    std_msgs::Int32MultiArray velocity;
    ros::NodeHandle nh;
    ros::Publisher publisher;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "velocity_publisher");
    auto node = std::make_shared<control>();
    while (ros::ok())
    {
        int right,left;   
        // std::cout << "----------------------------------------" << std::endl;
        std::cout << "Enter user's right input or enter -1 to quit: " << std::endl;
        std::cin >> right;
        std::cout << "Enter user's left input or enter -1 to quit: " << std::endl;
        std::cin >> left;
        if(right == -1 || left == -1) ros::shutdown();
        else
        {
            node->setVelocity(right,left);
        } 
        node->publishVelocity();
    }
    //ros::spin();
    return 0;
}
