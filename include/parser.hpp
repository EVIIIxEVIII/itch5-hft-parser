#pragma once

#include <cstddef>

class ItchParser {
public:

    template <typename Handler>
    void parse(std::byte const *  src, size_t len, Handler& visitor);
private:

};
