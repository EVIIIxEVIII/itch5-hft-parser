#include <benchmark/benchmark.h>
#include <fstream>
#include <vector>
#include <cstddef>
#include <stdexcept>

#include "utils.hpp"

std::vector<std::byte> load_chunk(std::size_t size) {
    std::ifstream file("../data/01302019.NASDAQ_ITCH50", std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open ITCH file");
    }

    std::vector<std::byte> buf(size);
    file.read(reinterpret_cast<char*>(buf.data()),
              static_cast<std::streamsize>(buf.size()));
    buf.resize(static_cast<std::size_t>(file.gcount()));
    return buf;
}

