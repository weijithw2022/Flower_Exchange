#ifndef GENERATECSV_H
#define GENERATECSV_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

class GenerateCSV {
private:
    string filename;
    vector<string> headers;
    vector<vector<string>> rows;
    
public:
    GenerateCSV(const string& fileName) : filename(fileName) {}
    
    void setHeaders(const vector<string>& headerList) {
        headers = headerList;
    }
    
    void addRow(const vector<string>& rowData) {
        rows.push_back(rowData);
    }
    
    bool writeCSV() {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return false;
        }
        
        // Write headers
        if (!headers.empty()) {
            for (size_t i = 0; i < headers.size(); ++i) {
                file << headers[i];
                if (i < headers.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        
        for (const auto& row : rows) {
            for (size_t i = 0; i < headers.size(); ++i) {
                if (i < row.size()) {
                    file << escapeCSVField(row[i]);
                }
                if (i < headers.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        
        file.close();
        cout << "CSV file '" << filename << "' generated successfully with " << rows.size() << " rows" << endl;
        return true;
    }
    
    void clear() {headers.clear();rows.clear();}
    int getRowCount() const {return rows.size();}


private:
    string escapeCSVField(const string& field) {
        if (field.find(',') != string::npos || 
            field.find('"') != string::npos || 
            field.find('\n') != string::npos) {
            string escaped = "\"";
            for (char c : field) {
                if (c == '"') {
                    escaped += "\"\"";  // Escape quotes by doubling them
                } else {
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