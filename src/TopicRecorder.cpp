#include "TopicRecorder.hpp"

// system includes
#include <algorithm>

// library includes
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

// custom includes


/*---------------------------------- public: -----------------------------{{{-*/
TopicRecorder::TopicRecorder(const std::string& topicName, const std::string& topicType)
  :m_topicName(topicName),
   m_topicType(topicType)
{
  ROS_INFO_STREAM("Creating topic recorder for topic " << m_topicName << " of type " << m_topicType);
  m_outputSubdir = topicName;
  
  std::replace(m_outputSubdir.begin(), m_outputSubdir.end(), '/', '_');
  if (m_topicType == "sensor_msgs/Image") {
    m_sub = m_node.subscribe<sensor_msgs::Image>(m_topicName, 1, &TopicRecorder::topicCallback, this);
  } else {
    ROS_ERROR_STREAM("Unsupported topic type: " << m_topicType);
  }
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
void
TopicRecorder::topicCallback(const sensor_msgs::Image::ConstPtr& imgMsg)
{
  if (!m_recordingActive) {
    return;
  }

  ROS_INFO_STREAM("img: " << Recorder::timeString(imgMsg->header.stamp));
	cv_bridge::CvImagePtr cvimgptr = cv_bridge::toCvCopy(imgMsg, "bgr8");
  std::string outputPath = m_outputDir + "/" + m_outputSubdir + "/" + Recorder::timeString(imgMsg->header.stamp) + ".png";
  if (!cv::imwrite(outputPath, cvimgptr->image)) {
    ROS_ERROR_STREAM("Failed to write image " << outputPath  << " to disk");
  }
}
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
