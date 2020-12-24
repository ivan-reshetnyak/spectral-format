/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include "format.h"

namespace spectral {
namespace format {


class raw : public format_t {
public:
  using buffer = std::unique_ptr<byte[]>;
  raw() = default;
  virtual ~raw() = default;

  virtual void Read( const std::string &FileName ) override;
  virtual byte Get();
  virtual void Get( buffer Buffer );
  virtual buffer && Transfer();
  virtual void Write( const std::string &FileName ) const override;
  virtual void Set( buffer &&Buffer );
};


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
