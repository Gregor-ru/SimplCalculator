#include "pluginLoader.h"
#include <windows.h>
#include <iostream>

void loadPlugins(std::map<std::string, Plugin>& plugins) {
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(L"./plugins/*.dll", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Плагины не найдены." << std::endl;
        return;
    }

    do {
        std::wstring dllPath = L"./plugins/" + std::wstring(findFileData.cFileName);
        HMODULE hModule = LoadLibraryW(dllPath.c_str());

        if (hModule) {
            auto getPluginName = (const char* (*)())GetProcAddress(hModule, "getPluginName");
            auto getArgumentCount = (int(*)())GetProcAddress(hModule, "getArgumentCount");
            auto getSyntax = (const char* (*)())GetProcAddress(hModule, "getSyntax");
            auto execute = (double(*)(double*))GetProcAddress(hModule, "execute");

            if (getPluginName && getArgumentCount && getSyntax && execute) {
                Plugin plugin;
                plugin.name = getPluginName();
                plugin.argCount = getArgumentCount();
                plugin.syntax = getSyntax();
                plugin.execute = execute;
                plugins[plugin.name] = plugin;
                std::cout << "Загружен плагин: " << plugin.name << std::endl;
            }
            else {
                std::wcerr << L"Ошибка загрузки функций из " << findFileData.cFileName << std::endl;
            }
        }
        else {
            std::wcerr << L"Ошибка загрузки плагина: " << findFileData.cFileName << std::endl;
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
}
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
