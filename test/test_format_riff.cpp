#include <cstdio>

#include <CppUnitTest.h>

#include "format.h"
#include "format_riff.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace spectral {
namespace test {


TEST_CLASS(test_format_riff) {
public:
  bool TestCopy( format::riff &File ) {
    std::string 
      FileNameIn = SolutionDir "assets/wav_1m.wav",
      FileNameOut = SolutionDir "out/wav_1m.wav";

    File.Read(FileNameIn);
    File.Write(FileNameOut);

    FILE
      *FileIn = fopen(FileNameIn.c_str(), "rb"),
      *FileOut = fopen(FileNameOut.c_str(), "rb");

    if (FileOut == nullptr) {
      fclose(FileOut);
      return false;
    }
    fseek(FileIn, 0, SEEK_END);
    int FInSize = ftell(FileIn);
    fseek(FileIn, 0, SEEK_SET);
    fseek(FileOut, 0, SEEK_END);
    int FOutSize = ftell(FileOut);
    fseek(FileOut, 0, SEEK_SET);

    if (FInSize != FOutSize) {
      fclose(FileOut);
      fclose(FileIn);
      return false;
    }

    format::byte
      *BufIn = new format::byte[FInSize],
      *BufOut = new format::byte[FInSize];
    fread(BufIn, sizeof(format::byte) * FInSize, 1, FileIn);
    fread(BufOut, sizeof(format::byte) * FInSize, 1, FileOut);
    for (int i = 0; i < FInSize; ++i)
      if (BufIn[i] != BufOut[i]) {
        fclose(FileOut);
        fclose(FileIn);
        return false;
      }

    fclose(FileOut);
    fclose(FileIn);
    return true;
  }

  TEST_METHOD(TestRWDefault) {
    format::riff File;
    Assert::IsTrue(TestCopy(File));
  }


  TEST_METHOD(TestRWRIFF) {
    format::riff File;
    File << std::make_pair<>(format::chunk::riff::Tag, std::make_shared<format::chunk::riff::factory>(File));
    Assert::IsTrue(TestCopy(File));
  }
};


} /* End of 'test' namespace */
} /* End of 'spectral' namespace */
