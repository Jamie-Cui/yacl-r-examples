// Copyright 2022 Ant Group Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "0001-dpf/dpf.h"
#include "0001-dpf/ss.h"
#include "benchmark/benchmark.h"

#include "yacl/utils/parallel.h"

namespace yacl::crypto::examples {

constexpr uint128_t first_mk = 0;
constexpr uint128_t second_mk = 1;

template <size_t IN_BITS, size_t OUT_BITS>
static void BM_DpfSSA(benchmark::State& state) {
  // place holder
  DpfKey k0;
  DpfKey k1;

  // main loop
  for (auto _ : state) {
    state.PauseTiming();

    auto num = state.range(0);

    // setup input
    auto alpha = GE2n<IN_BITS>(0);
    auto beta = GE2n<OUT_BITS>(1);

    // start
    state.ResumeTiming();

    for (auto i = 0; i < num; ++i) {
      DpfKeyGen(&k0, &k1, alpha, beta, first_mk, second_mk, false);
    }

    // setup context
  }
}

static void BM_SS_SSA(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    auto num = state.range(0);
    auto data0 = std::vector<uint64_t>(num, 0);
    auto data1 = std::vector<uint64_t>(num, 1);

    auto data0_s0 = std::vector<uint64_t>(num);
    auto data0_s1 = std::vector<uint64_t>(num);

    auto data1_s0 = std::vector<uint64_t>(num);
    auto data1_s1 = std::vector<uint64_t>(num);

    auto compare = std::vector<uint64_t>(num);

    Share(absl::MakeConstSpan(data0), absl::MakeSpan(data0_s0),
          absl::MakeSpan(data0_s1));

    Share(absl::MakeConstSpan(data1), absl::MakeSpan(data1_s0),
          absl::MakeSpan(data1_s1));

    state.ResumeTiming();

    auto precision = 100;
    auto block = num / precision;
    auto count = 0;

    // parallel_for(0, num, [&](int64_t beg, int64_t end) {
    //   for (int64_t i = beg; i < end; ++i) {
    // if (i > count * block) {
    //   SPDLOG_INFO("[{}/{}]", count, precision);
    //   count++;
    // }
    Aggregate(absl::MakeSpan(data0_s0), absl::MakeSpan(data1_s0));
    Aggregate(absl::MakeSpan(data0_s1), absl::MakeSpan(data1_s1));
    //   }
    // });
  }
}

// BENCHMARK(BM_DpfSSA<10, 64>)->Unit(benchmark::kMillisecond)->Arg(1024);
// BENCHMARK(BM_DpfSSA<15, 64>)->Unit(benchmark::kMillisecond)->Arg(1024);
// BENCHMARK(BM_DpfSSA<20, 64>)->Unit(benchmark::kMillisecond)->Arg(1024);
// BENCHMARK(BM_DpfSSA<24, 64>)->Unit(benchmark::kMillisecond)->Arg(1024);
BENCHMARK(BM_SS_SSA)->Unit(benchmark::kMillisecond)->Arg(1 << 24);

}  // namespace yacl::crypto::examples
