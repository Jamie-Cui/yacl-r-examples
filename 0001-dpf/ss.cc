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

#include "yacl/base/exception.h"
#include "yacl/crypto/rand/rand.h"

namespace yacl::crypto::examples {

void Share(absl::Span<const uint64_t> weights, absl::Span<uint64_t> share1,
           absl::Span<uint64_t> share2) {
  YACL_ENFORCE(weights.size() == share1.size());
  YACL_ENFORCE(weights.size() == share2.size());

  FillRand(reinterpret_cast<char*>(share1.data()),
           sizeof(uint64_t) * share1.size());

  for (auto i = 0; i < weights.size(); ++i) {
    share2[i] = weights[i] - share1[i];
  }
}

void Aggregate(absl::Span<uint64_t> model, absl::Span<const uint64_t> weights) {
  YACL_ENFORCE(weights.size() == model.size());
  for (auto i = 0; i < model.size(); ++i) {
    model[i] += weights[i];
  }
}

void Reconstruct(absl::Span<uint64_t> out, absl::Span<const uint64_t> lhf,
                 absl::Span<const uint64_t> rhf) {
  YACL_ENFORCE(out.size() == lhf.size());
  YACL_ENFORCE(out.size() == rhf.size());
  for (auto i = 0; i < out.size(); ++i) {
    out[i] = lhf[i] + rhf[i];
  }
}

}  // namespace yacl::crypto::examples
