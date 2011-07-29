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

#include <pdal/PipelineWriter.hpp>

#include <pdal/Filter.hpp>
#include <pdal/MultiFilter.hpp>
#include <pdal/Reader.hpp>
#include <pdal/Writer.hpp>
#include <pdal/PipelineManager.hpp>

#include <pdal/drivers/las/Reader.hpp>
#include <pdal/drivers/las/Writer.hpp>
#include <pdal/drivers/liblas/Reader.hpp>
#include <pdal/drivers/liblas/Writer.hpp>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/optional.hpp>

namespace pdal
{
    
PipelineWriter::PipelineWriter(const PipelineManager& manager)
    : m_manager(manager)
{

    return;
}


PipelineWriter::~PipelineWriter()
{
    return;
}


static boost::property_tree::ptree generateTreeFromWriter(const Writer& writer)
{
    boost::property_tree::ptree subtree = writer.generatePTree();

    boost::property_tree::ptree tree;

    tree.add_child("WriterPipeline", subtree);

    return tree;
}


void PipelineWriter::writeWriterPipeline(const std::string& filename) const
{
    const Writer* writer = m_manager.getWriter();
    
    boost::property_tree::ptree tree = generateTreeFromWriter(*writer);

    
    const boost::property_tree::xml_parser::xml_writer_settings<char> settings(' ', 4);
    boost::property_tree::xml_parser::write_xml(filename, tree, std::locale(), settings);

    return;
}


} // namespace pdal
