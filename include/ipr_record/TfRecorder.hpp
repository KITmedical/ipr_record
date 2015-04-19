#ifndef _TF_RECORDER_H_
#define _TF_RECORDER_H_

// system includes

// library includes

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
    TfRecorder(const std::string& childFrame, const std::string& parentFrame);

    // overwritten methods

    // methods

    // variables


  protected:
    // methods

    // variables
    std::string m_childFrame;
    std::string m_parentFrame;


  private:
    // methods

    // variables


};

#endif // _TF_RECORDER_H_
