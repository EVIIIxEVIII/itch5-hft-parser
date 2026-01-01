#include <benchmark/benchmark.h>
#include <vector>
#include <cstddef>

std::vector<std::byte> load_chunk(std::size_t size);
