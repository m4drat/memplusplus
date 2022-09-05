window.BENCHMARK_DATA = {
  "lastUpdate": 1662411367747,
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
      },
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
          "id": "b1db518aa04f321a6e3d0f7654093bab3b51d6c9",
          "message": "Updated unit-tests building",
          "timestamp": "2022-09-05T23:54:37+03:00",
          "tree_id": "7ccf230c41d84b4af50f2d6fb64ae5c231fa571d",
          "url": "https://github.com/m4drat/memplusplus/commit/b1db518aa04f321a6e3d0f7654093bab3b51d6c9"
        },
        "date": 1662411367165,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateDeallocate",
            "value": 56.92085268476107,
            "unit": "ns/iter",
            "extra": "iterations: 12300771\ncpu: 56.910652185948344 ns\nthreads: 1"
          },
          {
            "name": "BM_AllocateSingle",
            "value": 857.5343929763703,
            "unit": "ns/iter",
            "extra": "iterations: 814004\ncpu: 859.7987233478993 ns\nthreads: 1"
          },
          {
            "name": "BM_DeallocateSingle",
            "value": 860.00121428902,
            "unit": "ns/iter",
            "extra": "iterations: 811172\ncpu: 862.7084021637086 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}