#include<task2_node.h>

#ifndef ROS_STD_MSGS_STD_SRVS  // defined in task2_node.h
#include <std_msgs/Bool.h>
#endif  // ROS_STD_MSGS_STD_SRVS

void print_state(const std_msgs::Bool& state){
  /**
   * Shows the state of the thruster
   * 
   * If the LED is ON, the thruster is ON and vice versa
   * 
   * Paremeter:
   * state: The state of the thruster
   */
    if (state.data==true){
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(13, LOW);
    }
}

Node nh ("state", &print_state, "state_srv");

unsigned long t_start;

void setup() {
  nh.setup_node();
  while(!nh.node.connected()) {
    nh.node.spinOnce();
  }
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  
  nh.node.loginfo("Startup complete");
  t_start=millis();
  
}

void loop() {
  float error=10;
  unsigned long t_now = millis();
  unsigned long t=t_now-t_start;
  if( t<=error || (3000-error<=t && t<=3000+error) || (6000-error<=t && t<=6000+error)){
    nh.node.loginfo("Sending toggle request");
    nh.client_call();
  }
  nh.node.spinOnce();
}
