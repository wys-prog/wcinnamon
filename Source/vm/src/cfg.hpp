#pragma once

#define MEMORY_MAX ((4294967295) * 2)
#define THREAD_MAX ((12))

#include <string>
#include <cstdint>

namespace wcvm {

  typedef struct {
    std::string env;
    uint64_t    size_memory;
    uint64_t    thread_count;
    
  } cfg;

}
