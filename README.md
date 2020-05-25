# mem++

### Технологии:
1. cmake - build system
2. sphnix/doxygen - documentation
3. clang/g++ - compiler
4. clang-format - formatting tool
5. clang-tidy - linting tool
6. catch2 - unit-testing

### Правила форматирования
1. namespace `mpp`
2. Классы - с большой буквы (`GarbageCollector`), Функции - тоже (`Collect(std::size_t)`)
3. Переменные - с маленькой буквы, с необходимыми префиксами (`c_ArenaSizeMax`).  
    |Условие|Префикс|
    |---|:----|
    |приватные члены классов|m_|
    |параметры функций|t_|
    |статичные объекты|s_|
    |глобальные объекты|g_|
    |глобальные константы|c_|
4. Названия .cpp/.hpp файлов с маленькой буквы 

### Псевдокод алгоритма:
```c++
auto rawPtr = MemoryAllocator::Allocate(sizeof(UserData));
// ======================================================== {
    constexpr ARENA_SIZE = 16mb;
    
    class MemoryManager
    {
    private:
        ...
    public:
        static std::vector<Arena*> g_ArenaList; // sorted by addresses list
        ...
    }
    
    class MemoryAllocator : public MemoryManager
    {
    private:
        ...
    public:
        auto Allocate(std::size_t) -> void*;
        ...
    }
    
    struct Chunk
    {
        ...
    }

    struct Arena
    {
        ...

        std::vector<Chunk*> ChunkList; // sorted by addresses list

        void* begin{ nullptr };
        void* end{ nullptr };

        auto Init() -> void;
        auto GetChunk(std::size_t) -> Chunk*;

        ...
    };

    auto MemoryManager::Allocate(std::size_t size) -> void* 
    {
        if (size > ARENA_SIZE) 
        {
            Arena newArena = (Arena*)mmap(size + sizeof(ArenaMetadata));
            newArena->Init();
            Chunk* chunk = newArena->GetChunk(size);
            // Add info about chunk to ChunkList;
            return static_cast<void*>(chunk+sizeof(ChunkMetadata));
        }
        if (First allocation)
        {
            InitEverythingThatWeNeed();
            Arena newArena = (Arena*)mmap(size + sizeof(ArenaMetadata));
            newArena->Init();
            g_ArenaList.push_back(newArena);
        }
        Arena* foundArena = GetArenaWithAtLeastNFreeBytes(size);
        Chunk* chunk = foundArena->GetChunk(size);
        GetCorrespondingArena(chunk)->ChunkList.push_back(chunk);
        return static_cast<void*>(chunk+sizeof(ChunkMetadata));
    }
// } ========================================================

GcPtr<UserData> smartPtr = GcPtr<UserData>(rawPtr);
// ======================================================== {
    template <class T>
    GcPtr(T rawPtr) :
        m_ptrToObj{ rawPtr }
    {
        std::vector<GcPtr*>gcPtrs.push_back(this) // sorted list
        // мы всегда будем знать к какому чанку относится указатель, даже если он сдвинут, т.к. g_ChunkList
        rawPtr->T() // Вызвать конструкто юзер объекта
        Вернуть умный указатель на объект юзеру
    }
// } ========================================================

smartPtr->~GcPtr(); // Destructor gets called
// ======================================================== {
    template <class T>
    ~GcPtr()
    {
        std::vector<GcPtr*>gcPtrs.pop(this); // Удаляем себя из вектора GcPtrs 
        m_ptrToObj->~T() // Вызываем деструктор объекта
    }
// } ========================================================


GC::collect();
// ======================================================== {
    static auto GC::collect() -> void
    {
        Graph graph = new Graph();
        // mark
        for (gcPtr : gcPtrs)
            correspondingChunk = MemoryManager::FindChunk(gcPtr.ptrToData)
            markObject(correspondingChunk)
            graph.AddInfoAboutGraph(correspondingChunk)
            /** Как проверять, что указатель в чанке указывает 
             * 1. Ptr in Heap Range 
             * 2. Ptr in GcPtrs
             */ 

        // sweep
        for(chunk : MemoryManager::g_ChunkList)
            if (chunk.markBit != 1)
                MemoryManager::g_ChunkList.pop(chunk)
                graph.deleteNode(chunk)
            else
                chunk.markBit = 0
// } ========================================================

// ======================================================== {
        // easy compact
        for(chunk : MemoryManager::g_ChunkList)
            MoveChunkToTheLeftSide(chunk)
            for(gcPtr : GcPtrs)
                if chunk.start <= gcPtr <= chunk.end
                    UpdateSmartPointer(chunk)
// } ========================================================

OR

// ======================================================== {
    // Smart compact
    // Группы объектов, например LinkedList
        std::vector<Group> groups = Heuristics::FindStructures(graph)
        for(group : groups) 
        {
            switch (group)
            {
                case Structures::LinkedList:
                    SmartMoveChunksToTheLeftSideAndUpdatePtrs(group);
                    break;
                case Structures::BinaryTree:
                    SmartMoveChunksToTheLeftSideAndUpdatePtrs(group);
                    break;
                case ...:
                    for (chunk : group)
                        MoveChunkToTheLeftSideAndUpdatePtrs(chunk)
                    break;
            }
        }
    }
// } ========================================================
```

### Этапы разработки:
1. Основные структуры (chunk, arena) + Документация!
2. Системный аллокатор (враппер над mmap)
3. Базовый менеджмент free'd блоков (LinkedList + first-fit с разделением чанков) + Документация!
4. Ручная реализация ф-ции move?
5. __Тесты для пунктов 1-4 + Документация__
6. Advanced менеджмент free'd блоков (segregated-fit/best-fit)
7. Реализация умных указателей для GC
8. Базовая версия GC (ф-ция вида gc.collect(), строит граф связей объектов + удаляет те, на которые нету ссылок)
9. __Тесты для пунктов 6-8 + Документация__
10. Advanced версия GC - распознование структур (Уметь находить Связные списки, Деревья поиска)
11. Advanced версия GC - менеджмент свободных чанков (Во время копирования структуры (например linked list): необходимо попытаться разместить его ноды в памяти друг за другом)
12. Advanced версия GC - доработка для работы с другими структурами (деревья поиска)
13. __Тесты для пунктов 10-12 + Документация__

### Техническая спецификация
1. Free-list аллокатор памяти. Аллокатор сам по себе типа: best-fit/segregated-fit.
2. умный GC типа "mark-compact" + "mark and sweep", который будет пытаться распределить объекты в памяти опираясь на тип структуры, которую они реализуют.

### Ссылки
1. Custom allocator in c++: http://dmitrysoshnikov.com/compilers/writing-a-memory-allocator/
2. Mark and sweep GC in c++: http://dmitrysoshnikov.com/compilers/writing-a-mark-sweep-garbage-collector/
3. Memory allocator for custom game engine: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010/
4. Bitmapped memory manager: https://developer.ibm.com/technologies/systems/tutorials/au-memorymanager/
5. CppCon 2017 "How to Write a Custom Allocator": https://www.youtube.com/watch?v=kSWfushlvB8
6. Custom Allocator Tutorial - How-To: https://www.youtube.com/watch?v=pP15kDeXJU0
7. Article about memory allocators in c++: https://www.bogotobogo.com/cplusplus/memoryallocation.php
8. Precise GC in c++: http://oops.math.spbu.ru/papers/gcpp.pdf
9. A garbage collection framework for C++: https://www.codeproject.com/Articles/912/A-garbage-collection-framework-for-C
10. Memory managment with linked lists and bitmaps: http://examradar.com/memory-management-linked-list-bit-maps-questions-answers/
11. Memory Allocator Implementation (next video in series will show how to write GC): https://www.youtube.com/watch?v=74s0m4YoHgM
12. CppCon 2017 Memory Allocators (1/2): https://www.youtube.com/watch?v=nZNd5FjSquk
13. CppCon 2017 Memory Allocators (2/2): https://www.youtube.com/watch?v=CFzuFNSpycI
14. Malloc tutorial: https://danluu.com/malloc-tutorial/
15. Wikipedia article about GC: https://en.wikipedia.org/wiki/Boehm_garbage_collector
16. An introduction to custom allocators in C++: https://www.youtube.com/watch?v=FcpmMmyNNv8
17. examples of custom memory allocators: https://stackoverflow.com/questions/6564516/custom-memory-allocator
18. malloc sources: https://code.woboq.org/userspace/glibc/malloc/malloc.c.html#3034
19. Internals of malloc: https://sourceware.org/glibc/wiki/MallocInternals
20. Different examples of memory allocators: https://github.com/mtrebi/memory-allocators
21. Microsoft version of malloc: https://github.com/microsoft/mimalloc
22. Implementation of malloc: https://github.com/jterrazz/42-malloc
23. Scaling the Go page allocator (about bitmaps): https://go.googlesource.com/proposal/+/refs/changes/57/202857/2/design/35112-scaling-the-page-allocator.md
24. Mark-compact alggorithm description: https://en.wikipedia.org/wiki/Mark-compact_algorithm
25. About heap-compaction: https://stackoverflow.com/questions/2663292/how-does-heap-compaction-work-quickly
26. About mozilla's spidermonkey compacting GC: https://hacks.mozilla.org/2015/07/compacting-garbage-collection-in-spidermonkey/
27. Info about GC's: https://plumbr.io/handbook/what-is-garbage-collection
28. Detailed description of mark-compact: https://stackoverflow.com/questions/59044616/whats-the-mark-compact-algorithm-used-by-hotspot
29. __Amazing presentation about mark-compact__: http://www.cs.tau.ac.il/~maon/teaching/2014-2015/seminar/seminar1415a-lec2-mark-sweep-mark-compact.pdf
30. c++ profiler: https://github.com/yse/easy_profiler
31. custom c++ profiler: https://www.youtube.com/watch?v=xlAH4dbMVnU&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=81
32. __c++ GC__: http://www.devx.com/assets/sourcecode/9928.pdf
33. __Compacting garbage collector implementation in C++0x__: https://stackoverflow.com/questions/4558473/compacting-garbage-collector-implementation-in-c0x
34. Example allocators: https://github.com/tiagovcosta/aquaengine/tree/master/AquaEngine/Core/Allocators
---
1. Cmake intro: https://www.youtube.com/watch?v=wl2Srog-j7I
2. Cmake library intro: https://www.youtube.com/watch?v=5i6uLMP5VcY
3. Cmake library example project: https://github.com/YansonTech/Introduction-to-libraries-with-CMake
4. How to structurize project: https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
5. Structure of cmake project: https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
6. Cmake template project: https://github.com/Barthelemy/CppProjectTemplate
7. Cmake simple example: https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html
8. Configure VScode to debug cmake projects: https://medium.com/audelabs/c-development-using-visual-studio-code-cmake-and-lldb-d0f13d38c563
9. c++ best practices: https://lefticus.gitbooks.io/cpp-best-practices/03-Style.html
10. c++ core guidelines: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md 
11. c++ guide: https://www.youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb
---
1. Diving into windows memory allocator: https://www.corelan.be/index.php/2016/07/05/windows-10-x86wow64-userland-heap/
2. Segment heap internals (windows): https://www.blackhat.com/docs/us-16/materials/us-16-Yason-Windows-10-Segment-Heap-Internals.pdf
3. Windows 10 Nt Heap Exploitation: https://www.slideshare.net/AngelBoy1/windows-10-nt-heap-exploitation-english-version
---
1. Doxygen directives: https://breathe.readthedocs.io/en/latest/directives.html
2. Doxygen advanced directives: https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html
3. c++ and sphinx: https://stackoverflow.com/questions/835043/has-anyone-used-sphinx-to-document-a-c-project
4. basic commenting example (sphinx): https://breathe.readthedocs.io/en/latest/
5. markups (1): https://breathe.readthedocs.io/en/latest/markups.html
6. latex math (2): https://breathe.readthedocs.io/en/latest/latexmath.html
7. groups (3): https://breathe.readthedocs.io/en/latest/groups.html
8. lists (4): https://breathe.readthedocs.io/en/latest/lists.html
9. __Breathe Full documentation__: https://readthedocs.org/projects/breathe/downloads/pdf/latest/
10. How to document using doxygen: https://developer.lsst.io/cpp/api-docs.html
11. Doxygen examples: https://caiorss.github.io/C-Cpp-Notes/Doxygen-documentation.html
12. Doxygen manual: http://www.doxygen.nl/manual/docblocks.html#specialblock
13. __Doxygen doc-comment quick intro__: https://github.com/stan-dev/stan/wiki/How-to-Write-Doxygen-Doc-Comments
