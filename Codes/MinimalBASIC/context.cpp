#include "context.h"

void Context::setVar(const QString &identifier, int value) {
    vars.insert(identifier, value);
}

int Context::getVar(const QString &identifier) const {
    return vars.value(identifier);
}

void Context::setOutput(QString output) {
    this->output = output;
}

QString Context::getOutput() {
    return output;
}

bool Context::isDefined(const QString &identifier) const {
    return vars.contains(identifier);
}
