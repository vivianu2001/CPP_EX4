//umanskyvivian@gmail.com
#ifndef VALUE_TO_QSTRING_HPP
#define VALUE_TO_QSTRING_HPP

#include <QString>
#include "complex.hpp"

template <typename T>
inline QString valueToQString(const T& value) {
    return QString::number(value);
}

// Specialization for Complex type
inline QString valueToQString(const Complex& value) {
    return value.toQString();
}

#endif // VALUE_TO_QSTRING_HPP
