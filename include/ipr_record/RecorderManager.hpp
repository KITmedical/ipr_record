#ifndef _RECORDER_MANAGER_H_
#define _RECORDER_MANAGER_H_

// system includes
#include <vector>
#include <memory>

// library includes
#include <ros/ros.h>
#include <std_srvs/Empty.h>

// custom includes
#include "Recorder.hpp"


// forward declarations



class RecorderManager
{
  public:
    // enums

    // typedefs

    // static const member variables
 
    // static utility functions


    // constructors
    RecorderManager();

    // overwritten methods

    // methods

    // variables


  protected:
    // methods
    bool startRecording(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);
    bool stopRecording(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);

    // variables
    ros::NodeHandle m_node;
    ros::NodeHandle m_pnode;
    ros::ServiceServer m_startRecordingService;
    ros::ServiceServer m_stopRecordingService;
    std::vector<std::shared_ptr<Recorder>> m_recorders;


  private:
    // methods

    // variables


};

#endif // _RECORDER_MANAGER_H_
