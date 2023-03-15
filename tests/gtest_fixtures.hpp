#pragma once

#include "gtest/gtest.h"

#include "mpplib/memory_manager.hpp"

class MppTestBase : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mpp::g_memoryManager = std::make_unique<mpp::MemoryManager>();
    }

    void TearDown() override
    {
        mpp::g_memoryManager.reset();
    }
};

class AllocatorTest : public MppTestBase
{};

class SharedGcPtrTest : public MppTestBase
{};

class SharedGcArrayTests : public MppTestBase
{};

class GcTest : public MppTestBase
{};

class AsanTest : public MppTestBase
{};