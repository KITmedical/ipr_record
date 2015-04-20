#ifndef _TOPIC_RECORDER_H_
#define _TOPIC_RECORDER_H_

// system includes
#include <fstream>

// library includes
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Vector3.h>
#include <trocar2cartesian_msgs/TrocarPose.h>
#include <sensor_msgs/CameraInfo.h>
#include <camera_guidance_msgs/Mode.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>

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
    TopicRecorder(const std::string& topicName, const std::string& topicType, Recorder::Options options = Recorder::Options::NONE);

    // overwritten methods

    // methods

    // variables


  protected:
    // methods
    bool record();
    void imageTopicCallback(const sensor_msgs::Image::ConstPtr& imgMsg);

    template <typename T>
    void yamlTopicCallback(const typename T::ConstPtr& msg)
    {
      if (!record()) {
        return;
      }

      ros::Time fakeStamp = ros::Time::now();
      std::string outputPath = m_outputDir + "/" + m_outputSubdir + "/" + Recorder::timeString(fakeStamp) + ".yaml";
      std::fstream outStream(outputPath, std::ios::out);
      if (!outStream.is_open()) {
        ROS_ERROR_STREAM("Failed to write YAML " << outputPath  << " to disk");
        return;
      }
      outStream << *msg;
      m_recordCount++;
    }

    template <typename T>
    void yamlStampedTopicCallback(const typename T::ConstPtr& stampedMsg)
    {
      if (!record()) {
        return;
      }

      std::string outputPath = m_outputDir + "/" + m_outputSubdir + "/" + Recorder::timeString(stampedMsg->header.stamp) + ".yaml";
      std::fstream outStream(outputPath, std::ios::out);
      if (!outStream.is_open()) {
        ROS_ERROR_STREAM("Failed to write stamped YAML " << outputPath  << " to disk");
        return;
      }
      outStream << *stampedMsg;
      m_recordCount++;
    }

    // variables
    std::string m_topicName;
    std::string m_topicType;
    Recorder::Options m_options;
    ros::Subscriber m_sub;


  private:
    // methods

    // variables


};

#endif // _TOPIC_RECORDER_H_
