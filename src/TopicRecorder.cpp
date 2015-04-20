#include "TopicRecorder.hpp"

// system includes
#include <algorithm>

// library includes
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

// custom includes


/*---------------------------------- public: -----------------------------{{{-*/
TopicRecorder::TopicRecorder(const std::string& topicName, const std::string& topicType, Recorder::Options options)
  :m_topicName(topicName),
   m_topicType(topicType),
   m_options(options)
{
  ROS_INFO_STREAM("Creating topic recorder for topic " << m_topicName << " of type " << m_topicType);
  m_outputSubdir = topicName;
  
  std::replace(m_outputSubdir.begin(), m_outputSubdir.end(), '/', '_');
  if (m_topicType == "sensor_msgs/Image") {
    m_sub = m_node.subscribe<sensor_msgs::Image>(m_topicName, 1, &TopicRecorder::imageTopicCallback, this);
  } else if (m_topicType == "geometry_msgs/Vector3") {
    m_sub = m_node.subscribe<geometry_msgs::Vector3>(m_topicName, 1, &TopicRecorder::yamlTopicCallback<geometry_msgs::Vector3>, this);
  } else if (m_topicType == "trocar2cartesian_msgs/TrocarPose") {
    m_sub = m_node.subscribe<trocar2cartesian_msgs::TrocarPose>(m_topicName, 1, &TopicRecorder::yamlTopicCallback<trocar2cartesian_msgs::TrocarPose>, this);
  } else if (m_topicType == "sensor_msgs/CameraInfo") {
    m_sub = m_node.subscribe<sensor_msgs::CameraInfo>(m_topicName, 1, &TopicRecorder::yamlStampedTopicCallback<sensor_msgs::CameraInfo>, this);
  } else if (m_topicType == "camera_guidance_msgs/Mode") {
    m_sub = m_node.subscribe<camera_guidance_msgs::Mode>(m_topicName, 1, &TopicRecorder::yamlTopicCallback<camera_guidance_msgs::Mode>, this);
  } else if (m_topicType == "std_msgs/String") {
    m_sub = m_node.subscribe<std_msgs::String>(m_topicName, 1, &TopicRecorder::yamlTopicCallback<std_msgs::String>, this);
  } else if (m_topicType == "geometry_msgs/PoseStamped") {
    m_sub = m_node.subscribe<geometry_msgs::PoseStamped>(m_topicName, 1, &TopicRecorder::yamlTopicCallback<geometry_msgs::PoseStamped>, this);
  } else {
    ROS_ERROR_STREAM("Unsupported topic type: " << m_topicType);
  }
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
bool
TopicRecorder::record()
{
  return m_recordingActive && (!(m_options & Recorder::Options::ONCE) || m_recordCount == 0);
}

void
TopicRecorder::imageTopicCallback(const sensor_msgs::Image::ConstPtr& imgMsg)
{
  if (!record()) {
    return;
  }

	cv_bridge::CvImagePtr cvimgptr = cv_bridge::toCvCopy(imgMsg, "bgr8");
  std::string outputPath = m_outputDir + "/" + m_outputSubdir + "/" + Recorder::timeString(imgMsg->header.stamp) + ".png";
  if (!cv::imwrite(outputPath, cvimgptr->image)) {
    ROS_ERROR_STREAM("Failed to write Image " << outputPath  << " to disk");
    return;
  }
  m_recordCount++;
}
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
