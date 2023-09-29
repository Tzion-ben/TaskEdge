// TaskFireArc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

bool SetEdgeSearchEngine(const std::wstring& searchEngineURL)
{
    // Path to the Edge Search Provider in the Windows Registry
    const wchar_t* keyPath = L"SOFTWARE\\Policies\\Microsoft\\Edge";

    HKEY hKey;
     LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_SET_VALUE, &hKey);

    if (result != ERROR_SUCCESS)
    {
        std::wcerr << L"Failed to open registry key." << std::endl;
        return false;
    }

    result = RegSetValueExW(hKey, L"DefaultSearchProvider", 0, REG_SZ, (const BYTE*)searchEngineURL.c_str(), (searchEngineURL.size() + 1) * sizeof(wchar_t));

    RegCloseKey(hKey);

    if (result != ERROR_SUCCESS)
    {
        std::wcerr << L"Failed to set registry value." << std::endl;
        return false;
    }

    return true;
}


int main()
{
    std::wstring newSearchEngineURL = L"https://search.yahoo.com/search{google:pathWildcard}?ei={inputEncoding}&fr=crmas_sfp&p=%s"; // Replace with your desired search engine URL format.

    if (SetEdgeSearchEngine(newSearchEngineURL))
    {
        std::wcout << L"Search engine set successfully." << std::endl;
    }
    else
    {
        std::wcerr << L"Failed to set the search engine." << std::endl;
    }

    return 0;
}