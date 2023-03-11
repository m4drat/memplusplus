#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include <algorithm>
#include <cstdlib>
#include <random>

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/profiler_definitions.hpp"
#include "mpplib/utils/utils.hpp"

using namespace mpp;

template<bool RandomizedLinkedList, bool DoLayout = false>
class Worker
{
public:
    Worker(uint32_t t_LinkedListSize, uint64_t t_xorshiftSeed = 0x133796A5FF21B3C1)
        : m_xorshiftSeed(t_xorshiftSeed)
        , m_LinkedListSize(t_LinkedListSize)
    {
        if constexpr (RandomizedLinkedList) {
            m_LinkedListHead = CreateRandomizedLinkedList(t_LinkedListSize);
        } else {
            m_LinkedListHead = CreateLayoutedLinkedList(t_LinkedListSize);
        }

        if constexpr (DoLayout) {
            CollectGarbage();
        }
    }

    Worker(const Worker&) = delete;
    Worker(Worker&&) = delete;
    Worker& operator=(const Worker&) = delete;
    Worker& operator=(Worker&&) = delete;
    ~Worker() = default;

    void DoCleanup()
    {
        m_LinkedListHead = nullptr;
    }

    uint32_t DoBenchmark()
    {
        // SharedGcPtr<ListNode> current = m_LinkedListHead;

        // while (current->next != nullptr) {
        //     current->data = current->data ^ 0x1337AF12 ^ current->next->data;
        //     current = current->next;
        // }

        // return current->data;

        // mpp::utils::ErrorAbort("TEST!\n");

        SharedGcPtr<ListNode>* current = &m_LinkedListHead;

        while (current->Get()->next.Get() != nullptr) {
            current->Get()->data = current->Get()->data ^ 0x1337AF12 ^ current->Get()->next->data;
            current = &current->Get()->next;
        }

        return current->Get()->data;
    }

private:
    struct alignas(64) ListNode
    {
        uint32_t index;
        uint32_t data;
        SharedGcPtr<ListNode> next;

        ListNode(uint32_t t_index, uint32_t t_data)
            : index(t_index)
            , data(t_data)
            , next(nullptr)
        {
        }
    };

    uint64_t m_xorshiftSeed;
    SharedGcPtr<ListNode> m_LinkedListHead;
    uint32_t m_LinkedListSize;

    SharedGcPtr<ListNode> CreateLayoutedLinkedList(uint32_t size)
    {
        uint32_t data = 0xF7ADF3E1;
        SharedGcPtr<ListNode> head = MakeShared<ListNode>(0, data);
        SharedGcPtr<ListNode> current = head;

        for (uint32_t i = 1; i < size; ++i) {
            data = (data + 0xffffd) % ((2 << 20) + 1);
            current->next = MakeShared<ListNode>(i, data);
            current = current->next;
        }

        return head;
    }

    SharedGcPtr<ListNode> CreateRandomizedLinkedList(uint32_t size)
    {
        std::vector<SharedGcPtr<ListNode>> nodes;
        nodes.reserve(size);
        uint32_t data = 0xF7ADF3E1;

        for (uint32_t i = 0; i < size; ++i) {
            data = (data + 0xffffd) % ((2 << 20) + 1);
            nodes.emplace_back(MakeShared<ListNode>(i, data));
        }

        std::shuffle(std::begin(nodes), std::end(nodes), std::minstd_rand(m_xorshiftSeed));

        for (uint32_t i = 0; i < size - 1; ++i) {
            nodes[i]->next = nodes[i + 1];
        }

        return nodes[0];
    }
};

void leak()
{
    void* p1 = mpp::Allocate(128);
    // mpp::Deallocate(p1);
}

int main()
{
    // MPP_LOG_DBG("Starting main");
    // MPP_LOG_ERROR("Starting main");
    // MPP_LOG_WARN("Starting main");
    // MPP_LOG_INFO("Starting main");

    // Worker<false, true> worker(2048);
    // worker.DoBenchmark();

    leak();

    return 0;
}