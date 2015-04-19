#ifndef _TOPIC_RECORDER_H_
#define _TOPIC_RECORDER_H_

// system includes

// library includes
#include <sensor_msgs/Image.h>

// custom includes
#include "Recorder.hpp"

// forward declarations



class TopicRecorder
  :public Recorder
{
  public:
    // enums

    // typedefs

    // static const member variables
 
    // static utility functions


    // constructors
    TopicRecorder(const std::string& topicName, const std::string& topicType);

    // overwritten methods

    // methods

    // variables


  protected:
    // methods
    void topicCallback(const sensor_msgs::Image::ConstPtr& imgMsg);

    // variables
    std::string m_topicName;
    std::string m_topicType;
    ros::Subscriber m_sub;


  private:
    // methods

    // variables


};

#endif // _TOPIC_RECORDER_H_
