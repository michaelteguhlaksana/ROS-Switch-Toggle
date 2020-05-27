#include <ros.h>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>

class Node{
 private:
    ros::Subscriber<std_msgs::Bool> sub;
    ros::ServiceClient<std_srvs::Empty::Request, std_srvs::Empty::Response> cln;
 public:

    void print_state(const std_msgs::Bool& state){
      if (state.data==true){
        digitalWrite(13, HIGH);
      }
      else{
        digitalWrite(13, LOW);
      }
    }
    ros::NodeHandle node;
    Node(const char topic[100], void (*cb) (std_msgs::Bool&), char srv[100]):
    sub(topic, cb), cln(srv)
    {}

    void setup_node() {
      node.initNode();
      node.subscribe(sub);
      node.serviceClient(cln);
    }

    void client_call(){
      std_srvs::Empty::Request req;
      std_srvs::Empty::Response rep;
      cln.call(req, rep);
    }
};

void print_state(const std_msgs::Bool& state){
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
