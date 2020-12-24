/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <stdint.h>

#include <string>

namespace spectral {
namespace format {


class format_t {
public:
  format_t() = default;
  virtual ~format_t() = default;

  virtual void Read( const std::string &FileName ) = 0;
  virtual void Write( const std::string &FileName ) const = 0;
};


using byte = int8_t;
using word = int16_t;
using dword = int32_t;


static const int BitsInByte = 8;


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
