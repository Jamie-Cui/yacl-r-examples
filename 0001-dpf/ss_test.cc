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

#include "0001-dpf/ss.h"

#include "gtest/gtest.h"

#include "yacl/crypto/rand/rand.h"

namespace yacl::crypto::examples {

TEST(SSTest, ShareAndAggregate) {
  // prepare input
  uint32_t data_size = 1024;
  auto data0 = std::vector<uint64_t>(data_size, 0);
  auto data1 = std::vector<uint64_t>(data_size, 1);

  auto data0_s0 = std::vector<uint64_t>(data_size);
  auto data0_s1 = std::vector<uint64_t>(data_size);

  auto data1_s0 = std::vector<uint64_t>(data_size);
  auto data1_s1 = std::vector<uint64_t>(data_size);

  auto compare = std::vector<uint64_t>(data_size);

  Share(absl::MakeConstSpan(data0), absl::MakeSpan(data0_s0),
        absl::MakeSpan(data0_s1));

  Share(absl::MakeConstSpan(data1), absl::MakeSpan(data1_s0),
        absl::MakeSpan(data1_s1));

  Aggregate(absl::MakeSpan(data0_s0), absl::MakeSpan(data1_s0));
  Aggregate(absl::MakeSpan(data0_s1), absl::MakeSpan(data1_s1));

  Reconstruct(absl::MakeSpan(compare), absl::MakeSpan(data0_s0),
              absl::MakeSpan(data0_s1));

  for (auto i = 0; i < compare.size(); ++i) {
    EXPECT_EQ(compare[i], 1);
  }
}

}  // namespace yacl::crypto::examples
