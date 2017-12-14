#include "sources.h"


namespace cppatch
{
  BaseSource::BaseSource(const dispatch_source_t source)
    : _source(source)
  {}

  BaseSource::~BaseSource()
  {
    suspend();
    ::dispatch_release(_source);
  }

  void BaseSource::set_event_handler(const dispatch_block_t block) const
  {
    ::dispatch_source_set_event_handler(_source, block);
  }

  void BaseSource::set_cancel_handler(const dispatch_block_t block) const
  {
    ::dispatch_source_set_cancel_handler(_source, block);
  }

  void BaseSource::resume() const
  {
    ::dispatch_resume(_source);
  }

  void BaseSource::suspend() const
  {
    ::dispatch_suspend(_source);
  }

  DataAddSource::DataAddSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_ADD, 0, 0, queue.queue()))
  {}

  DataOrSource::DataOrSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_OR, 0, 0, queue.queue()))
  {}

#ifdef LINUX_MACRO
  DataReplaceSource::DataReplaceSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_REPLACE, 0, 0, queue.queue()))
  {}
#endif // LINUX_MACRO

  ReadSource::ReadSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, 0, 0, queue.queue()))
  {}

  SignalSource::SignalSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_SIGNAL, 0, 0, queue.queue()))
  {}

  TimerSource::TimerSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue.queue()))
  {}

  WriteSource::WriteSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_WRITE, 0, 0, queue.queue()))
  {}

#ifdef APPLE_MACRO
  /*
  MemoryPressureSource::MemoryPressureSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_MEMORYPRESSURE, 0, 0, queue.queue()))
  {}

  MachSendSource::MachSendSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_MACH_SEND, 0, 0, queue.queue()))
  {}

  MachRecvSource::MachRecvSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_MACH_RECV, 0, 0, queue.queue()))
  {}

  ProcSource::ProcSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_PROC, 0, 0, queue.queue()))
  {}

  VNodeSource::VNodeSource(const BaseQueue &queue)
    : BaseSource(dispatch_source_create(DISPATCH_SOURCE_TYPE_DATA_VNODE, 0, 0, queue.queue()))
  {}
  */
#endif // APPLE_MACRO

}
