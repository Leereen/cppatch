#ifndef CPPATCH_QUEUES_H
#define CPPATCH_QUEUES_H

#include <mutex>
#include <string>
#include <dispatch/dispatch.h>


namespace cppatch
{

  enum QueuePriority
  {
    HIGH       = DISPATCH_QUEUE_PRIORITY_HIGH,
    DEFAULT    = DISPATCH_QUEUE_PRIORITY_DEFAULT,
    LOW        = DISPATCH_QUEUE_PRIORITY_LOW,
    BACKGROUND = DISPATCH_QUEUE_PRIORITY_BACKGROUND
  };


  enum QueueType
  {
    UNTYPED,
    SERIAL,
    CONCURRENT,
  };


  class BaseQueue
  {
  private:
    const dispatch_queue_t _queue;
    bool _wait_on_exit;
    std::mutex _lock;

  public:
    const QueueType type;

    BaseQueue(const dispatch_queue_t, const QueueType, const bool);
    ~BaseQueue();
    const dispatch_queue_t queue() const;
    void dispatch_sync(const dispatch_block_t) const;
    void dispatch_async(const dispatch_block_t) const;
    void dispatch_barrier_sync(const dispatch_block_t) const;
    void dispatch_barrier_async(const dispatch_block_t) const;
    void dispatch_sync_f(void*, const dispatch_function_t) const;
    void dispatch_async_f(void*, const dispatch_function_t) const;
    void dispatch_barrier_sync_f(void*, const dispatch_function_t) const;
    void dispatch_barrier_async_f(void*, const dispatch_function_t) const;
    void dispatch_set_finalizer_f(const dispatch_function_t) const;
  };


  class MainQueue: public BaseQueue
  {
  public:
    MainQueue(const bool wait_on_exit=true);
  };


  class GlobalQueue: public BaseQueue
  {
  public:
    GlobalQueue(const enum QueuePriority, const bool wait_on_exit=true);
  };


  class CreatedQueue: public BaseQueue
  {
  public:
    CreatedQueue(const std::string, const enum QueueType, const bool wait_on_exit=true);
  };


  class SerialQueue: public CreatedQueue
  {
  public:
    SerialQueue(const std::string, const bool wait_on_exit=true);
  };


  class ConcurrentQueue: public CreatedQueue
  {
  public:
    ConcurrentQueue(const std::string, const bool wait_on_exit=true);
  };

}

#endif // CPPATCH_QUEUES_H
