#include <Windows.h>
#include <Winspool.h>
#include <iostream>

// Function declaration for adding a printer
BOOL AddPrinterExample(const wchar_t* pszPrinterName, const wchar_t* pszPortName, const wchar_t* pszDriverName);

int main() {
    const wchar_t* printerName = L"My IPP Printer";
    const wchar_t* portName = L"MyPrinterPort"; // Typically, this would be a WSD port.
    const wchar_t* driverName = L"Microsoft XPS Document Writer"; // Replace with your actual printer driver name.

    if (AddPrinterExample(printerName, portName, driverName)) {
        std::wcout << L"Printer added successfully." << std::endl;
    } else {
        std::wcout << L"Failed to add the printer." << std::endl;
    }

    return 0;
}

BOOL AddPrinterExample(const wchar_t* pszPrinterName, const wchar_t* pszPortName, const wchar_t* pszDriverName) {
    PRINTER_INFO_2 PrinterInfo = {0};
    HANDLE hPrinter = NULL;
    DWORD dwNeeded = 0;

    // Fill in the PRINTER_INFO_2 structure for the new printer
    PrinterInfo.pPrinterName = const_cast<LPWSTR>(pszPrinterName);
    PrinterInfo.pPortName = const_cast<LPWSTR>(pszPortName);
    PrinterInfo.pDriverName = const_cast<LPWSTR>(pszDriverName);
    PrinterInfo.pComment = L"Added via C++";
    PrinterInfo.pLocation = L"Office";
    PrinterInfo.Status = PRINTER_STATUS_READY;
    PrinterInfo.Attributes = PRINTER_ATTRIBUTE_LOCAL;
    PrinterInfo.Priority = 1;
    PrinterInfo.DefaultPriority = 1;

    // Add the printer using the Windows API
    hPrinter = AddPrinter(NULL, 2, (LPBYTE)&PrinterInfo);
    if (hPrinter == NULL) {
        // If the function fails, you can get extended error information by calling GetLastError.
        std::wcout << L"AddPrinter failed. Error: " << GetLastError() << std::endl;
        return FALSE;
    }

    // Close the printer handle when done
    ClosePrinter(hPrinter);
    return TRUE;
}
