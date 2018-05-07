#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

const char* msgTask;

//////////////////////////pototype//////////////////////////
void chatterCallback(const std_msgs::String::ConstPtr& msg);

int main(int argc, char **argv)
{

  ros::init(argc, argv, "TaskOne");
  ros::NodeHandle n;

  ros::ServiceClient client;
  // Listener
  ros::Subscriber sub = n.subscribe("command", 1000, chatterCallback);

  // Publisher
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(0.2);

  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;
    std::stringstream ss;

    ss << "*";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

    ++count;
  }
  return 0;
}

///////////////////////// receive msg /////////////////////
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ros::NodeHandle n;
  ros::ServiceClient client;
  ros::Rate loop_rate(0.2);
  // Publisher
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);


  ROS_INFO("I heard: [%s]", msg->data.c_str());
  msgTask = msg->data.c_str();
  if(*msgTask == 'a')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'a';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'b')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'b';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'c')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'c';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'd')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'd';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'e')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'e';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'f')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'f';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'g')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'g';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////LineDown/////////////////////////////////
  if(*msgTask == 'i')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'i';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'j')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'j';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'k')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'k';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'l')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'l';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'm')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'm';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'n')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'n';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  /////////////////////////////////////////////////////////////
  if(*msgTask == 'o')
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << 'o';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  //////////////////////////////////////////////////////
  if(*msgTask == 'v')
  {

    std_msgs::String msg;
    std::stringstream ss;
    ss << 'v';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'w')
  {

    std_msgs::String msg;
    std::stringstream ss;
    ss << 'w';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  //////////////////////////////////////////////////////
  if(*msgTask == 'y')
  {

    std_msgs::String msg;
    std::stringstream ss;
    ss << 'y';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
  //////////////////////////////////////////////////////
  if(*msgTask == 'z')
  {

    std_msgs::String msg;
    std::stringstream ss;
    ss << 'z';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    ros::spinOnce();
  }
}
