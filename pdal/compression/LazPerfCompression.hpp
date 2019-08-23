/******************************************************************************
* Copyright (c) 2014, Howard Butler (howard@hobu.co)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/
#pragma once

#include "Compression.hpp"

#include <pdal/DimType.hpp>

namespace pdal
{

class LazPerfCompressorImpl;

class LazPerfCompressor : public Compressor
{
public:
    PDAL_EXPORT LazPerfCompressor(BlockCb cb, const DimTypeList& dims);
    PDAL_EXPORT ~LazPerfCompressor();

    PDAL_EXPORT void compress(const char *buf, size_t bufsize);
    PDAL_EXPORT void done();

private:
    std::unique_ptr<LazPerfCompressorImpl> m_impl;
};


class LazPerfDecompressorImpl;

// NOTE - The LazPerfDecompressor is different from others, even though the
//   interface is the same, in that it always executes the callback after
//   a point's worth of data is read.
class LazPerfDecompressor : public Decompressor
{
public:
    PDAL_EXPORT LazPerfDecompressor(BlockCb cb, const DimTypeList& dims,
        size_t numPoints);
    PDAL_EXPORT ~LazPerfDecompressor();

    PDAL_EXPORT void decompress(const char *buf, size_t bufsize);

private:
    std::unique_ptr<LazPerfDecompressorImpl> m_impl;
};

} // namespace pdal

