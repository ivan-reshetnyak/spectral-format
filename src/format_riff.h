/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <cstdio>
#include <stdint.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "format.h"

namespace spectral {
namespace format {


class riff : public format_t {
public:
  using buffer = std::shared_ptr<byte[]>;


  class chunk_t {
  public:
    class factory {
    public:
      factory() = default;
      virtual ~factory() = default;
      virtual std::shared_ptr<chunk_t> Create( dword ID, dword Size ) const = 0;
    };
    friend factory;


    virtual ~chunk_t() = default;
    virtual void Clear();
    virtual void Write( FILE *File ) const = 0;
    virtual void Read( FILE *File ) = 0;
    void SkipPadByte( FILE *File ) const;
    void AddPadByte( FILE *File ) const;

  protected:
    dword ID, Size;
    chunk_t( dword ID, dword Size );
  };


  riff();
  riff( std::shared_ptr<chunk_t::factory> DefaultFactory );
  virtual ~riff() = default;
  virtual void Read( const std::string &FileName ) override;
  virtual void Write( const std::string &FileName ) const override;
  riff & operator<<( const std::pair<dword, std::shared_ptr<chunk_t::factory>> &CustomChunk );
  std::shared_ptr<chunk_t> Produce( dword ID, dword Size ) const;

protected:
  std::vector<std::shared_ptr<chunk_t>> Chunks;
  std::unordered_map<dword, std::shared_ptr<chunk_t::factory>> CustomChunks;
  std::shared_ptr<chunk_t::factory> DefaultFactory;
};


namespace chunk {


class unknown final : public riff::chunk_t {
public:
  class factory final : public chunk_t::factory {
  public:
    factory() = default;
    virtual ~factory() = default;
    std::shared_ptr<chunk_t> Create( dword ID, dword Size ) const;
  };
  friend factory;

  ~unknown() = default;
  void Clear() final override;
  virtual void Write( FILE *File ) const final override;
  virtual void Read( FILE *File ) final override;

private:
  unknown( dword ID, dword Size );
  std::unique_ptr<byte[]> Data;
};


/*
class riff : public ::spectral::format::riff::chunk_t {
public:
  class factory final : public chunk_t::factory {
  public:
    factory() = default;
    virtual ~factory() = default;
    std::shared_ptr<chunk_t> Create( dword ID, dword Size ) const;
  };
  friend factory;

  ~riff() = default;
  void Clear() final override;
  virtual void Write( FILE *File ) const override;
  virtual void Read( FILE *File ) override;

protected:
  riff( dword ID, dword Size );
};
*/


} /* End of 'chunk' namespace */
} /* End of 'format' namespace */
} /* End of 'spectral' namespace */
