/******************************************************************************
* Copyright (c) 2018, Kyle Mann (kyle@hobu.co)
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

#include "I3SReader.hpp"
#include "EsriUtil.hpp"
#include <thread>

namespace pdal
{

static PluginInfo const i3sInfo
{
    "readers.i3s",
    "I3S Reader",
    "http://pdal.io/stages/readers.i3s.html"
};

CREATE_SHARED_STAGE(I3SReader, i3sInfo)

std::string I3SReader::getName() const { return i3sInfo.name; }

void I3SReader::initInfo()
{
    try
    {
        m_info = EsriUtil::parse(m_arbiter->get(m_filename));

        if (m_info.empty())
            throwError(std::string("Incorrect Json object"));
        if (!m_info.contains("layers"))
            throwError(std::string("Json object contains no layers"));

        m_info = m_info["layers"][0];
    }
    catch(EsriUtil::json_parse_error& e)
    {
        throwError(std::string("Error parsing Json object: ") + e.what());
    }

    m_filename += "/layers/0";
}


NL::json I3SReader::fetchJson(std::string filepath)
{
    return EsriUtil::parse(m_arbiter->get(filepath));
}


std::vector<char> I3SReader::fetchBinary(std::string url,
    std::string attNum, std::string ext) const
{
    const int NumRetries(5);
    int retry = 0;

    // For the REST I3S endpoint there are no file extensions.
    std::vector<char> result;
    while (true)
    {
        auto data = m_arbiter->tryGetBinary(url + attNum);
        if (data)
        {
            result = std::move(*data);
            break;
        }
        if (++retry == NumRetries)
            throwError(std::string("Failed to fetch: " + url + attNum));
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return result;
}

} //namespace pdal
