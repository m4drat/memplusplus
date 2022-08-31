#include "gtest/gtest.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"

TEST(AsanIntegrationTests, DISABLED_UseAfterFreeRead)
{
    using namespace mpp;

    uint64_t* p1 = (uint64_t*)MM::Allocate(128);
    *p1 = 0x1337133791237482;
    void* p2 = MM::Allocate(128);

    MM::Deallocate(p1);

    EXPECT_EXIT({ volatile bool res = *(uint64_t*)p1 == 0x1337133791237482; },
                testing::KilledBySignal(SIGABRT),
                "UseAfterFreeRead detected!");
}

TEST(AsanIntegrationTests, DISABLED_UseAfterFreeWrite)
{
    using namespace mpp;

    uint64_t* p1 = (uint64_t*)MM::Allocate(128);
    *p1 = 0x1337133791237482;
    void* p2 = MM::Allocate(128);

    MM::Deallocate(p1);

    EXPECT_EXIT({ *p1 = 0x1234567812345678; },
                testing::KilledBySignal(SIGABRT),
                "UseAfterFreeWrite detected!");
}
