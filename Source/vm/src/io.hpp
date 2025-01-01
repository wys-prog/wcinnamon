#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <functional>

#include "vm.hpp"

namespace wcvm {  
  class wcio {
    using fnwriter = std::function<void(const std::string&)>;
    using fnreader = std::function<void(byte *, uint32_t)>;
  private:

  public:
    class file {
    private:
      fnwriter _writer;
      fnreader _reader;

    public:
      void write(const std::string &s) { _writer(s); }
      void read(byte *buff, uint32_t len) { _reader(buff, len); }
      
      file( 
        fnwriter &writer,
        fnreader &reader
      ) : _writer(writer), _reader(reader) {}

      file() = default;
    };
  


    file stdout;
    file stderr;
    std::unordered_map<word, file> handles = {
      {0xFFFE, stdout}, {0xFFFF, stderr},
    };
    

    wcio() {
      fnwriter w = [](const std::string &str) { std::cout << str; };
      fnreader r = [](byte *buff, uint32_t len) { std::cin.read((char*)buff, len); };
      fnwriter wr = [](const std::string &str) { std::cerr << str; };
      stdout = file(w, r);
      stderr = file(wr, r);
    }
  };

}