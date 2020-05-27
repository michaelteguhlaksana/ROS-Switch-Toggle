#!/usr/bin/env python

"""
DEVICE NODE
----------------
	The device node.

	The device node will toggle the thruster speed and publish the thruster state upon request.

DEPENDENCIES
----------------
	rospy
	std_msgs
	toggle.srv -- Empty Service file (http://docs.ros.org/melodic/api/std_srvs/html/srv/Empty.html)

CLASSES
---------------

	Publisher
	===============
	The publisher object.

    A publisher node for publishing the state of the thruster.

    Attributes
    ----------
    queue: The maximum queue length for subscriber. The default is 10
    rate: The publishing rate. The default is 10 hz.
    state: The state of the thruster. Either True or False.

	Methods
	-------
	set_queue: 		Set values for the number of queued topic.
	set_rate: 		Set the rate of publishing value to the topic.
	publish_state:	Toggle the state of the thruster


	Button
	===============
	The Button Object

    The switch responsible for toggling the thruster state

    Attributes:
    state:  The state of the thruster. Boolean value. True for on, and False for off

"""

import rospy
from std_msgs.msg import Bool
from task2_py.srv import toggle


class Publisher(object):
    '''The publisher object.

    A publisher node for publishing the state of the thruster.

    Attributes:
    queue: The maximum queue length for subscriber. The default is 10
    rate: The publishing rate. The default is 10 hz.
    state: The state of the thruster. Either True or False.

    '''

    def __init__(self, button, queue=10, rate=10, name="state"):
        self.set_queue(queue)
        self.pub = rospy.Publisher(name, Bool, queue_size=self._queue)
        self.set_rate(rate)
        self.button = button

    def set_queue(self, queue):
        """Set values for the number of queued topic."""
        self._queue = queue

    def set_rate(self, rate):
        '''Set the rate of publishing value to the topic.'''
        self._pub_rate = rospy.Rate(rate)

    def publish_state(self, *args):
        '''
        Toggle the state of the thruster

        Args:
        Takes no argument
        args only there for absorbing unused arguments

        Return:
        Empty message []

        '''
        self.button.toggle_state()
        self.pub.publish(self.button.get_state())
        return []

class Button(object):
    """The Button Object

    The switch responsible for toggling the thruster state

    Attributes:
    state:  The state of the thruster. Boolean value. True for on, and False for off

    """
    def __init__(self, state=False):
        self.set_state(state)

    def set_state(self, state):
        """Set the state of the thruster"""
        #This is honestly redundant for current condition.
        #But if the state is more than 1 states, this will be more useful
        self._state = state

    def get_state(self):
        """Returns the current state of the thruster"""
        return self._state

    def toggle_state(self):
        """Flip the switch of the thruster"""
        self.set_state(not self._state)
        print "State toggled to: %s" %(self._state)

if __name__ == "__main__":
    try:
        print "starting node...."
        rospy.init_node('device')
        BUTTON = Button()

        print "starting publisher..."
        PUBLISHER = Publisher(button=BUTTON)

        print "initiate loop for service..."
        while not rospy.is_shutdown():
            print "initiate service..."
            SRV = rospy.Service("state_srv", toggle, PUBLISHER.publish_state)
            print "Ready for input..."
            rospy.spin()
    except rospy.ROSInterruptException:
        pass
