#include "context.h"

void Context::set(const QString &identifier, int value) {
    vars.insert(identifier, value);
}

int Context::get(const QString &identifier) const {
    return vars.value(identifier);
}

bool Context::isDefined(const QString &identifier) const {
    return vars.contains(identifier);
}
