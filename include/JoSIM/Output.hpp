// Copyright (c) 2021 Johannes Delport
// This code is licensed under MIT license (see LICENSE for details)
#ifndef JOSIM_OUTPUT_HPP
#define JOSIM_OUTPUT_HPP

#include "JoSIM/Matrix.hpp"
#include "JoSIM/Misc.hpp"
#include "JoSIM/Simulation.hpp"
#include "JoSIM/Input.hpp"

namespace JoSIM {
class Trace {
  public:
  std::string name_;
  char type_;
  std::vector<float> data_;
  Trace(const std::string &name) {
    name_ = name;
  }
  ~Trace(){};
};

class Output {
  public:
  std::vector<Trace> traces;
  std::vector<float> timesteps;
  Output(){};
  void write_output(const Input &iObj, 
                    Matrix &mObj, 
                    Simulation &sObj);

  void format_csv_or_dat(const std::string &filename, 
                          const char &delimiter,
                          bool argmin = true);

  void format_raw(const std::string &filename, bool argmin = true);

  void format_cout(const bool &argMin);
};
} // namespace JoSIM

#endif
