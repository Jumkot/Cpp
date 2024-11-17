#include "normpath.hpp"

std::string normpath(const std::string& path)
{
    if (path.empty() || path[0] != '/') {
        throw std::invalid_argument("invalid argument, not an absolute path");
    }

    if (path.find(' ') != std::string::npos) {
        throw std::domain_error("domain_error, spaces are not allowed");
    }

    std::vector<std::string> components;
    const std::string_view path_view = path;
    size_t start = 1;

    while (start < path.size()) {
        const size_t end = path.find('/', start);
        const std::string_view part = path_view.substr(start, end - start);

        if (part == "..") {
            if (!components.empty()) {
                components.pop_back();
            } else {
                throw std::runtime_error(
                        "runtime_error, cannot normalize path");
            }
        } else if (part != "." && !part.empty()) {
            components.push_back(std::string(part));
        }

        if (end == std::string::npos)
            break;
        start = end + 1;
    }

    std::string result = "/";
    for (const auto& comp : components) {
        result += comp + "/";
    }
    if (result.size() > 1)
        result.pop_back();

    return result;
}