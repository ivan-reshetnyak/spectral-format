/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#include "pch.h"

#include "format_riff.h"

namespace spectral {
namespace format {


riff::chunk_t::chunk_t( dword ID, dword Size ) : ID(ID), Size(Size) {
}


void riff::chunk_t::Clear() {
  ID = (dword)0;
  Size = (dword)0;
}


void riff::chunk_t::SkipPadByte( FILE *File ) const {
  if (Size % 2 == 1)
    fseek(File, 1, SEEK_CUR);
}


void riff::chunk_t::AddPadByte( FILE *File ) const {
  if (Size % 2 == 1) {
    byte Pad;
    fwrite(&Pad, sizeof(Pad), 1, File);
  }
}


riff::riff() : DefaultFactory(std::make_shared<chunk::unknown::factory>()) {
  this->operator<<(std::make_pair<>(chunk::riff::Tag, std::make_shared<chunk::riff::factory>(*this)));
}


riff::riff( std::shared_ptr<chunk_t::factory> DefaultFactory ) : DefaultFactory(DefaultFactory) {
}


void riff::Read( const std::string &FileName ) {
  FILE *File = fopen(FileName.c_str(), "rb");
  if (File == nullptr)
    return;

  fseek(File, 0, SEEK_END);
  int FileSize = ftell(File);
  fseek(File, 0, SEEK_SET);
  while (ftell(File) < FileSize) {
    dword ID, Size;
    fread(&ID, sizeof(ID), 1, File);
    fread(&Size, sizeof(Size), 1, File);

    auto NewChunk = Produce(ID, Size);
    NewChunk->Read(File);
    Chunks.push_back(NewChunk);
  }
  fclose(File);
}


void riff::Write( const std::string &FileName ) const {
  FILE *File = fopen(FileName.c_str(), "wb");
  if (File == nullptr)
    return;

  for (const auto &Chunk : Chunks)
    Chunk->Write(File);
  fclose(File);
}


riff & riff::operator<<( const mapping::value_type &CustomChunk ) {
  CustomChunks.insert(CustomChunk);
  return *this;
}


std::shared_ptr<riff::chunk_t> riff::Produce( dword ID, dword Size ) const {
  auto Factory = CustomChunks.find(ID);
  if (Factory != CustomChunks.end())
    return Factory->second->Create(ID, Size);
  return DefaultFactory->Create(ID, Size);
}


namespace chunk {


std::shared_ptr<::spectral::format::riff::chunk_t> unknown::factory::Create( format::dword ID, format::dword Size ) const {
  return std::shared_ptr<unknown>(new unknown(ID, Size));
}


void unknown::Clear() {
  chunk_t::Clear();
  Data = nullptr;
}


void unknown::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  fwrite(&Data[0], sizeof(Data[0]) * Size, 1, File);
  AddPadByte(File);
}


void unknown::Read( FILE *File ) {
  Data = std::make_unique<byte[]>(Size);
  fread(&Data[0], sizeof(Data[0]) * Size, 1, File);
  SkipPadByte(File);
}


unknown::unknown( dword ID, dword Size ) : chunk_t(ID, Size) {
}


riff::factory::factory( const ::spectral::format::riff &Mapping ) : Mapping(Mapping) {
}


std::shared_ptr<::spectral::format::riff::chunk_t> riff::factory::Create( dword ID, dword Size ) const {
  return std::shared_ptr<riff>(new riff(Mapping, ID, Size));
}


void riff::Clear() {
  chunk_t::Clear();
  Subchunks.clear();
}


void riff::Write( FILE *File ) const {
  fwrite(&ID, sizeof(ID), 1, File);
  fwrite(&Size, sizeof(Size), 1, File);
  fwrite(&Format, sizeof(Format), 1, File);
  for (const auto &Subchunk : Subchunks)
    Subchunk->Write(File);
  AddPadByte(File);
}


void riff::Read( FILE *File ) {
  fread(&Format, sizeof(Format), 1, File);

  int BytesRead = sizeof(Format);
  while (BytesRead < Size) {
    dword ID, Size;
    fread(&ID, sizeof(ID), 1, File);
    fread(&Size, sizeof(Size), 1, File);

    auto NewSubchunk = Mapping.Produce(ID, Size);
    NewSubchunk->Read(File);
    Subchunks.push_back(NewSubchunk);
    BytesRead += sizeof(ID) + sizeof(Size) + Size + Size % 2;
  }
  SkipPadByte(File);
}


riff::riff( const ::spectral::format::riff &Mapping, dword ID, dword Size ) :
    chunk_t(ID, Size), Mapping(Mapping) {
}


} /* End of 'chunk' namespace */
} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
