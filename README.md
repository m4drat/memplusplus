# mem++

### Этапы разработки:
1. Основные структуры (chunk, arena)
2. Системный аллокатор (враппер над mmap)
3. Базовый менеджмент free'd блоков (LinkedList + first-fit с разделением чанков) 
4. Ручная реализация ф-ции free
5. __Тесты для пунктов 1-4__
6. Advanced менеджмент free'd блоков (segregated-fit)
7. Реализация умных указателей для GC
8. Базовая версия GC (ф-ция вида gc.collect())
9. __Тесты для пунктов 6-8__
10. Advanced версия GC - распознование структур (Уметь находить Связные списки, Деревья поиска)
11. Advanced версия GC - менеджмент свободных чанков (Во время копирования структуры (например linked list): необходимо попытаться разместить его ноды в памяти друг за другом)
12. Advanced версия GC - доработка для работы с другими структурами (деревья поиска)
13. __Тесты для пунктов 10-12__

### Техническая спецификация
1. Free-list аллокатор памяти (или построенный на bitmap). Аллокатор сам по себе типа: best-fit/segregated-fit.
2. умный GC типа "mark and sweep", или "reference count", который будет пытаться распределить объекты в памяти опираясь на тип структуры, которую они реализуют.

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
---
24. Cmake intro: https://www.youtube.com/watch?v=wl2Srog-j7I
25. Cmake library intro: https://www.youtube.com/watch?v=5i6uLMP5VcY
26. Cmake library example project: https://github.com/YansonTech/Introduction-to-libraries-with-CMake
27. How to structurize project: https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
28. Structure of cmake project: https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
-----
29. Diving into windows memory allocator: https://www.corelan.be/index.php/2016/07/05/windows-10-x86wow64-userland-heap/
30. Segment heap internals (windows): https://www.blackhat.com/docs/us-16/materials/us-16-Yason-Windows-10-Segment-Heap-Internals.pdf
31. Windows 10 Nt Heap Exploitation: https://www.slideshare.net/AngelBoy1/windows-10-nt-heap-exploitation-english-version