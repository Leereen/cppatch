#ifndef CPPATCH_SOURCES_H
#define CPPATCH_SOURCES_H

#include <dispatch/dispatch.h>

#include "queues.h"


namespace cppatch
{

  class BaseSource
  {
  private:
    const dispatch_source_t _source;

  public:
    BaseSource(const dispatch_source_t);
    ~BaseSource();

    void set_event_handler(const dispatch_block_t) const;
    void set_cancel_handler(const dispatch_block_t) const;
    void resume() const;
    void suspend() const;
  };

  class DataAddSource: public BaseSource
  {
  public:
    DataAddSource(const BaseQueue&);
  };

  class DataOrSource: public BaseSource
  {
  public:
    DataOrSource(const BaseQueue&);
  };

#ifdef LINUX_MACRO // TODO: Travis build on OSX fails, why?
  class DataReplaceSource: public BaseSource
  {
  public:
    DataReplaceSource(const BaseQueue&);
  };
#endif // LINUX_MACRO

  class ReadSource: public BaseSource
  {
  public:
    ReadSource(const BaseQueue&);
  };

  class SignalSource: public BaseSource
  {
  public:
    SignalSource(const BaseQueue&);
  };

  class TimerSource: public BaseSource
  {
  public:
    TimerSource(const BaseQueue&);
  };

  class WriteSource: public BaseSource
  {
  public:
    WriteSource(const BaseQueue&);
  };

#ifdef APPLE_MACRO
  /*
  // TODO: Travis build on OSX fails, why?
  class MemoryPressureSource: public BaseSource
  {
  public:
    MemoryPressureSource(const BaseQueue&);
  };

  class MachSendSource: public BaseSource
  {
  public:
    MachSendSource(const BaseQueue&);
  };

  class MachRecvSource: public BaseSource
  {
  public:
    MachRecvSource(const BaseQueue&);
  };

  class ProcSource: public BaseSource
  {
  public:
    ProcSource(const BaseQueue&);
  };

  class VNodeSource: public BaseSource
  {
  public:
    VNodeSource(const BaseQueue&);
  };
  */
#endif // APPLE_MACRO

}

#endif // CPPATCH_SOURCES_H
