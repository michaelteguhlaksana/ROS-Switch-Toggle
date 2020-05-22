cmake_minimum_required(VERSION 3.0.2)
project(task2_py)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  message_generation
)

#catkin_python_setup()


## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Num.msg   
# )

add_service_files(
 FILES
 toggle.srv
)

generate_messages(
 DEPENDENCIES
 std_msgs
)

catkin_package(
  #INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS rospy std_msgs
  #DEPENDS system_lib
)
