/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "def.h"
#include "format_riff.h"

namespace spectral {
namespace format {


void riff::subchunk::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  fwrite(Data, Size / BitsInByte, 1, File);
}


void riff::chunk::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  fwrite(&Format, sizeof(Format), 1, File);
  for (const auto &Subchunk : Subchunks)
    Subchunk->Write(File);
}


void riff::Read( const std::string &FileName ) {
  // TODO
}


void riff::Write( const std::string &FileName ) {
  FILE *File = fopen(FileName.c_str(), "wb");
  Chunk->Write(File);
  fclose(File);
}


} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
