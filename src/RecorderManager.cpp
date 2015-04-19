#include "RecorderManager.hpp"

// system includes

// library includes

// custom includes

/*---------------------------------- public: -----------------------------{{{-*/
RecorderManager::RecorderManager()
  :m_pnode("~")
{
  if (!m_pnode.hasParam("output_dir")) {
    ROS_ERROR("Missing private param: output_dir");
    return;
  }
  std::string outputDir;
  m_pnode.getParam("output_dir", outputDir);
  if (!m_pnode.hasParam("recordings")) {
    ROS_ERROR("Missing private param: recordings");
    return;
  }
  std::map<std::string,std::string> recordings;
  m_pnode.getParam("recordings", recordings);
  for (auto& recording : recordings) {
    std::string name(recording.first);
    std::replace(name.begin(), name.end(), '!', '/');
    std::string type(recording.second);
    std::replace(type.begin(), type.end(), '!', '/');
    //std::cout << name << " : " << type << std::endl;
    m_recorders.push_back(Recorder::create(name, type));
    m_recorders.back()->setOutputDir(outputDir);
  }

  m_startRecordingService = m_pnode.advertiseService("start_recording", &RecorderManager::startRecording, this);
  m_stopRecordingService = m_pnode.advertiseService("stop_recording", &RecorderManager::stopRecording, this);
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
bool
RecorderManager::startRecording(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
  for (auto& recorder : m_recorders) {
    recorder->startRecording();
  }

  return true;
}

bool
RecorderManager::stopRecording(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
  for (auto& recorder : m_recorders) {
    recorder->stopRecording();
  }

  return true;
}
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
