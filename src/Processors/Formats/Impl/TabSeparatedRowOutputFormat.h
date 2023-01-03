#pragma once

#include <Core/Block.h>
#include <Formats/FormatSettings.h>
#include <Processors/Formats/IRowOutputFormat.h>
#include <IO/WriteBufferFromString.h>


namespace DB
{

class WriteBuffer;

/** A stream for outputting data in tsv format.
  */
class TabSeparatedRowOutputFormat : public IRowOutputFormat
{
public:
    /** with_names - output in the first line a header with column names
      * with_types - output the next line header with the names of the types
      */
    TabSeparatedRowOutputFormat(
        WriteBuffer & out_,
        const Block & header_,
        bool with_names_,
        bool with_types_,
        bool is_raw_,
        const FormatSettings & format_settings_);

    String getName() const override { return "TabSeparatedRowOutputFormat"; }

    /// https://www.iana.org/assignments/media-types/text/tab-separated-values
    String getContentType() const override { return "text/tab-separated-values; charset=UTF-8"; }

protected:
    void writeField(const IColumn & column, const ISerialization & serialization, size_t row_num) override;
    void writeFieldDelimiter() override final;
    void writeRowBetweenDelimiter() override;

    bool supportTotals() const override { return true; }
    bool supportExtremes() const override { return true; }

    void writeBeforeTotals() override final;
    void writeAfterTotals() override final;
    void writeBeforeExtremes() override final;
    void writeAfterExtremes() override final;

    void writePrefix() override;
    void writeSuffix() override;
    void writeLine(const std::vector<String> & values);

    bool with_names;
    bool with_types;
    bool is_raw;
    const FormatSettings format_settings;
};

}
