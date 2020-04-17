#pragma once

#include <memory>
#include <sstream>
#include <vector>

template<typename T>
std::vector<T*> toPtrVector(const std::vector<std::unique_ptr<T>>& vec) {
    std::vector<T*> result;
    for (auto& e : vec) {
        result.push_back(e.get());
    }
    return result;
}

template<typename T>
std::string join(const std::vector<T>& vec, std::string infix) {
    std::stringstream result;
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) result << infix;
        result << vec[i];
    }
    return result.str();
}

template<typename T>
std::string join(const std::vector<T*>& vec, std::string infix) {
    std::stringstream result;
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) result << infix;
        result << *vec[i];
    }
    return result.str();
}
