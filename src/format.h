/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>

namespace spectral {


class format_t {
public:
  format_t() = default;
  virtual ~format_t() = default;

  virtual void Read( const std::string &FileName ) = 0;
  virtual void Write( const std::string &FileName ) = 0;
};


} /* End of 'spectral' namespace */
