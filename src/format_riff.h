/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cstdio>
#include <stdint.h>

#include <memory>
#include <vector>

#include "def.h"
#include "format.h"

namespace spectral {
namespace format {


class riff : public format_t {
public:
  class subchunk {
  public:
    int32_t ID, Size;
    void *Data;

    virtual void Write( FILE *File ) const {
      fwrite(&ID, sizeof(ID), 1, File);
      fwrite(&Size, sizeof(Size), 1, File);
      fwrite(Data, Size / BitsInByte, 1, File);
    }
  };

  class chunk {
  public:
    int32_t ID, Size, Format;
    std::vector<std::shared_ptr<subchunk>> Subchunks;

    virtual void Write( FILE *File ) const {
      fwrite(&ID, sizeof(ID), 1, File);
      fwrite(&Size, sizeof(Size), 1, File);
      fwrite(&Format, sizeof(Format), 1, File);
      for (const auto &Subchunk : Subchunks)
        Subchunk->Write(File);
    }
  };

  riff() = default;
  virtual ~riff() = default;

  virtual void Read( const std::string &FileName ) override {
    // TODO
  }


  virtual void Write( const std::string &FileName ) override {
    FILE *File = fopen(FileName.c_str(), "wb");
    Chunk->Write(File);
    fclose(File);
  }

protected:
  std::shared_ptr<chunk> Chunk;
};


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
