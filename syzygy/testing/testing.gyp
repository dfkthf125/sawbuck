# Copyright 2013 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

{
  'variables': {
    'chromium_code': 1,
  },
  'targets': [
    {
      'target_name': 'toolchain_paths',
      'type': 'none',
      'msvs_cygwin_shell': 0,
      'sources': [
        'toolchain_paths.gen.template',
      ],
      'actions': [
        {
          'action_name': 'make_toolchain_paths.gen',
          'inputs': [
            '<(src)/syzygy/build/make_toolchain_paths_gen.py',
            '<(src)/syzygy/testing/toolchain_paths.gen.template',
          ],
          'outputs': [
            '<(SHARED_INTERMEDIATE_DIR)/syzygy/testing/toolchain_paths.gen',
          ],
          'action': [
            '<(python_exe)',
            '<(src)/syzygy/build/make_toolchain_paths_gen.py',
            '--input=<(src)/syzygy/testing/toolchain_paths.gen.template',
            '--output='
                '<(SHARED_INTERMEDIATE_DIR)/syzygy/testing/toolchain_paths.gen',
            # We need the trailing slash to get around string escaping issues
            # with the MSVS macros.
            '--vs-install-dir=$(VSInstallDir)\\',
          ],
          'process_outputs_as_sources': 1,
        },
      ],
      'all_dependent_settings': {
        'include_dirs': [
          '<(SHARED_INTERMEDIATE_DIR)',
        ],
      },
    },
    {
      'target_name': 'testing_lib',
      'type': 'static_library',
      'sources': [
        'toolchain.cc',
        'toolchain.h',
      ],
      'dependencies': [
        'toolchain_paths',
        '<(src)/base/base.gyp:base',
        '<(src)/testing/gmock.gyp:gmock',
        '<(src)/testing/gtest.gyp:gtest',
      ],
      'hard_dependency': 1,
    },
  ],
}
