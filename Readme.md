# CSV Parser with Automatic Primary Key/Foreign Key Detection

This is a C++ library for parsing CSV files and automatically connecting different files with primary keys/foreign keys
to each other. The library provides a simple and efficient way to process and manipulate CSV files, making it easy to
work with large data sets.

## Features

- Parse CSV files with customizable delimiters, quotes, and escape characters.
- Automatically detect primary keys and foreign keys in CSV files, and connect them to other files with matching keys.
- Classify the data types of columns in CSV files, including boolean, integer, double, UUID, string, and date.


## Usage

To use the CSV parser, include the csv_parser.hpp header file in your C++ code:

```cpp
#include <fx/csv_parser.hpp>
```

The `CSVFile` class represents a CSV file, and can be used to read and write data to and from the file:

```cpp
// Read a CSV file
CSVFile file("data.csv");
CSVHeader header = file.getHeader();
for (CSVRow row : file) {
// process row data
}

// Write a CSV file
CSVFile output("output.csv", {
"col1", "col2", "col3"
});
CSVRow row = { "value1", 2, 3.14 };
output.addRow(row);

```
The library provides a CSVParser class that can be used to automatically connect different CSV files with primary
keys/foreign keys. To use this feature, create a CSVParser object and add the files you want to connect:

```cpp
CSVParser parser;

// Add files to the parser
parser.addFile("orders.csv");
parser.addFile("customers.csv");

// Connect files using primary key/foreign key relationships
parser.connectFiles("orders.csv", "order_id", "customers.csv", "customer_id");
```
The `getLinkedRows` method takes the name of the connected file as its argument, and returns a vector of CSVRow objects representing the linked rows in the connected file.

## Requirements

- C++11 or higher
- Boost C++ Libraries (1.58 or higher)

## License

This library is licensed under the MIT License. See the LICENSE file for details.