#pragma once

#include "gtest/gtest.h"

#include "mpplib/memory_manager.hpp"

class AllocatorTest : public ::testing::Test
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

class SharedGcPtrTest : public ::testing::Test
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

class SharedGcArrayTests : public ::testing::Test
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
