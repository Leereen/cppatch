#include <iostream>
#include <unistd.h>

#include "cppatch.h"
#include "utils.h"

int test(std::string message)
{
  const cppatch::ConcurrentQueue* queue1 = new cppatch::ConcurrentQueue("toto");
  // const cppatch::GlobalQueue* queue1 = new cppatch::GlobalQueue(cppatch::QueuePriority::DEFAULT);
  const cppatch::ConcurrentQueue* queue2 = new cppatch::ConcurrentQueue("tata");
  // const cppatch::SerialQueue* queue = new cppatch::SerialQueue("toto");
  uint32_t const count = 50000, p_count = 1000;

  __block uint32_t i = 0, j = 0;

  dispatch_block_t lol1 = ^{
    i++;
    if (i % p_count == 0) {
      DEBUG_LOG("[1] " << i);
    }
    usleep(300);
  };

  dispatch_block_t lol2 = ^{
    j++;
    if (j % p_count == 0) {
      DEBUG_LOG("[2] " << j);
      }
  };

  uint32_t a = 0;
  for (a = 0; a < count; a++) {
    queue1->dispatch_async(lol1);
    queue2->dispatch_async(lol2);
  }
  std::cout << "Finished inserting " << count << " blocks by queue" << std::endl;

  usleep(500000);
  delete queue1;
  usleep(500000);
  delete queue2;
  std::cout << "KOOOO" << std::endl;
  return 0;
}
