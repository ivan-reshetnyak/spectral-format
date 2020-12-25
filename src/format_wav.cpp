/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "format_wav.h"

namespace spectral {
namespace format {


wav::subchunk_audio_format::subchunk_audio_format( int32_t ID, int32_t Size,
                                                   int16_t Tag, int16_t NumOfChannels, int16_t BlockAlign,
                                                   int32_t SamplingRate, int32_t AverageBPS ) :
    Tag(Tag), NumOfChannels(NumOfChannels), BlockAlign(BlockAlign),
    SamplingRate(SamplingRate), AverageBPS(AverageBPS),
    subchunk(ID, Size) {
}


wav::subchunk_audio_format::subchunk_audio_format( int32_t ID,
                                                   int16_t Tag, int16_t NumOfChannels, int16_t BlockAlign,
                                                   int32_t SamplingRate, int32_t AverageBPS ) :
    subchunk_audio_format(ID, DataSize, Tag, NumOfChannels, BlockAlign, SamplingRate, AverageBPS) {
}


wav::subchunk_audio_data::subchunk_audio_data( int32_t NumOfSamples, int32_t SizeOfSample,
                                               int32_t NumOfChannels, void *Data ) :
    NumOfSamples(NumOfSamples), SizeOfSample(SizeOfSample),
    NumOfChannels(NumOfChannels), Data(Data) {
}


void wav::subchunk_audio_data::Write( FILE *File ) const {
  // fwrite()
}

wav::wav() : riff(std::make_shared<chunk_t>()) {
}


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
