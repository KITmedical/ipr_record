#include <iostream>

#include "RecorderManager.hpp"

int
main(int argc, char** argv)
{
  ros::init(argc, argv, "ipr_record_node");

  RecorderManager manager;

  std::cout << "Spinning" << std::endl;
  ros::MultiThreadedSpinner spinner(4);
  spinner.spin();

  return 0;
}
