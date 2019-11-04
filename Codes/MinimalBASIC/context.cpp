#include "context.h"

void Context::setVar(const QString &identifier, int value) {
    vars.insert(identifier, value);
}

int Context::getVar(const QString &identifier) const {
    return vars.value(identifier);
}

bool Context::isDefined(const QString &identifier) const {
    return vars.contains(identifier);
}
