#include "TfRecorder.hpp"

// system includes

// library includes

// custom includes


/*---------------------------------- public: -----------------------------{{{-*/
TfRecorder::TfRecorder(const std::string& childFrame, const std::string& parentFrame)
  :m_childFrame(childFrame),
   m_parentFrame(parentFrame)
{
  ROS_INFO_STREAM("Creating TF recorder for parent frame " << parentFrame << " and child frame " << childFrame);
}
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
