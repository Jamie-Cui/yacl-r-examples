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

#include "benchmark/benchmark.h"

#include "yacl/crypto/experimental/dpf/dpf.h"

namespace yacl::crypto {

constexpr uint128_t first_mk = 0;
constexpr uint128_t second_mk = 1;

template <size_t IN_BITS, size_t OUT_BITS>
static void BM_DpfGen(benchmark::State& state) {
  // place holder
  DpfKey k0;
  DpfKey k1;

  // main loop
  for (auto _ : state) {
    state.PauseTiming();

    // setup input
    auto alpha = GE2n<IN_BITS>(0);
    auto beta = GE2n<OUT_BITS>(1);

    // start
    state.ResumeTiming();

    // setup context
    DpfKeyGen(&k0, &k1, alpha, beta, first_mk, second_mk, false);
  }
}

BENCHMARK(BM_DpfGen<2, 64>)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_DpfGen<4, 64>)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_DpfGen<8, 64>)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_DpfGen<16, 64>)->Unit(benchmark::kMillisecond);

}  // namespace yacl::crypto
