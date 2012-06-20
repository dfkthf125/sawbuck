// Copyright 2012 Google Inc.
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

#include "syzygy/pe/transforms/add_pdb_info_transform.h"

#include "gtest/gtest.h"
#include "syzygy/block_graph/typed_block.h"
#include "syzygy/core/unittest_util.h"
#include "syzygy/pe/decomposer.h"
#include "syzygy/pe/unittest_util.h"

namespace pe {
namespace transforms {

using block_graph::TypedBlock;

namespace {

const FilePath kPdbPath(L"dummy.pdb");
const uint32 kPdbAge = 0;
const GUID kPdbGuid = { 0x11111111, 0x2222, 0x3333,
                        { 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB } };

class AddPdbInfoTransformTest : public testing::PELibUnitTest {
 public:
  AddPdbInfoTransformTest()
      : image_layout_(&block_graph_),
        dos_header_block_(NULL) {
  }

  ImageLayout image_layout_;
  BlockGraph block_graph_;
  BlockGraph::Block* dos_header_block_;
};

}  // namespace

TEST_F(AddPdbInfoTransformTest, UpdateExisting) {
  PEFile pe_file;
  ASSERT_TRUE(pe_file.Init(testing::GetExeRelativePath(kDllName)));

  Decomposer decomposer(pe_file);
  ASSERT_TRUE(decomposer.Decompose(&image_layout_));

  dos_header_block_ = image_layout_.blocks.GetBlockByAddress(
      core::RelativeAddress(0));
  ASSERT_TRUE(dos_header_block_ != NULL);

  AddPdbInfoTransform transform(kPdbPath, kPdbAge, kPdbGuid);
  EXPECT_TRUE(block_graph::ApplyBlockGraphTransform(
      &transform, &block_graph_, dos_header_block_));

  // TODO(chrisha): Create the image and the PDB in a temp directory and
  //     see if pe::FindPdbForModule can find it. If so, then so will the
  //     debug machinery.
}

TEST_F(AddPdbInfoTransformTest, CreateNew) {
  // Create some empty dummy headers and hook them up.
  dos_header_block_ = block_graph_.AddBlock(
      BlockGraph::DATA_BLOCK, sizeof(IMAGE_DOS_HEADER), "Dos Header");
  ASSERT_TRUE(dos_header_block_ != NULL);
  dos_header_block_->AllocateData(sizeof(IMAGE_DOS_HEADER));

  BlockGraph::Block* nt_headers_block = block_graph_.AddBlock(
      BlockGraph::DATA_BLOCK, sizeof(IMAGE_NT_HEADERS), "Nt Headers");
  ASSERT_TRUE(nt_headers_block != NULL);
  nt_headers_block->AllocateData(sizeof(IMAGE_NT_HEADERS));

  dos_header_block_->SetReference(
      offsetof(IMAGE_DOS_HEADER, e_lfanew),
      BlockGraph::Reference(BlockGraph::RELATIVE_REF,
                            sizeof(core::RelativeAddress),
                            nt_headers_block,
                            0, 0));


  AddPdbInfoTransform transform(kPdbPath, kPdbAge, kPdbGuid);
  EXPECT_TRUE(block_graph::ApplyBlockGraphTransform(
      &transform, &block_graph_, dos_header_block_));
}

}  // namespace transforms
}  // namespace pe
