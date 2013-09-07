/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:set ts=2 sw=2 sts=2 et cindent: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef FFTBlock_h_
#define FFTBlock_h_

#include "nsTArray.h"
#include "AudioNodeEngine.h"
#include "kiss_fft/kiss_fftr.h"

namespace mozilla {

// This class defines an FFT block, loosely modeled after Blink's FFTFrame
// class to make sharing code with Blink easy.
// Currently it's implemented on top of KissFFT on all platforms.
class FFTBlock {
public:
  explicit FFTBlock(uint32_t aFFTSize)
    : mFFT(nullptr)
    , mIFFT(nullptr)
    , mFFTSize(aFFTSize)
  {
    MOZ_COUNT_CTOR(FFTBlock);
    mOutputBuffer.SetLength(aFFTSize / 2 + 1);
    PodZero(mOutputBuffer.Elements(), aFFTSize / 2 + 1);
  }
  ~FFTBlock()
  {
    MOZ_COUNT_DTOR(FFTBlock);
    Clear();
  }

  // Return a new FFTBlock with frequency components interpolated between
  // |block0| and |block1| with |interp| between 0.0 and 1.0.
  static FFTBlock*
  CreateInterpolatedBlock(const FFTBlock& block0,
                          const FFTBlock& block1, double interp);

  void PerformFFT(const float* aData)
  {
    EnsureFFT();
    kiss_fftr(mFFT, aData, mOutputBuffer.Elements());
  }
  void PerformInverseFFT(float* aData)
  {
    EnsureIFFT();
    kiss_fftri(mIFFT, mOutputBuffer.Elements(), aData);
    for (uint32_t i = 0; i < mFFTSize; ++i) {
      aData[i] /= mFFTSize;
    }
  }
  void Multiply(const FFTBlock& aFrame)
  {
    BufferComplexMultiply(reinterpret_cast<const float*>(mOutputBuffer.Elements()),
                          reinterpret_cast<const float*>(aFrame.mOutputBuffer.Elements()),
                          reinterpret_cast<float*>(mOutputBuffer.Elements()),
                          mFFTSize / 2 + 1);
  }

  void PerformPaddedFFT(const float* aData, size_t dataSize)
  {
    MOZ_ASSERT(dataSize <= FFTSize());
    nsTArray<float> paddedData;
    paddedData.SetLength(FFTSize());
    PodCopy(paddedData.Elements(), aData, dataSize);
    PodZero(paddedData.Elements() + dataSize, mFFTSize - dataSize);
    PerformFFT(paddedData.Elements());
  }

  void SetFFTSize(uint32_t aSize)
  {
    mFFTSize = aSize;
    mOutputBuffer.SetLength(aSize / 2 + 1);
    PodZero(mOutputBuffer.Elements(), aSize / 2 + 1);
    Clear();
  }

  // Return the average group delay and removes this from the frequency data.
  double ExtractAverageGroupDelay();

  uint32_t FFTSize() const
  {
    return mFFTSize;
  }
  float RealData(uint32_t aIndex) const
  {
    return mOutputBuffer[aIndex].r;
  }
  float ImagData(uint32_t aIndex) const
  {
    return mOutputBuffer[aIndex].i;
  }

private:
  FFTBlock(const FFTBlock& other) MOZ_DELETE;
  void operator=(const FFTBlock& other) MOZ_DELETE;

  void EnsureFFT()
  {
    if (!mFFT) {
      mFFT = kiss_fftr_alloc(mFFTSize, 0, nullptr, nullptr);
    }
  }
  void EnsureIFFT()
  {
    if (!mIFFT) {
      mIFFT = kiss_fftr_alloc(mFFTSize, 1, nullptr, nullptr);
    }
  }
  void Clear()
  {
    free(mFFT);
    free(mIFFT);
    mFFT = mIFFT = nullptr;
  }
  void AddConstantGroupDelay(double sampleFrameDelay);
  void InterpolateFrequencyComponents(const FFTBlock& block0,
                                      const FFTBlock& block1, double interp);

  kiss_fftr_cfg mFFT, mIFFT;
  nsTArray<kiss_fft_cpx> mOutputBuffer;
  uint32_t mFFTSize;
};

}

#endif
