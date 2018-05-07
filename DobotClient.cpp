#include "ros/ros.h"
#include "std_msgs/String.h"
#include "dobot/SetCmdTimeout.h"
#include "dobot/SetQueuedCmdClear.h"
#include "dobot/SetQueuedCmdStartExec.h"
#include "dobot/SetQueuedCmdForceStopExec.h"
#include "dobot/GetDeviceVersion.h"

#include "dobot/SetEndEffectorParams.h"
#include "dobot/SetPTPJointParams.h"
#include "dobot/SetPTPCoordinateParams.h"
#include "dobot/SetPTPJumpParams.h"
#include "dobot/SetPTPCommonParams.h"
#include "dobot/SetPTPCmd.h"

#include "dobot/GetPose.h"
#include "dobot/SetEndEffectorSuctionCup.h"
#include <sstream>
///////////////////////////////////////////////////////////
int countUP;
int countMid;
int countDown;
int countSuc;
const char* msgIN;

////////////////////////New Para///////////////////////////
int box1;
int box2;

//////////////////////////pototype//////////////////////////
void chatterCallback(const std_msgs::String::ConstPtr& msg);

//////////////////////////  main  //////////////////////////
int main(int argc, char **argv)
{
    ros::init(argc, argv, "DobotClientDown");
    ros::NodeHandle n;

    ros::ServiceClient client;

    // Publisher
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("command", 1000);

    // Listener
    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    ros::Rate loop_rate(0.2);

    // SetCmdTimeout
    client = n.serviceClient<dobot::SetCmdTimeout>("/DobotServer/SetCmdTimeout");
    dobot::SetCmdTimeout srv1;
    srv1.request.timeout = 3000;
    if (client.call(srv1) == false) {
        ROS_ERROR("Failed to call SetCmdTimeout. Maybe DobotServer isn't started yet!");
        return -1;
    }

    // Clear the command queue
    client = n.serviceClient<dobot::SetQueuedCmdClear>("/DobotServer/SetQueuedCmdClear");
    dobot::SetQueuedCmdClear srv2;
    client.call(srv2);

    // Start running the command queue
    client = n.serviceClient<dobot::SetQueuedCmdStartExec>("/DobotServer/SetQueuedCmdStartExec");
    dobot::SetQueuedCmdStartExec srv3;
    client.call(srv3);

    // Get device version information
    client = n.serviceClient<dobot::GetDeviceVersion>("/DobotServer/GetDeviceVersion");
    dobot::GetDeviceVersion srv4;
    client.call(srv4);
    if (srv4.response.result == 0) {
        ROS_INFO("Device version:%d.%d.%d", srv4.response.majorVersion, srv4.response.minorVersion, srv4.response.revision);
    } else {
        ROS_ERROR("Failed to get device version information!");
    }

    // Set end effector parameters
    client = n.serviceClient<dobot::SetEndEffectorParams>("/DobotServer/SetEndEffectorParams");
    dobot::SetEndEffectorParams srv5;
    srv5.request.xBias = 70;
    srv5.request.yBias = 0;
    srv5.request.zBias = 0;
    client.call(srv5);

    // Set PTP joint parameters
    do {
        client = n.serviceClient<dobot::SetPTPJointParams>("/DobotServer/SetPTPJointParams");
        dobot::SetPTPJointParams srv;

        for (int i = 0; i < 4; i++) {
            srv.request.velocity.push_back(100);
        }
        for (int i = 0; i < 4; i++) {
            srv.request.acceleration.push_back(100);
        }
        client.call(srv);
    } while (0);

    // Set PTP coordinate parameters
    do {
        client = n.serviceClient<dobot::SetPTPCoordinateParams>("/DobotServer/SetPTPCoordinateParams");
        dobot::SetPTPCoordinateParams srv;

        srv.request.xyzVelocity = 100;
        srv.request.xyzAcceleration = 100;
        srv.request.rVelocity = 100;
        srv.request.rAcceleration = 100;
        client.call(srv);
    } while (0);

    // Set PTP jump parameters
    do {
        client = n.serviceClient<dobot::SetPTPJumpParams>("/DobotServer/SetPTPJumpParams");
        dobot::SetPTPJumpParams srv;

        srv.request.jumpHeight = 20;
        srv.request.zLimit = 200;
        client.call(srv);
    } while (0);

    // Set PTP common parameters
    do {
        client = n.serviceClient<dobot::SetPTPCommonParams>("/DobotServer/SetPTPCommonParams");
        dobot::SetPTPCommonParams srv;

        srv.request.velocityRatio = 50;
        srv.request.accelerationRatio = 50;
        client.call(srv);
    } while (0);

///////////////////////////////////////////////////////////
  while (ros::ok())
  {
/*
    std_msgs::String msg;
    std::stringstream ss;

    ss << '2';
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
*/
    ros::spin();
  }
    return 0;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ros::NodeHandle n;
  ros::ServiceClient client;
  ros::Rate loop_rate(0.2);

  ////////////////////////////////////////////////////////
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  msgIN = msg->data.c_str();
  if(*msgIN == 'a' || *msgIN == 'b'|| *msgIN == 'c' || *msgIN == 'd' || *msgIN == 'e' || *msgIN == 'f'|| *msgIN == 'g' )
  {
    ROS_INFO("box1 = 1");
    loop_rate.sleep();
    box1 = 1;
  }
  ////////////////////////////////////////////////////////
  msgIN = msg->data.c_str();
  if(*msgIN == 'i' || *msgIN == 'j'|| *msgIN == 'k'|| *msgIN == 'l'|| *msgIN == 'm' || *msgIN == 'n'|| *msgIN == 'o')
  {
    ROS_INFO("box2 = 1");
    loop_rate.sleep();
    box2 = 1;
  }
  // Publisher
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("command", 1000);

//////////////////////// Number#1 /////////////////////////
///////////////////////////////////////////////////////
if(box1 == 1 )
{

  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_1");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = 2;
      srv.request.r = 95;
      client.call(srv);
      if (srv.response.result == 0) {
        /////////////////////////////////////////////////////////////////////
        //loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("LineUP_Suc#ON");
            srv.request.enableCtrl = 1;
            srv.request.suck = 1;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        /////////////////////////////////////////////////////////////////////
       box1 = 2;
       break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box1 == 2)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_2");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = -41;
      srv.request.r = 95;
      client.call(srv);
      if (srv.response.result == 0) {
        box1 = 3;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box1 == 3)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
  /////////////////////////////////////////////////////////////////
      std_msgs::String msg;
      std::stringstream ss;
      ss << 'y';
      msg.data = ss.str();
      ROS_INFO("%s", msg.data.c_str());
      chatter_pub.publish(msg);
  /////////////////////////////////////////////////////////////////
      ROS_INFO("LineUP_3");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = 151;
      srv.request.r = -40;
      client.call(srv);

      if (srv.response.result == 0) {
        box1 = 4;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box1 == 4)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_4");
      srv.request.ptpMode = 1;
      srv.request.x = 211;
      srv.request.y = 116;
      srv.request.z = 151;
      srv.request.r = -40;
      client.call(srv);
      if (srv.response.result == 0) {
        /////////////////////////////////////////////////////////////////////
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("LineUP_Suc#OFF");
            srv.request.enableCtrl = 1;
            srv.request.suck = 0;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        /////////////////////////////////////////////////////////////////////
        box1 = 5;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
//loop_rate.sleep();
}

if(box1 == 5)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_5");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = 151;
      srv.request.r = -40;
      client.call(srv);
      if (srv.response.result == 0) {
        box1 = 6;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box1 == 6)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_6");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = 2;
      srv.request.r = 95;
      client.call(srv);
      if (srv.response.result == 0) {
        box1 = 7;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  //loop_rate.sleep();
}

if(box1 == 7)
{
  std_msgs::String msg;
  std::stringstream ss;

  ss << 'z';
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  chatter_pub.publish(msg);

  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_7");
      srv.request.ptpMode = 1;
      srv.request.x = 131;
      srv.request.y = -2;
      srv.request.z = -15;
      srv.request.r = 0;
      client.call(srv);
      if (srv.response.result == 0) {
        box1 = 0;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}
///////////////////////////////////////////////////////

//////////////////////// Number#2 /////////////////////////
///////////////////////////////////////////////////////
if(box2 == 1 )
{

  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineDown_1");
      srv.request.ptpMode = 1;
      srv.request.x = 120;
      srv.request.y = 173;
      srv.request.z = 2;
      srv.request.r = 93;
      client.call(srv);
      if (srv.response.result == 0) {
        /////////////////////////////////////////////////////////////////////
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("LineDown_Suc#ON");
            srv.request.enableCtrl = 1;
            srv.request.suck = 1;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        /////////////////////////////////////////////////////////////////////
       box2 = 2;
       break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box2 == 2)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineDown_2");
      srv.request.ptpMode = 1;
      srv.request.x = 120;
      srv.request.y = 173;
      srv.request.z = -41;
      srv.request.r = 93;
      client.call(srv);
      if (srv.response.result == 0) {
        box2 = 3;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box2 == 3)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
  /////////////////////////////////////////////////////////////////
      std_msgs::String msg;
      std::stringstream ss;
      ss << 'v';
      msg.data = ss.str();
      ROS_INFO("%s", msg.data.c_str());
      chatter_pub.publish(msg);
  /////////////////////////////////////////////////////////////////
      ROS_INFO("LineDown_3");
      srv.request.ptpMode = 1;
      srv.request.x = 120;
      srv.request.y = 173;
      srv.request.z = 151;
      srv.request.r = -10;
      client.call(srv);
      if (srv.response.result == 0) {
        box2 = 4;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box2 == 4)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineDown_4");
      srv.request.ptpMode = 1;
      srv.request.x = 211;
      srv.request.y = 116;
      srv.request.z = 151;
      srv.request.r = -40;
      client.call(srv);
      if (srv.response.result == 0) {
        /////////////////////////////////////////////////////////////////////
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("LineDown_Suc#OFF");
            srv.request.enableCtrl = 1;
            srv.request.suck = 0;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        /////////////////////////////////////////////////////////////////////
        box2 = 5;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
}

if(box2 == 5)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineDown_5");
      srv.request.ptpMode = 1;
      srv.request.x = 109;
      srv.request.y = 218;
      srv.request.z = 151;
      srv.request.r = -20;
      client.call(srv);
      if (srv.response.result == 0) {
        box2 = 6;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(box2 == 6)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineDown_6");
      srv.request.ptpMode = 1;
      srv.request.x = 110;
      srv.request.y = 163;
      srv.request.z = 2;
      srv.request.r = 93;
      client.call(srv);
      if (srv.response.result == 0) {
        box2 = 7;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  //loop_rate.sleep();
}

if(box2 == 7)
{
  std_msgs::String msg;
  std::stringstream ss;

  ss << 'w';
  msg.data = ss.str();
  ROS_INFO("%s", msg.data.c_str());
  chatter_pub.publish(msg);

  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("LineUP_7");
      srv.request.ptpMode = 1;
      srv.request.x = 131;
      srv.request.y = -2;
      srv.request.z = -15;
      srv.request.r = 0;
      client.call(srv);
      if (srv.response.result == 0) {
        box2 = 0;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//////////////////////// Mid //////////////////////////
///////////////////////////////////////////////////////
if(countMid == 1)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_1");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -200;
      srv.request.z = -5;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("DobotMid_Suc#1");
            srv.request.enableCtrl = 1;
            srv.request.suck = 1;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        countMid = 2;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
}

if(countMid == 2)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_2");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -320;
      srv.request.z = -5;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 3;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 3)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_3");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -200;
      srv.request.z = -5;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 4;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
loop_rate.sleep();
}

if(countMid == 4)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_4");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -200;
      srv.request.z = -5;
      srv.request.r = -1.5;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 5;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 5)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_5");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -200;
      srv.request.z = 70;
      srv.request.r = -1.5;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 6;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 6)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_6");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 191;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 7;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 7)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_7");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 300;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 8;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 8)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_8");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 290;
      srv.request.z = 26;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("DobotMid_Suc#2");
            srv.request.enableCtrl = 1;
            srv.request.suck = 0;
            client.call(srv);
            if (srv.response.result == 0) {
              countMid = 9;
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
}

if(countMid == 9)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_9");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 300;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 10;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countMid == 10)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotMid_HOME");
      srv.request.ptpMode = 1;
      srv.request.x = 131;
      srv.request.y = -2;
      srv.request.z = -15;
      srv.request.r = 91;
      client.call(srv);
      if (srv.response.result == 0) {
        countMid = 0;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
 }
///////////////////////////////////////////////////////

//////////////////////// UP /////////////////////////
///////////////////////////////////////////////////////
if(countUP == 1 )
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_1");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -205;
      srv.request.z = -5;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
       countUP = 2;
       break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 2)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_2");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -205;
      srv.request.z = 112;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("DobotUP_Suc#1");
            srv.request.enableCtrl = 1;
            srv.request.suck = 1;
            client.call(srv);
            if (srv.response.result == 0) {
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
        countUP = 3;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 3)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_3");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -300;
      srv.request.z = 112;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 4;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 4)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_4");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -205;
      srv.request.z = 112;
      srv.request.r = -98;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 5;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
loop_rate.sleep();
}

if(countUP == 5)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_5");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -205;
      srv.request.z = 112;
      srv.request.r = -1.5;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 6;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 6)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_6");
      srv.request.ptpMode = 1;
      srv.request.x = 7;
      srv.request.y = -205;
      srv.request.z = 70;
      srv.request.r = -1.5;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 7;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 7)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_7");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 191;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 8;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 8)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_8");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 300;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 9;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 9)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_9");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 290;
      srv.request.z = 26;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        loop_rate.sleep();
        do {
        client = n.serviceClient<dobot::SetEndEffectorSuctionCup>("/DobotServer/SetEndEffectorSuctionCup");
        dobot::SetEndEffectorSuctionCup srv;
            ROS_INFO("DobotUP_Suc#2");
            srv.request.enableCtrl = 1;
            srv.request.suck = 0;
            client.call(srv);
            if (srv.response.result == 0) {
              countUP = 10;
              break;
            }
           ros::spinOnce();
           if(ros::ok() == false){
             break;
           }
        } while(0);
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
}

if(countUP == 10)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_10");
      srv.request.ptpMode = 1;
      srv.request.x = -30;
      srv.request.y = 300;
      srv.request.z = 70;
      srv.request.r = 189;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 11;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}

if(countUP == 11)
{
  do {
  client = n.serviceClient<dobot::SetPTPCmd>("/DobotServer/SetPTPCmd");
  dobot::SetPTPCmd srv;
      ROS_INFO("DobotUP_HOME");
      srv.request.ptpMode = 1;
      srv.request.x = 131;
      srv.request.y = -2;
      srv.request.z = -15;
      srv.request.r = 91;
      client.call(srv);
      if (srv.response.result == 0) {
        countUP = 0;
        break;
      }
      ros::spinOnce();
      if(ros::ok() == false){
        break;
      }
  } while (0);
  loop_rate.sleep();
}
///////////////////////////////////////////////////////
}
