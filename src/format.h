/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>

namespace spectral {


class format {
public:
  format() = default;
  virtual ~format() = default;

  virtual void Read( const std::string &FileName ) = 0;
  virtual void Write( const std::string &FileName ) = 0;
};


} /* End of 'spectral' namespace */
