/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <stdint.h>

#include "format_riff.h"

namespace spectral {
namespace format {


class wav : public riff {
public:
  class subchunk_audio_format : public riff::subchunk {
  public:
    subchunk_audio_format( int32_t ID, int32_t Size,
                           int16_t Tag, int16_t NumOfChannels, int16_t BlockAlign,
                           int32_t SamplingRate, int32_t AverageBPS );
    subchunk_audio_format( int32_t ID,
                           int16_t Tag, int16_t NumOfChannels, int16_t BlockAlign,
                           int32_t SamplingRate, int32_t AverageBPS );
    virtual ~subchunk_audio_format() = default;
    virtual void Write( FILE *File ) const override;

  protected:
    static const int32_t DataSize = sizeof(int16_t) * 3 + sizeof(int32_t) * 2;
    int16_t Tag, NumOfChannels, BlockAlign;
    int32_t SamplingRate, AverageBPS;
  };


  class subchunk_audio_data : public riff::subchunk {
  public:
    subchunk_audio_data( int32_t NumOfSamples, int32_t SizeOfSample,
                         int32_t NumOfChannels, void *Data );
    virtual ~subchunk_audio_data() = default;
    virtual void Write( FILE *File ) const override;

  protected:
    static const int32_t Tag = 'a' << 24 | 't' << 16 | 'a' << 8 | 'd';  // "data"
    int32_t NumOfSamples, SizeOfSample, NumOfChannels;
    void *Data;
  };


  wav();
  virtual ~wav() = default;
  virtual void Read( const std::string &FileName ) override;
  virtual void Write( const std::string &FileName ) const override;
};


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
