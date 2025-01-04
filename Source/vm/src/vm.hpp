#pragma once

#define MEMORY_MAX ((4294967295) * 2)

#include <stack>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <functional>
#include <unordered_map>

#include "io.hpp"
#include "cfg.hpp"

namespace wcvm {
  typedef uint8_t      byte;
  typedef uint16_t     word;
  typedef uint32_t     dword;
  typedef uint64_t     qword;

  class vm {
  private:
    cfg config;
    wcio io;
    qword ip;
    byte cf; // Compare Flag
    std::stack<uint64_t> st; // Stack
    bool halt = false;
    byte *memory;
    std::unordered_map<byte, std::function<void()>> ftable;
    std::unordered_map<word, std::function<void()>> syscalls;
  
    void  init_table();               // core.hpp
    void  init_prog();                // core.hpp
    void  init_disk();                // disk.hpp
    void  init_syscalls();            // syscalls.hpp
    void  _syscalls_check_files();    // syscalls.hpp
    void  _syscalls_load_functions(); // syscalls.hpp
    byte  read_byte();                // core.hpp
    word  read_word();                // core.hpp
    dword read_dword();               // core.hpp
    qword read_qword();               // core.hpp

    void write(const byte *buff, qword _len, qword _addr);
   
  public:
    void init() {
      std::cout << "------------------------------------\n"
                   "Wide Cinnamon Virtual Machine (WCVM)\n"
                   "Memory:  " << config.size_memory << " bytes\n"   
                   "Threads: " << config.thread_count << "\n"
                   "Runtime: Wys - WCVM:RT\n"
                   "Runtime Environnement: " << config.env << "\n"
                   "------------------------------------\n";
      
      memory = new byte[config.size_memory];

      init_table();
      init_syscalls();
      init_disk();
      init_prog(); 

      delete[] memory;
    }

    vm(cfg &c) : config(c) { }
  };
}
