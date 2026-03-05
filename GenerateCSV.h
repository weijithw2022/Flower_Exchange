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
    vector<map<string, string>> rows;
    
public:
    GenerateCSV(const string& fileName) : filename(fileName) {}
    
    void setHeaders(const vector<string>& headerList) {
        headers = headerList;
    }
    
    void addRow(const map<string, string>& rowData) {
        rows.push_back(rowData);
        
        if (headers.empty()) {
            for (const auto& pair : rowData) {
                headers.push_back(pair.first);
            }
        }
    }
    
    void addRows(const vector<map<string, string>>& rowsData) {
        for (const auto& row : rowsData) {
            addRow(row);
        }
    }
    
    bool writeCSV() {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << " for writing" << endl;
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
                auto it = row.find(headers[i]);
                if (it != row.end()) {
                    file << escapeCSVField(it->second);
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
    
    void clear() {
        headers.clear();
        rows.clear();
    }
    
    int getRowCount() const {
        return rows.size();
    }
    
    // Display preview of data
    void displayPreview(int maxRows = 5) {
        cout << "\n=== CSV Preview ===" << endl;
        cout << "File: " << filename << endl;
        cout << "Headers: ";
        for (size_t i = 0; i < headers.size(); ++i) {
            cout << headers[i];
            if (i < headers.size() - 1) cout << ", ";
        }
        cout << endl;
        
        cout << "Data (" << min((int)rows.size(), maxRows) << " of " << rows.size() << " rows):" << endl;
        for (int i = 0; i < min((int)rows.size(), maxRows); ++i) {
            for (size_t j = 0; j < headers.size(); ++j) {
                auto it = rows[i].find(headers[j]);
                if (it != rows[i].end()) {
                    cout << it->second;
                }
                if (j < headers.size() - 1) cout << " | ";
            }
            cout << endl;
        }
        cout << "===================" << endl;
    }

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