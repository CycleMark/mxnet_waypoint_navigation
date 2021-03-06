#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//Wibble 

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  move_base_msgs::MoveBaseGoal lWayPoints[10];

  // Lounge
  lWayPoints[0].target_pose.pose.position.x = 5.19148302078;
  lWayPoints[0].target_pose.pose.position.y = -3.88265228271;
  lWayPoints[0].target_pose.pose.orientation.w = 1.0;

  // Kitchen Waypoint Patio
  lWayPoints[1].target_pose.pose.position.x = -8.1485710144;
  lWayPoints[1].target_pose.pose.position.y = -1.52750754356;
  lWayPoints[1].target_pose.pose.orientation.w = 1.0;

 // Kitchen (Oven)
  lWayPoints[2].target_pose.pose.position.x = -5.05258893967;
  lWayPoints[2].target_pose.pose.position.y = -0.318086385727;
  lWayPoints[2].target_pose.pose.orientation.w = 1.0;

  // Playroom
  lWayPoints[3].target_pose.pose.position.x = -1.79476928711;
  lWayPoints[3].target_pose.pose.position.y = -3.15057492256;
  lWayPoints[3].target_pose.pose.orientation.w = 1.0;

/*
  lWayPoints[5].target_pose.pose.position.x = 
  lWayPoints[5].target_pose.pose.position.y = 
  lWayPoints[5].target_pose.pose.orientation.w = 1.0;
*/
  int lWayPointNumber = 0;

  while(ros::ok())
  {
    //Move to the Oven
    goal = lWayPoints[lWayPointNumber];
    ROS_INFO("Waypoint No. %i", lWayPointNumber);
   //we'll send a goal to the robot to move 1 meter forward
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Waypoint Reached Sucessfully");
    else
      ROS_INFO("Failed to Reach Waypoint");

    if (lWayPointNumber < 3)
      lWayPointNumber++;
    else
      lWayPointNumber = 0;
    /*
    goal.target_pose.pose.position.x = 2.29059457779;
    goal.target_pose.pose.position.y = -0.182346343994;
    goal.target_pose.pose.orientation.w = 1.0; 
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Waypoint Reached Sucessfully");
    else
      ROS_INFO("Failed to Reach Waypoint");

    // Move to the Shower Room
    goal.target_pose.pose.position.x = 1.46254444122;
    goal.target_pose.pose.position.y = 2.58535337448;
    goal.target_pose.pose.orientation.w = 1.0; 
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Waypoint Reached Sucessfully");
    else
      ROS_INFO("Failed to Reach Waypoint");
      */

  }






  return 0;
}
