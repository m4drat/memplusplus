#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

#include <cstdlib>
#include <random>

#include "mpplib/chunk.hpp"
#include "mpplib/containers/gc_graph.hpp"
#include "mpplib/gc.hpp"
#include "mpplib/memory_manager.hpp"
#include "mpplib/shared_gcptr.hpp"
#include "mpplib/utils/macros.hpp"
#include "mpplib/utils/profiler_definitions.hpp"

using namespace mpp;

template<bool RandomizedLinkedList, bool DoLayout = false>
class Worker
{
public:
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

    SharedGcPtr<ListNode> m_LinkedListHead;
    uint32_t m_LinkedListSize;
    uint64_t m_xorshiftSeed;

    Worker(uint32_t t_LinkedListSize, uint64_t t_xorshiftSeed = 0x133796A5FF21B3C1)
        : m_LinkedListSize(t_LinkedListSize)
        , m_xorshiftSeed(t_xorshiftSeed)
    {
        if constexpr (RandomizedLinkedList) {
            m_LinkedListHead = CreateRandomizedLinkedList(t_LinkedListSize);
        } else {
            m_LinkedListHead = CreateLayoutedLinkedList(t_LinkedListSize);
        }
    }

    Worker(const Worker&) = delete;
    Worker(Worker&&) = delete;
    Worker& operator=(const Worker&) = delete;
    Worker& operator=(Worker&&) = delete;
    ~Worker() = default;

    uint32_t DoBenchmark()
    {
        SharedGcPtr<ListNode>& current = m_LinkedListHead;

        while (current->next != nullptr) {
            current->data = current->data ^ current->next->data ^ 0x1337AF12;
            current = current->next;
        }

        return current->data;
    }

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

        std::shuffle(
            std::begin(nodes), std::end(nodes), std::default_random_engine(m_xorshiftSeed));

        for (uint32_t i = 0; i < size - 1; ++i) {
            nodes[i]->next = nodes[i + 1];
        }

        return nodes[0];
    }
};

void logic()
{
    using namespace mpp;

    Worker<true, false> worker(8);
    std::cout << worker.DoBenchmark() << std::endl;

    std::cout << "Before GC" << std::endl;
    g_memoryManager->VisHeapLayout(std::cout, nullptr);
    // Iterate linked list
    auto head = worker.m_LinkedListHead;
    while (head != nullptr) {
        std::cout << head << head->index << " " << head->data << std::endl;
        head = head->next;
    }

    // CollectGarbage();

    std::cout << "After GC" << std::endl;
    g_memoryManager->VisHeapLayout(std::cout, nullptr);
    // Iterate linked list
    head = worker.m_LinkedListHead;
    while (head != nullptr) {
        std::cout << head << head->index << " " << head->data << std::endl;
        head = head->next;
    }

    std::cout << std::endl;

    SharedGcPtr<Worker<true, false>::ListNode>* newHead = &worker.m_LinkedListHead;
    while (newHead->Get() != nullptr) {
        std::cout << *newHead << newHead->Get()->index << " " << newHead->Get()->data << std::endl;
        newHead = &newHead->Get()->next;
    }

    head = nullptr;
    worker.m_LinkedListHead = nullptr;

    // MM::VisHeapLayout(std::cout, nullptr);
    // GC::GetInstance().Collect();
    // MM::VisHeapLayout(std::cout, nullptr);
}

int main()
{
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

    SharedGcPtr<ListNode> ptr = MakeShared<ListNode>(0, 0x1337);
    ptr->next = MakeShared<ListNode>(1, 0xdead);

    std::cout << ptr << '\n';
    std::cout << ptr->next << '\n';

    g_memoryManager->VisHeapLayout(std::cout, ptr.Get());

    CollectGarbage();

    ptr = ptr->next;

    return 0;
}