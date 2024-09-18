# Project_Normal_Template

This is a C program template tailored for:

- GCC, GDB, MAKE, VALGRING and DOXYGEN
- VS CODE editor

## What's included?

### CSV Files

The following *comma separaved value* (CSV) files contain all information that must be imported:

- `csv_data/country_vaccinations.csv` - Vaccination data by country/date (no order given)

- `csv_data/country_data_2020.csv` - Country information; updated information at 2020.

The file `csv_data/country_vaccinations_sorted.txt` illustrates the type of data you'll be working with, ordered by country/date.

You **must use** the "unordered" version, i.e., the `csv` file.

#### Reading CSV files

You have examples on *parsing* CSV files in the course repositories.

Some **useful notes**:

- Be aware that you should *right trim* each CSV line before *tokenizing* the *string* (see `rtrim`), because there are usually some unwanted characters at the end of each line read, e.g., *newlines* and *carriage returns*.

- The `atof` function expects the decimal point as a *point* `.`; some values have commas as the
decimal point, i.e., `,`. You should use the provided `replace` function to convert them.

### Abstract Data Types

Includes the **ADT List** and **ADT Map** to support the project's development.

For each ADT, two implementations are provided: based on *array list* and *linked list*. You should choose the "best" implementation at compile time.

### Miscellaneous utilities

The following modules are provided; they can be extended/modified, if you wish:

- **`date`** module: date manipulation; includes `addDaysToDate` and `daysDiffDate` functions

- **`input`** module: for user data input, includes an updated `splitString` function which automatically deals with *windows/linux* CSV line terminations.

- **`stringutils`** module: includes some utilitary functions, namely `rtrim` and `replace`.
  
