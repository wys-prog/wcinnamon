#pragma once

#include <cstdint>
#include <algorithm>

namespace wcvm {
  template <typename T>
  class list {
  private:
    T *data;
    uint32_t mylen;
    uint32_t mycap;

  public:
    void resize(uint32_t len) {
      T *buff = new T[len];
      uint32_t max = std::min(mycap, len);

      for (uint32_t i = 0; i < max; i++) {
        buff[i] = data[i];
        mylen++;
      }

      data = buff;
      mycap = len;
    }

    void push(const T &_t) {
      if (mylen + 2 >= mycap) resize(mycap * 1.3);
      data[mylen] = _t;
    }

    T pop() {
      T tmp = data[mylen];
      data[mylen] = T();

      return tmp;
    }

    void fit() {
      resize(mylen);
    }

    list() : data(nullptr), mylen = 0, mycap = 0 {}

    list(uint32_t _s) : data(nullptr), mylen = 0, mycap = _s {
      resize(_s);
    }
  };

}