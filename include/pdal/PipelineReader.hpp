/******************************************************************************
* Copyright (c) 2011, Michael P. Gerlek (mpg@flaxen.com)
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

#ifndef INCLUDED_PIPELINEREADER_HPP
#define INCLUDED_PIPELINEREADER_HPP

#include <pdal/pdal.hpp>
#include <pdal/StageFactory.hpp>

#include <vector>
#include <string>


namespace pdal
{

class Options;
class PipelineManager;

class PDAL_DLL PipelineReader
{
private:
    class StageParserContext;

public:
    PipelineReader(PipelineManager&);
    ~PipelineReader();

   
    // Use this to fill in a pipeline manager with an XML file that
    // contains a <Writer> as the last pipeline stage.
    void readWriterPipeline(const std::string&);

    // Use this to fill in a pipeline manager with an XML file that 
    // don't contain a <Writer>.  (Even though this is called "parse 
    // READER pipeline", it actually returns a Stage; it can be used 
    // where the last pipeline stage is a Reader or Filter.)
    void readReaderPipeline(const std::string&);

private:
    Writer* parseElement_WriterPipeline(const boost::property_tree::ptree&);
    Stage* parseElement_ReaderPipeline(const boost::property_tree::ptree&);
    Stage* parseElement_anystage(const std::string& name, const boost::property_tree::ptree& subtree);
    Reader* parseElement_Reader(const boost::property_tree::ptree& tree);
    Filter* parseElement_Filter(const boost::property_tree::ptree& tree);
    MultiFilter* parseElement_MultiFilter(const boost::property_tree::ptree& tree);
    Writer* parseElement_Writer(const boost::property_tree::ptree& tree);

    Option<std::string> parseElement_Option(const boost::property_tree::ptree& tree);
    std::string parseElement_Type(const boost::property_tree::ptree& tree);

private:
    PipelineManager& m_manager;

    PipelineReader& operator=(const PipelineReader&); // not implemented
    PipelineReader(const PipelineReader&); // not implemented
};


} // namespace pdal

#endif
