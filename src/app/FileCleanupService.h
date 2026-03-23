#ifndef FILECLEANUPSERVICE_H
#define FILECLEANUPSERVICE_H

#include <filesystem>
#include <string>
#include <iostream>

class FileCleanupService
{
public:
    void cleanup(const std::string &directory = "output")
    {
        try
        {
            std::filesystem::create_directories(directory);
            std::filesystem::create_directories(directory + "/execution_reps");
            std::filesystem::create_directories(directory + "/order_books");
            std::filesystem::create_directories(directory + "/rejected_execution_reps");

            for (const auto &entry : std::filesystem::recursive_directory_iterator(directory))
            {
                if (!entry.is_regular_file())
                    continue;

                const std::string filename = entry.path().filename().string();
                if (shouldDelete(filename))
                    std::filesystem::remove(entry.path());
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Cleanup error: " << e.what() << std::endl;
        }
    }

private:
    bool shouldDelete(const std::string &filename)
    {
        const bool isCsv = filename.length() >= 4 &&
                           filename.rfind(".csv") == filename.length() - 4;
        bool isOutput = filename.find("execution_rep") == 0 ||
                        filename.find("order_book_") == 0 ||
                        filename.find("rejected_execution_rep") == 0;
        return isCsv && isOutput;
    }
};

#endif