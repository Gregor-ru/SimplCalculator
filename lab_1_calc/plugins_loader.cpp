#include "plugins_loader.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#error "Только для Windows!"
#endif

PluginsLoader::PluginsLoader(const std::string& directory) : directory(directory) {}

void PluginsLoader::loadPlugins() {
    bool pluginFound = false;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".dll") {
            pluginFound = true;
            loadPlugin(entry.path().string());
        }
    }

    if (!pluginFound) {
        std::cerr << "Внимание: не найдено ни одного плагина. Используются только встроенные функции." << std::endl;
    }
}

void PluginsLoader::loadPlugin(const std::string& path) {
#ifdef _WIN32
    HMODULE hModule = LoadLibraryA(path.c_str());
    if (!hModule) {
        std::cerr << "Ошибка загрузки плагина: " << path << ". Код ошибки: " << GetLastError() << std::endl;
        return;
    }

    auto getName = (const char* (*)())GetProcAddress(hModule, "getFunctionName");
    auto getArgCount = (int (*)())GetProcAddress(hModule, "getArgumentCount");
    auto execFunc = (double (*)(double*))GetProcAddress(hModule, "executeFunction");

    if (getName && getArgCount && execFunc) {
        std::string funcName = getName();
        int argCount = getArgCount();

        functions[funcName] = [execFunc, argCount](const std::vector<double>& args) -> double {
            if (args.size() != argCount) {
                throw std::invalid_argument("Неправильное количество аргументов для функции.");
            }
            return execFunc(const_cast<double*>(args.data()));
            };

        argumentCountMap[funcName] = argCount;
        std::cout << "Загружен плагин: " << funcName << " (аргументов: " << argCount << ")" << std::endl;
    }
    else {
        std::cerr << "Ошибка: не найдены нужные функции в плагине: " << path << std::endl;
        FreeLibrary(hModule);
    }
#endif
}

const std::unordered_map<std::string, Function>& PluginsLoader::getFunctionsMap() const {
    return functions;
}

const std::unordered_map<std::string, int>& PluginsLoader::getArgumentsMap() const {
    return argumentCountMap;
}
