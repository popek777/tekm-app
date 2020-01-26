#pragma once

#include <string>

namespace https {
std::string get(const std::string& host, const std::string& port,
                const std::string& target);

}  // namespace https
