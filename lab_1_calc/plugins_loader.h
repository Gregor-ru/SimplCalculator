#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

using Function = std::function<double(const std::vector<double>&)>;

class PluginsLoader {
public:
    PluginsLoader(const std::string& directory);

    // Загрузка плагинов из указанной директории
    void loadPlugins();

    // Возвращает карту функций
    const std::unordered_map<std::string, Function>& getFunctionsMap() const;

    // Возвращает информацию о количестве аргументов функции
    const std::unordered_map<std::string, int>& getArgumentsMap() const;

private:
    std::string directory;
    std::unordered_map<std::string, Function> functions;
    std::unordered_map<std::string, int> argumentCountMap;

    // Загрузка отдельного плагина
    void loadPlugin(const std::string& path);
};
