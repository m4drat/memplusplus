#include "gtest/gtest.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mpplib/chunk.hpp"
#include "mpplib/memory_manager.hpp"

#include "gtest_fixtures.hpp"

TEST_F(AllocatorTest, InvalidFree)
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

    // InvalidFree
    EXPECT_EXIT({ Deallocate((void*)0xdeadbeef); },
                [](int status) {
                    // With Valgrind, the exit status is 1, without it is SIGABRT
                    return (WIFSIGNALED(status) && WTERMSIG(status) == SIGABRT) ||
                           WEXITSTATUS(status) == 1;
                },
                "Invalid pointer deallocation detected!");
}
