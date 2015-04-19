#include "Recorder.hpp"

// system includes

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
/*------------------------------------------------------------------------}}}-*/

/*--------------------------------- protected: ---------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/

/*---------------------------------- private: ----------------------------{{{-*/
/*------------------------------------------------------------------------}}}-*/
