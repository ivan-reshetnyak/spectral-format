#include <cstdio>

#include <CppUnitTest.h>

#include "format.h"
#include "format_riff.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace spectral {
namespace test {


TEST_CLASS(test_format_riff) {
public:
  TEST_METHOD(TestRW) {
    format::riff File;
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
      Assert::Fail();
      return;
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
      Assert::Fail();
      return;
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
        Assert::Fail();
        return;
      }

    fclose(FileOut);
    fclose(FileIn);
  }
};


} /* End of 'test' namespace */
} /* End of 'spectral' namespace */
