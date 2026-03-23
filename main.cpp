#include "ExchangeApp.h"
#include "CsvOrderReader.h"
#include "SequentialIdGenerator.h"
#include "CsvReportWriter.h"

int main()
{
    CsvOrderReader         reader;
    SequentialIdGenerator  idGen;
    CsvReportWriter        writer;
    CsvRejectedReportWriter rejectedWriter;

    ExchangeApp app(reader, idGen, writer, rejectedWriter);
    app.run("order.csv");

    return 0;
}