#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>

#include "vm.hpp"

namespace wcvm {  
  class IO {
  private:
  public:
    class file {
    private:
      std::function<void(const std::string&)> _writer;
      std::function<void(byte *, uint32_t)> _reader;

    public:
      void write(const std::string &s) { _writer(s); }
      
      file( 
        std::function<void(const std::string&)> &writer,
        std::function<void(byte *, uint32_t)> &reader
      ) : _writer(writer), _reader(reader) {}
    };
  
    
  };

}