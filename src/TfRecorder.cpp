#include "TfRecorder.hpp"

// system includes
#include <fstream>

// library includes

// custom includes


/*---------------------------------- public: -----------------------------{{{-*/
TfRecorder::TfRecorder(const std::string& childFrame, const std::string& parentFrame, double hz)
  :m_childFrame(childFrame),
   m_parentFrame(parentFrame),
   m_hz(hz)
{
  ROS_INFO_STREAM("Creating TF recorder for parent frame " << m_parentFrame << " and child frame " << m_childFrame << " with " << m_hz << "Hz");
  m_outputSubdir = parentFrame + "_TO_" + childFrame;

  m_tfThread = std::thread(&TfRecorder::readTfLoop, this);
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
void
TfRecorder::readTfLoop()
{
  ros::Rate rate(m_hz);
  while (ros::ok()) {
    rate.sleep();
    if (!m_recordingActive) {
      continue;
    }
    tf::StampedTransform parentChildTf;
    try {
      m_tfListener.lookupTransform(m_parentFrame, m_childFrame, ros::Time(0), parentChildTf);
    } catch (tf::TransformException ex) {
      ROS_ERROR("TF lookup error: %s", ex.what());
      continue;
    }
    geometry_msgs::TransformStamped parentChildTfMsg;
    tf::transformStampedTFToMsg(parentChildTf, parentChildTfMsg);
    std::string outputPath = m_outputDir + "/" + m_outputSubdir + "/" + Recorder::timeString(parentChildTfMsg.header.stamp) + ".yaml";
    std::fstream outStream(outputPath, std::ios::out);
    if (!outStream.is_open()) {
      ROS_ERROR_STREAM("Failed to write TransformStamped " << outputPath  << " to disk");
      return;
    }
    outStream << parentChildTfMsg;
    m_recordCount++;
  }
}
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
