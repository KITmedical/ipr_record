#include "RecorderManager.hpp"

// system includes

// library includes

// custom includes

/*---------------------------------- public: -----------------------------{{{-*/
RecorderManager::RecorderManager()
{
  ros::NodeHandle pnh("~");

  std::map<std::string,std::string> recordings;
  if (!pnh.hasParam("recordings")) {
    ROS_ERROR("Missing private param: recordings");
    return;
  }
  pnh.getParam("recordings", recordings);
  for (auto& recording : recordings) {
    std::string name(recording.first);
    std::replace(name.begin(), name.end(), '!', '/');
    std::string type(recording.second);
    std::replace(type.begin(), type.end(), '!', '/');
    //std::cout << name << " : " << type << std::endl;
    m_recorders.push_back(Recorder::create(name, type));
  }
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
