#include "Recorder.hpp"

// system includes
#include <sys/types.h>
#include <sys/stat.h>

// library includes
#include <ahbstring.h>

// custom includes
#include "TopicRecorder.hpp"
#include "TfRecorder.hpp"

/*---------------------------------- public: -----------------------------{{{-*/
std::shared_ptr<Recorder>
Recorder::create(const std::string& name, const std::string& type)
{
  if (ahb::string::startswith(type, "TF ")) {
    return std::make_shared<TfRecorder>(name, type.substr(2));
  } else {
    return std::make_shared<TopicRecorder>(name, type);
  }
}

std::string
Recorder::timeString(const ros::Time& rosTime)
{
  std::stringstream ss;

  ss << std::setfill('0') << std::setw(10) << rosTime.sec << "." << std::setw(10) << rosTime.nsec;

  return ss.str();
}

bool
Recorder::dirExists(const std::string& path)
{
  struct stat sb;
  return stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode);
}

bool
Recorder::createDir(const std::string& path)
{
  ROS_INFO_STREAM("Creating directory " << path);
  return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}


Recorder::Recorder()
  :m_recordingActive(false)
{
}

void
Recorder::setOutputDir(const std::string& outputDir)
{
  m_outputDir = outputDir;
  if (!Recorder::dirExists(m_outputDir)) {
    Recorder::createDir(m_outputDir);
  }
  std::string subdirPath = m_outputDir + "/" + m_outputSubdir;
  if (m_outputSubdir.size() > 0 && !Recorder::dirExists(subdirPath)) {
    Recorder::createDir(subdirPath);
  }
}

void
Recorder::startRecording()
{
  if (m_outputDir.size() == 0) {
    ROS_ERROR("Cannot start recording because output directory is not set.");
    return;
  }
  m_recordingActive = true;
}

void
Recorder::stopRecording()
{
  m_recordingActive = false;
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
