# ROS-Switch-Toggle
Toggling a thruster switch using ROS (rospy) and Arudino MEGA 2560.

During operation, there are 2 nodes,1 as the device and 1 as the remote.
For this implementation, the device is the computer running the python node (device.py) and the remote (remote.ino) is the Arduino MEGA board.

The remote consists of a node, which act as a subscriber and a service client.
The device also consists of a node acting as a publisher and a service server.

The state of the thruster is represented by a boolean variable (True for on, and False for off).
The request message and response message is an Empty message ([]). 

The remote can request the device to toggle the switch. The device will then toggle the switch and publish the current state of the thruster. The remote will then log the info to the terminal.

Currently, the request message will be sent right after startup, 3 second after startup and 6 second after.
