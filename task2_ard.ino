#include <ros.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>

ros::NodeHandle node;

void print_state(const std_msgs::Bool& state){
    if (state.data==true){
      digitalWrite(13, HIGH);
    }
    else{
      digitalWrite(13, LOW);
    }
}

ros::Subscriber<std_msgs::Bool> sub("state", &print_state);
ros::ServiceClient<std_srvs::Empty::Request, std_srvs::Empty::Response> state_client("state_srv");

unsigned long t_start;

void setup() {
  node.initNode();
  node.subscribe(sub);
  node.serviceClient(state_client);
  while(!node.connected()) {
    node.spinOnce();
  }
  //Serial.print("Startup complete");
  pinMode(13,OUTPUT);
  
  node.loginfo("Startup complete");
  t_start=millis();
  
}

void loop() {
  
  std_srvs::Empty::Request req;
  std_srvs::Empty::Response rep;
  float error=10;
  unsigned long t_now = millis();
  unsigned long t=t_now-t_start;
  if( t<=error || (3000-error<=t && t<=3000+error) || (6000-error<=t && t<=6000+error)){
    node.loginfo("Sending toggle request");
    state_client.call(req, rep);
  }
  node.spinOnce();
  //delay(10);
}
