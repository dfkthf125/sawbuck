// Copyright 2013 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "syzygy/agent/asan/nested_heap.h"

#include <algorithm>

#include "base/bits.h"
#include "gtest/gtest.h"
#include "syzygy/agent/asan/asan_heap.h"
#include "syzygy/agent/asan/asan_rtl_impl.h"
#include "syzygy/agent/asan/asan_runtime.h"
#include "syzygy/agent/asan/asan_shadow.h"
#include "syzygy/agent/asan/unittest_util.h"
#include "syzygy/common/align.h"

namespace agent {
namespace asan {

namespace {

class NestedHeapTest : public testing::Test {
 public:
  void SetUp() OVERRIDE {
    testing::Test::SetUp();
    runtime_.SetUp(std::wstring());
    agent::asan::SetUpRtl(&runtime_);
  }

  void TearDown() OVERRIDE {
    agent::asan::TearDownRtl();
    runtime_.TearDown();
    testing::Test::TearDown();
  }

  static const size_t kMaxAlignment = 2048;
  static const size_t kBufferSize = kMaxAlignment * 2;

  bool MemoryRangeIsPoisoned(const uint8* address, size_t size) {
    EXPECT_TRUE(address != NULL);
    for (size_t i = 0; i < size; ++i) {
      if (Shadow::IsAccessible(address + i))
        return false;
    }
    return true;
  }

  bool MemoryRangeIsAccessible(const uint8* address, size_t size) {
    EXPECT_TRUE(address != NULL);
    for (size_t i = 0; i < size; ++i) {
      if (!Shadow::IsAccessible(address + i))
        return false;
    }
    return true;
  }

  AsanRuntime runtime_;

  // The buffer we use internally.
  uint8 buffer[kBufferSize];
};

}  // namespace

TEST_F(NestedHeapTest, IntegrationTest) {
  EXPECT_TRUE(MemoryRangeIsAccessible(buffer, kBufferSize));
  asan_PoisonMemoryRange(buffer, kBufferSize);
  EXPECT_TRUE(MemoryRangeIsPoisoned(buffer, kBufferSize));
  asan_UnpoisonMemoryRange(buffer, kBufferSize);
  EXPECT_TRUE(MemoryRangeIsAccessible(buffer, kBufferSize));

  const size_t kAllocSize = 100;

  for (size_t alignment = Shadow::kShadowGranularity;
       alignment <= kMaxAlignment;
       alignment *= 2) {
    uint8* aligned_buffer = reinterpret_cast<uint8*>(
        common::AlignUp(reinterpret_cast<size_t>(buffer), alignment));
    size_t real_buffer_size = kBufferSize - (aligned_buffer - buffer);

    size_t asan_size = asan_GetAsanObjectSize(kAllocSize, alignment);
    ASSERT_GT(real_buffer_size, asan_size);

    asan_InitializeObject(aligned_buffer, kAllocSize, alignment);

    void* user_pointer = NULL;
    size_t tmp_size = 0;
    asan_GetUserExtent(aligned_buffer, &user_pointer, &tmp_size);
    EXPECT_NE(reinterpret_cast<void*>(NULL), user_pointer);
    EXPECT_EQ(kAllocSize, tmp_size);

    void* asan_pointer = NULL;
    asan_GetAsanExtent(user_pointer, &asan_pointer, &tmp_size);
    EXPECT_EQ(asan_size, tmp_size);
    EXPECT_EQ(reinterpret_cast<void*>(aligned_buffer), asan_pointer);

    asan_QuarantineObject(aligned_buffer);
    EXPECT_TRUE(MemoryRangeIsPoisoned(aligned_buffer, asan_size));

    asan_DestroyObject(aligned_buffer);
    // Destroying the object shouldn't affect the shadow memory.
    EXPECT_TRUE(MemoryRangeIsPoisoned(aligned_buffer, asan_size));

    asan_UnpoisonMemoryRange(aligned_buffer, real_buffer_size);
  }
}

}  // namespace asan
}  // namespace agent
