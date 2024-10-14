#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>
#include <vector>

struct Plugin {
    std::string name;
    int argCount;
    std::string syntax;
    double (*execute)(double*);
};

double evaluateFunction(const Plugin& plugin, std::vector<double>& args);

#endif // PLUGIN_H
