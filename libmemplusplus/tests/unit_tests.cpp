// #include "mpplib/mpp.hpp"

// #define CATCH_CONFIG_MAIN
// #include "catch2/catch.hpp"

// TEST_CASE("negative difference")
// {
//     GC gc;

//     char *ptr1 = (char*)(0x1000), *ptr2 = (char*)(0x1020);

//     ptrdiff_t diff = gc.CalcDist(ptr1, ptr2);

//     REQUIRE(diff < 0);
// }

// TEST_CASE("positive difference")
// {
//     GC gc;

//     char *ptr1 = (char*)(0x1000), *ptr2 = (char*)(0x1020);

//     ptrdiff_t diff = gc.CalcDist(ptr2, ptr1);

//     REQUIRE(diff > 0);
// }