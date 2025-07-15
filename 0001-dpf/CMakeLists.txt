# Copyright 2025 Jamie Cui
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

add_library(dpf STATIC ${CMAKE_CURRENT_LIST_DIR}/dpf.cc
                       ${CMAKE_CURRENT_LIST_DIR}/dpf.h)

target_include_directories(dpf PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
target_link_libraries(dpf PUBLIC Deps::yacl Deps::fmt)

# dpf test

add_executable(dpf_test ${CMAKE_CURRENT_LIST_DIR}/dpf_test.cc)
target_link_libraries(dpf_test PRIVATE dpf Deps::gtest)
add_test(NAME dpf_test COMMAND dpf_test)

# dpf benchmark

add_executable(dpf_bench ${CMAKE_CURRENT_LIST_DIR}/dpf_bench.cc)
target_link_libraries(dpf_bench PRIVATE dpf Deps::yacl Deps::benchmark)
add_test(NAME dpf_bench COMMAND dpf_bench)
