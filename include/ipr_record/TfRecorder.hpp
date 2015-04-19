#ifndef _TF_RECORDER_H_
#define _TF_RECORDER_H_

// system includes
#include <thread>

// library includes
#include <tf/transform_listener.h>

// custom includes
#include "Recorder.hpp"

// forward declarations



class TfRecorder
  :public Recorder
{
  public:
    // enums

    // typedefs

    // static const member variables
 
    // static utility functions


    // constructors
    TfRecorder(const std::string& childFrame, const std::string& parentFrame, double hz);

    // overwritten methods

    // methods

    // variables


  protected:
    // methods
    void readTfLoop();

    // variables
    std::string m_childFrame;
    std::string m_parentFrame;
    double m_hz;
    tf::TransformListener m_tfListener;
    std::thread m_tfThread;


  private:
    // methods

    // variables


};

#endif // _TF_RECORDER_H_
