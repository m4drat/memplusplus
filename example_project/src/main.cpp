#include <iostream>

#include "mpplib/shared_gcptr.hpp"
#include "mpplib/containers/chunk_treap.hpp"

int main(int argc, char* argv[])
{
    using namespace mpp;

    ChunkTreap* cTreap = new ChunkTreap();

    Chunk* ch1 = (Chunk*)malloc(128);
    Chunk* ch2 = (Chunk*)malloc(128);
    Chunk* ch3 = (Chunk*)malloc(128);
    Chunk* ch4 = (Chunk*)malloc(128);
    Chunk* ch5 = (Chunk*)malloc(128);
    Chunk* ch6 = (Chunk*)malloc(128);
    Chunk* ch7 = (Chunk*)malloc(128);
    Chunk* ch8 = (Chunk*)malloc(128);
    Chunk* ch9 = (Chunk*)malloc(128);
    
    ch1->SetSize(16);
    std::cout << ch1 << std::endl;
    ch2->SetSize(16);

    cTreap->InsertChunk(ch1);
    cTreap->InsertChunk(ch2);

    // Print(cTreap->GetRoot());

    cTreap->RemoveChunk(ch1);

    // Print(cTreap->GetRoot());

    return 0;
}