/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <stdint.h>

#include "format_riff.h"

namespace spectral {
namespace format {
namespace chunk {


class wav_format : public riff::chunk_t {
public:
  static const dword Tag = ' ' << 24 | 't' << 16 | 'm' << 8 | 'f';  // "fmt "
  word Format, NumOfChannels, BlockAlign;
  dword SamplingRate, AverageBPS;
  std::unique_ptr<byte[]> SpecificFields;

  class factory : public chunk_t::factory {
  public:
    factory() = default;
    virtual ~factory() = default;
    virtual std::shared_ptr<chunk_t> Create( dword ID, dword Size ) const override;
  };
  friend factory;

  virtual ~wav_format() = default;
  virtual void Clear() override;
  virtual void Write( FILE *File ) const override;
  virtual void Read( FILE *File ) override;

protected:
  wav_format( dword ID, dword Size );
};


class wav_data : public riff::chunk_t {
public:
  static const int32_t Tag = 'a' << 24 | 't' << 16 | 'a' << 8 | 'd';  // "data"
  std::unique_ptr<byte[]> Data;

  class factory : public chunk_t::factory {
  public:
    factory() = default;
    virtual ~factory() = default;
    virtual std::shared_ptr<chunk_t> Create( dword ID, dword Size ) const override;
  };
  friend factory;

  virtual ~wav_data() = default;
  virtual void Clear() override;
  virtual void Write( FILE *File ) const override;
  virtual void Read( FILE *File ) override;

protected:
  wav_data( dword ID, dword Size );
};


} /* End of 'chunk' namespace */
} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
