window.BENCHMARK_DATA = {
  "lastUpdate": 1662409523984,
  "repoUrl": "https://github.com/m4drat/memplusplus",
  "entries": {
    "Mem++ benchmarks": [
      {
        "commit": {
          "author": {
            "email": "ftri2001@gmail.com",
            "name": "Theodor",
            "username": "m4drat"
          },
          "committer": {
            "email": "ftri2001@gmail.com",
            "name": "Theodor",
            "username": "m4drat"
          },
          "distinct": true,
          "id": "736005fd59f4a929f78f738d7d0681402105f2e5",
          "message": "Moved benchmarking to main repo",
          "timestamp": "2022-09-05T23:24:02+03:00",
          "tree_id": "df934903d5a67627ee36dd1956c2ef12f2d1e972",
          "url": "https://github.com/m4drat/memplusplus/commit/736005fd59f4a929f78f738d7d0681402105f2e5"
        },
        "date": 1662409523683,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateDeallocate",
            "value": 39.9300541368409,
            "unit": "ns/iter",
            "extra": "iterations: 17614437\ncpu: 39.82059716129445 ns\nthreads: 1"
          },
          {
            "name": "BM_AllocateSingle",
            "value": 798.7815746841891,
            "unit": "ns/iter",
            "extra": "iterations: 873333\ncpu: 801.2875959111833 ns\nthreads: 1"
          },
          {
            "name": "BM_DeallocateSingle",
            "value": 800.9242915002363,
            "unit": "ns/iter",
            "extra": "iterations: 869360\ncpu: 804.9362749611913 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}