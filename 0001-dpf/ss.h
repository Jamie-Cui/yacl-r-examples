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

#pragma once

#include "absl/types/span.h"

namespace yacl::crypto::examples {

void Share(absl::Span<const uint64_t> weights, absl::Span<uint64_t> share1,
           absl::Span<uint64_t> share2);

void Aggregate(absl::Span<uint64_t> model, absl::Span<const uint64_t> weights);

void Reconstruct(absl::Span<uint64_t> out, absl::Span<const uint64_t> lhf,
                 absl::Span<const uint64_t> rhf);

}  // namespace yacl::crypto::examples
