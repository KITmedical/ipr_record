#ifndef _RECORDER_MANAGER_H_
#define _RECORDER_MANAGER_H_

// system includes
#include <vector>
#include <memory>

// library includes
#include <ros/ros.h>

// custom includes
#include "Recorder.hpp"


// forward declarations



class RecorderManager
{
  public:
    // enums

    // typedefs

    // static const member variables
 
    // static utility functions


    // constructors
    RecorderManager();

    // overwritten methods

    // methods

    // variables


  protected:
    // methods

    // variables
    std::vector<std::shared_ptr<Recorder>> m_recorders;


  private:
    // methods

    // variables


};

#endif // _RECORDER_MANAGER_H_
