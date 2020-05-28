/*
Copyright [2020] Michael Teguh Laksana
*/
#ifndef _HOME_MICHAEL_ARDUINO_LIBRARIES_TASK2_NODE_H_
#define _HOME_MICHAEL_ARDUINO_LIBRARIES_TASK2_NODE_H_

#include <ros.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>
#define ROS_STD_MSGS_STD_SRVS

/**
  * A node acting as subscriber and client
  * 
  * 
  * @param topic Topic the node is subscribed to
  * @param cb Pointer to the callback function
  * @param srv:    The service name
*/
class Node{
 private:
    ros::Subscriber<std_msgs::Bool> sub;
    ros::ServiceClient<std_srvs::Empty::Request, std_srvs::Empty::Response> cln;

 public:
    ros::NodeHandle node;
    Node (const char topic[100], void (*cb)(std_msgs::Bool&), char srv[100]):
    sub(topic, cb), cln(srv)
    {}

    /**
    * Setup the node
    */
    void setup_node() {
      
      node.initNode();
      node.subscribe(sub);
      node.serviceClient(cln);
    }

    /**
    * Call the service
    */
    void client_call(){
      std_srvs::Empty::Request req;
      std_srvs::Empty::Response rep;
      cln.call(req, rep);
    }
};

#endif  // _HOME_MICHAEL_ARDUINO_LIBRARIES_TASK2_NODE_H_
