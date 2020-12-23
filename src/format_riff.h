/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cstdio>
#include <stdint.h>

#include <memory>
#include <vector>

#include "format.h"

namespace spectral {
namespace format {


class riff : public format_t {
public:
  class subchunk {
  public:
    int32_t ID, Size;
    void *Data;

    virtual void Write( FILE *File ) const;
  };

  class chunk {
  public:
    int32_t ID, Size, Format;
    std::vector<std::shared_ptr<subchunk>> Subchunks;

    virtual void Write( FILE *File ) const;
  };

  riff() = default;
  virtual ~riff() = default;
  virtual void Read( const std::string &FileName ) override;
  virtual void Write( const std::string &FileName ) override;

protected:
  std::shared_ptr<chunk> Chunk;
};


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
