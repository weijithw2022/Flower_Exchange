#ifndef GENERATECSV_H
#define GENERATECSV_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class GenerateCSV
{
private:
    std::string filename;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;

public:
    GenerateCSV(const std::string &fileName) : filename(fileName) {}

    void setHeaders(const std::vector<std::string> &headerList)
    {
        headers = headerList;
    }

    void addRow(const std::vector<std::string> &rowData)
    {
        rows.push_back(rowData);
    }

    bool writeCSV()
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        // Write headers
        if (!headers.empty())
        {
            for (std::size_t i = 0; i < headers.size(); ++i)
            {
                file << headers[i];
                if (i < headers.size() - 1)
                {
                    file << ",";
                }
            }
            file << "\n";
        }

        for (const auto &row : rows)
        {
            for (std::size_t i = 0; i < headers.size(); ++i)
            {
                if (i < row.size())
                {
                    file << escapeCSVField(row[i]);
                }
                if (i < headers.size() - 1)
                {
                    file << ",";
                }
            }
            file << "\n";
        }

        file.close();
        std::cout << "CSV file '" << filename << "' generated successfully with " << rows.size() << " rows" << std::endl;
        return true;
    }

    void clear()
    {
        headers.clear();
        rows.clear();
    }
    std::size_t getRowCount() const { return rows.size(); }

private:
    std::string escapeCSVField(const std::string &field)
    {
        if (field.find(',') != std::string::npos ||
            field.find('"') != std::string::npos ||
            field.find('\n') != std::string::npos)
        {
            std::string escaped = "\"";
            for (char c : field)
            {
                if (c == '"')
                {
                    escaped += "\"\""; // Escape quotes by doubling them
                }
                else
                {
                    escaped += c;
                }
            }
            escaped += "\"";
            return escaped;
        }
        return field;
    }
};

#endif