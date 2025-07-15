# Copyright 2024 Jamie Cui
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ExternalProject_Add(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.4.tar.gz
  URL_HASH
    SHA256=b334658edd35efcf06a99d9be21e4e93e092bd5f95074c1673d5c8705d95c104
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_DEPS_PREFIX} #
             -DBENCHMARK_ENABLE_GTEST_TESTS=Off -DBENCHMARK_USE_BUNDLED_GTEST=On
  PREFIX ${CMAKE_DEPS_PREFIX}
  EXCLUDE_FROM_ALL true
  DOWNLOAD_EXTRACT_TIMESTAMP On
  LOG_DOWNLOAD On
  LOG_CONFIGURE On
  LOG_BUILD On
  LOG_INSTALL On)

import_static_lib_from(libbenchmark benchmark)
import_static_lib_from(libbenchmark_main benchmark)

target_link_libraries(libbenchmark_main INTERFACE libbenchmark)

# -----------------------------
# Alias Target for External Use
# -----------------------------
add_library(Deps::benchmark ALIAS libbenchmark_main)
