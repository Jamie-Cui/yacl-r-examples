# Copyright 2024 Jamie Cui
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

ExternalProject_Add(
  yacl-r
  GIT_REPOSITORY https://github.com/Jamie-Cui/yacl-r.git
  GIT_TAG jamie/dev
  PREFIX ${CMAKE_DEPS_PREFIX}
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_DEPS_PREFIX} -DBUILD_TEST=Off
  # UPDATE_COMMAND "" # HACK no update
  EXCLUDE_FROM_ALL true
  DOWNLOAD_EXTRACT_TIMESTAMP On
  LOG_DOWNLOAD On
  LOG_CONFIGURE On
  LOG_BUILD On
  LOG_INSTALL On)

add_library(libyacl SHARED IMPORTED)
set_target_properties(
  libyacl PROPERTIES IMPORTED_LOCATION
                     ${CMAKE_DEPS_LIBDIR}/libyacl${CMAKE_SHARED_LIBRARY_SUFFIX})
add_dependencies(libyacl yacl-r)

target_include_directories(
  libyacl INTERFACE ${CMAKE_DEPS_INCLUDEDIR}
                    ${CMAKE_DEPS_SRCDIR}/yacl-r-build/deps/include)

# -----------------------------
# Alias Target for External Use
# -----------------------------
add_library(Deps::yacl ALIAS libyacl)

# HACK https://github.com/gabime/spdlog/issues/1897
add_compile_definitions(SPDLOG_FMT_EXTERNAL)

# HACK msgpack read the following macro from cmake definitions
add_compile_definitions(MSGPACK_NO_BOOST)
