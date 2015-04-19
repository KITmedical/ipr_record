#ifndef _RECORDER_H_
#define _RECORDER_H_

// system includes

// library includes
#include <ros/ros.h>

// custom includes


// forward declarations



class Recorder
{
  public:
    // enums
    enum Options { NONE = 0x0, ONCE = 0x01 };

    // typedefs

    // static const member variables
 
    // static utility functions
    static std::shared_ptr<Recorder> create(const std::string& name, const std::string& type);
    static std::string timeString(const ros::Time& rosTime);
    static bool dirExists(const std::string& path);
    static bool createDir(const std::string& path);


    // constructors
    Recorder();

    // overwritten methods

    // methods
    void setOutputDir(const std::string& outputDir);
    void startRecording();
    void stopRecording();

    // variables


  protected:
    // methods

    // variables
    ros::NodeHandle m_node;
    bool m_recordingActive;
    std::string m_outputDir;
    std::string m_outputSubdir;
    unsigned m_recordCount;


  private:
    // methods

    // variables


};

#endif // _RECORDER_H_
