#include <benchmark/benchmark.h>
#include "utils.hpp"
#include "parser_v2.hpp"

struct HandlerV2 {
    uint64_t messages = 0;

    void handle(const ITCHv2::Message& msg) {
        messages++;
    }
};

static void BM_Parse_v2(benchmark::State& state) {
    static std::vector<std::byte> buf = load_chunk(1 * 1024 * 1024);

    ITCHv2::ItchParser parser;

    for (auto _ : state) {
        HandlerV2 handler{};
        parser.parse(buf.data(), buf.size(), handler);

        benchmark::DoNotOptimize(handler.messages);
    }
}

BENCHMARK(BM_Parse_v2);

