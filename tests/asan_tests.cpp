#include "gtest/gtest.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"

#include "gtest_fixtures.hpp"

TEST_F(AsanTest, DoubleFree)
{
    using namespace mpp;

    std::vector<void*> ptrs;
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(256));
    ptrs.push_back(Allocate(512));
    ptrs.push_back(Allocate(16));
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(256));
    ptrs.push_back(Allocate(512));
    ptrs.push_back(Allocate(1024));
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(2048));
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(128));
    ptrs.push_back(Allocate(128));

    Deallocate(ptrs[0]);
    Deallocate(ptrs[2]);
    Deallocate(ptrs[4]);
    Deallocate(ptrs[6]);
    Deallocate(ptrs[8]);
    Deallocate(ptrs[7]);
    Deallocate(ptrs[10]);
    Deallocate(ptrs[12]);

    // DoubleFree
    EXPECT_EXIT({ Deallocate((void*)ptrs[8]); },
                testing::ExitedWithCode(SIGHUP),
                "AddressSanitizer: use-after-poison on address");
}

TEST_F(AsanTest, UseAfterFreeRead)
{
    using namespace mpp;

    uint64_t* p1 = (uint64_t*)Allocate(128);
    *p1 = 0x1337133791237482;
    void* p2 = Allocate(128);

    Deallocate(p1);

    EXPECT_EXIT({ volatile bool res = *(uint64_t*)p1 == 0x1337133791237482; },
                testing::ExitedWithCode(SIGHUP),
                "READ of size 8");
}

TEST_F(AsanTest, UseAfterFreeWrite)
{
    using namespace mpp;

    uint64_t* p1 = (uint64_t*)Allocate(128);
    *p1 = 0x1337133791237482;
    void* p2 = Allocate(128);

    Deallocate(p1);

    EXPECT_EXIT({ *p1 = 0x1234567812345678; }, testing::ExitedWithCode(SIGHUP), "WRITE of size 8");
}
