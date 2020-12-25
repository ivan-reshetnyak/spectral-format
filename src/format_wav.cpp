/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "format_wav.h"

namespace spectral {
namespace format {
namespace chunk {


std::shared_ptr<::spectral::format::riff::chunk_t> wav_format::factory::Create( dword ID, dword Size ) const {
  return std::shared_ptr<wav_format>(new wav_format(ID, Size));
}


void wav_format::Clear() {
  chunk_t::Clear();
  SpecificFields = nullptr;
}


void wav_format::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  int BytesWritten = 0;
  BytesWritten += fwrite(&Format, sizeof(Format), 1, File) * sizeof(Format);
  BytesWritten += fwrite(&NumOfChannels, sizeof(NumOfChannels), 1, File) * sizeof(NumOfChannels);
  BytesWritten += fwrite(&SamplingRate, sizeof(SamplingRate), 1, File) * sizeof(SamplingRate);
  BytesWritten += fwrite(&AverageBPS, sizeof(AverageBPS), 1, File) * sizeof(AverageBPS);
  BytesWritten += fwrite(&BlockAlign, sizeof(BlockAlign), 1, File) * sizeof(BlockAlign);
  if (BytesWritten < Size)
    fwrite(&SpecificFields[0], Size - BytesWritten, 1, File);
  AddPadByte(File);
}


std::ostream & wav_format::Print( std::ostream &Stream ) const {
  return Stream <<
    "fmt chunk with size: " << Size << " bytes begin" << std::endl <<
    "Format: " << Format << "; Number of channels: " << NumOfChannels <<
    "; Block alignment: " << BlockAlign << "; Sample rate: " << SamplingRate <<
    "; Average BPS:" << AverageBPS << "; " << std::endl <<
    Size - CommonFieldSize << " bytes of format-specific fields" << std::endl <<
    "fmt chunk end" << std::endl;
}


void wav_format::Read( FILE *File ) {
  int BytesRead = 0;
  BytesRead += fread(&Format, sizeof(Format), 1, File) * sizeof(Format);
  BytesRead += fread(&NumOfChannels, sizeof(Format), 1, File) * sizeof(NumOfChannels);
  BytesRead += fread(&SamplingRate, sizeof(SamplingRate), 1, File) * sizeof(SamplingRate);
  BytesRead += fread(&AverageBPS, sizeof(AverageBPS), 1, File) * sizeof(AverageBPS);
  BytesRead += fread(&BlockAlign, sizeof(BlockAlign), 1, File) * sizeof(BlockAlign);
  if (BytesRead < Size) {
    SpecificFields = std::make_unique<byte[]>(Size - BytesRead);
    fread(&SpecificFields[0], Size - BytesRead, 1, File);
  }
  SkipPadByte(File);
}


wav_format::wav_format( dword ID, dword Size ) : chunk_t(ID, Size) {
}


std::shared_ptr<::spectral::format::riff::chunk_t> wav_data::factory::Create( dword ID, dword Size ) const {
  return std::shared_ptr<wav_data>(new wav_data(ID, Size));
}


void wav_data::Clear() {
  chunk_t::Clear();
  Data = nullptr;
}


void wav_data::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  if (Data != nullptr)
    fwrite(&Data[0], Size, 1, File);
  AddPadByte(File);
}


std::ostream & wav_data::Print( std::ostream &Stream ) const {
  return Stream << "WAVE chunk with size: " << Size << " bytes" << std::endl;
}


void wav_data::Read( FILE *File ) {
  Data = std::make_unique<byte[]>(Size);
  fread(&Data[0], Size, 1, File);
  AddPadByte(File);
}


wav_data::wav_data( dword ID, dword Size ) : chunk_t(ID, Size) {
}


} /* End of 'chunk' namespace */
} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
