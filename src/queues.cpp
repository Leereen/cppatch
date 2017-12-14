#include <iostream>

#include "queues.h"
#include "utils.h"


namespace cppatch
{

  BaseQueue::BaseQueue(const dispatch_queue_t queue,
                       const QueueType queue_type,
                       const bool wait_on_exit)
    : _queue(queue), _wait_on_exit(wait_on_exit), _lock(), type(queue_type)
  {
    if (_wait_on_exit) {
      dispatch_set_finalizer_f([](void* context) -> void {
          DEBUG_LOG("FINALIZER");
          // cleanup garbage
        });
      }
  }

  BaseQueue::~BaseQueue()
  {
    std::lock_guard<std::mutex> lock(_lock);
    int i = std::rand();
    DEBUG_LOG("STOP " << i);
    if (_wait_on_exit) {
      dispatch_barrier_sync(^{
          DEBUG_LOG("Barrier block " << i);
        });
    }
    // release on global queues has no effect
    ::dispatch_release(_queue);
    DEBUG_LOG("QUEUE RELEASE " << i);
  }

  const dispatch_queue_t BaseQueue::queue() const
  {
    return _queue;
  }

  void BaseQueue::dispatch_sync(const dispatch_block_t block) const
  {
    ::dispatch_sync(_queue, block);
  }

  void BaseQueue::dispatch_sync_f(void* context, const dispatch_function_t function) const
  {
    ::dispatch_sync_f(_queue, context, function);
  }

  void BaseQueue::dispatch_async(const dispatch_block_t block) const
  {
    ::dispatch_async(_queue, block);
  }

  void BaseQueue::dispatch_async_f(void* context, const dispatch_function_t function) const
  {
    ::dispatch_async_f(_queue, context, function);
  }

  void BaseQueue::dispatch_barrier_sync(const dispatch_block_t block) const
  {
    ::dispatch_barrier_sync(_queue, block);
  }

  void BaseQueue::dispatch_barrier_sync_f(void* context, const dispatch_function_t function) const
  {
    ::dispatch_barrier_sync_f(_queue, context, function);
  }

  void BaseQueue::dispatch_barrier_async(const dispatch_block_t block) const
  {
    ::dispatch_barrier_async(_queue, block);
  }

  void BaseQueue::dispatch_barrier_async_f(void* context, const dispatch_function_t function) const
  {
    ::dispatch_barrier_async_f(_queue, context, function);
  }

  void BaseQueue::dispatch_set_finalizer_f(const dispatch_function_t function) const
  {
    ::dispatch_set_finalizer_f(_queue, function);
  }


  MainQueue::MainQueue(const bool _wait_on_exit)
    : BaseQueue(::dispatch_get_main_queue(), QueueType::SERIAL, _wait_on_exit)
  {}


  GlobalQueue::GlobalQueue(const enum QueuePriority priority,
                           const bool _wait_on_exit)
    : BaseQueue(::dispatch_get_global_queue(priority, 0), QueueType::CONCURRENT, _wait_on_exit)
  {}


  CreatedQueue::CreatedQueue(const std::string label, const enum QueueType type,
                             const bool wait_on_exit)
    : BaseQueue(::dispatch_queue_create(label.c_str(),
                                        (type == QueueType::SERIAL
                                         ? DISPATCH_QUEUE_SERIAL
                                         : (type == QueueType::CONCURRENT
                                            ? DISPATCH_QUEUE_CONCURRENT
                                            : nullptr))),
                type,
                wait_on_exit)
  {}


  SerialQueue::SerialQueue(const std::string label, const bool wait_on_exit)
    : CreatedQueue(label, cppatch::QueueType::SERIAL, wait_on_exit)
  {}


  ConcurrentQueue::ConcurrentQueue(const std::string label, const bool wait_on_exit)
    : CreatedQueue(label, cppatch::QueueType::CONCURRENT, wait_on_exit)
  {}

}
