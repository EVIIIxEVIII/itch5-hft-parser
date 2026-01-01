#include "parser_v1.hpp"
#include "utils.hpp"
#include <benchmark/benchmark.h>

struct HandlerV1 {
    uint64_t messages = 0;

    void handle(const ITCHv1::Message& msg) {
        messages++;
    }
};

static void BM_Parse_v1(benchmark::State& state) {
    static std::vector<std::byte> buf = load_chunk(1 * 1024 * 1024);

    ITCHv1::ItchParser parser;

    for (auto _ : state) {
        HandlerV1 handler;
        parser.parse(buf.data(), buf.size(), handler);

        benchmark::DoNotOptimize(handler);
    }
}

BENCHMARK(BM_Parse_v1);
