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

add_library(
  all_src STATIC
  ${CMAKE_CURRENT_LIST_DIR}/dpf_ro.cc ${CMAKE_CURRENT_LIST_DIR}/dpf.cc
  ${CMAKE_CURRENT_LIST_DIR}/ss.cc)

target_include_directories(all_src
                           PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
target_link_libraries(all_src PUBLIC Deps::yacl Deps::fmt)

macro(add_dpf_test NAME)
  add_executable(${NAME} ${NAME}.cc)
  target_link_libraries(${NAME} PRIVATE all_src Deps::absl Deps::yacl
                                        Deps::gtest)
  add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()

# dpf test
add_dpf_test(dpf_ro_test)
add_dpf_test(dpf_test)
add_dpf_test(ss_test)

# dpf ssa_benchmark

add_executable(ssa_benchmark ${CMAKE_CURRENT_LIST_DIR}/ssa_benchmark.cc)
target_link_libraries(ssa_benchmark PRIVATE all_src Deps::yacl Deps::benchmark)
