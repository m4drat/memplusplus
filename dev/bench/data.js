window.BENCHMARK_DATA = {
  "lastUpdate": 1666617708076,
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
          "id": "fb5964f6e112b8545561be88d62157d084067a4c",
          "message": "Added .clang-tidy config + whole lot of refactoring",
          "timestamp": "2022-10-23T23:42:47+03:00",
          "tree_id": "b73a48d56e80993e9f4cd3275faabe6067f728c4",
          "url": "https://github.com/m4drat/memplusplus/commit/fb5964f6e112b8545561be88d62157d084067a4c"
        },
        "date": 1666557932263,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 5.060551618263877,
            "unit": "us/iter",
            "extra": "iterations: 133286\ncpu: 5.0696397221008835 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 8.563557660205838,
            "unit": "us/iter",
            "extra": "iterations: 79032\ncpu: 8.572240358333877 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 25.74796739654147,
            "unit": "us/iter",
            "extra": "iterations: 27543\ncpu: 25.701408706380644 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 64.16413670668106,
            "unit": "us/iter",
            "extra": "iterations: 10870\ncpu: 64.1414535418661 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 149.3107647190076,
            "unit": "us/iter",
            "extra": "iterations: 4501\ncpu: 149.25647633859694 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 396.312854999334,
            "unit": "us/iter",
            "extra": "iterations: 1800\ncpu: 396.2188333333542 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1565.7916341998657,
            "unit": "us/iter",
            "extra": "iterations: 462\ncpu: 1565.4658008657223 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 580040.8220000009,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 579546.500000001 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 8.126339583736604,
            "unit": "us/iter",
            "extra": "iterations: 94607\ncpu: 8.128942890060431 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 15.65343307220813,
            "unit": "us/iter",
            "extra": "iterations: 42120\ncpu: 15.653008072170097 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 35.04438783937773,
            "unit": "us/iter",
            "extra": "iterations: 21068\ncpu: 35.001632808038764 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 69.54860148369274,
            "unit": "us/iter",
            "extra": "iterations: 10110\ncpu: 69.54940652820368 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 158.60015918611717,
            "unit": "us/iter",
            "extra": "iterations: 4523\ncpu: 158.63656864911547 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 329.4882732007573,
            "unit": "us/iter",
            "extra": "iterations: 2112\ncpu: 329.4787405302777 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 731.5533070002118,
            "unit": "us/iter",
            "extra": "iterations: 1000\ncpu: 731.4046000000794 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1958.5918864867215,
            "unit": "us/iter",
            "extra": "iterations: 370\ncpu: 1958.8567567568132 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 3.8936296509066293,
            "unit": "us/iter",
            "extra": "iterations: 179293\ncpu: 3.893099563284683 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 7.656923052139399,
            "unit": "us/iter",
            "extra": "iterations: 90009\ncpu: 7.655736648557378 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 15.456076802299997,
            "unit": "us/iter",
            "extra": "iterations: 45220\ncpu: 15.451001769128698 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 30.67197191058577,
            "unit": "us/iter",
            "extra": "iterations: 23710\ncpu: 30.668194854491944 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 58.42994570623258,
            "unit": "us/iter",
            "extra": "iterations: 12064\ncpu: 58.42220656498666 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 116.85466649413547,
            "unit": "us/iter",
            "extra": "iterations: 5796\ncpu: 116.83726708074592 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 241.56821684282332,
            "unit": "us/iter",
            "extra": "iterations: 2933\ncpu: 241.5331742243419 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 490.0313795864041,
            "unit": "us/iter",
            "extra": "iterations: 1499\ncpu: 489.97184789859733 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"",
            "value": 361.55101050849225,
            "unit": "ms/iter",
            "extra": "iterations: 2\ncpu: 363.24819999908084 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"",
            "value": 764.6575479896853,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 767.3025000002199 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"",
            "value": 1146.5327990059109,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1150.9793000005716 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"",
            "value": 1519.1137060052995,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1524.8798000028073 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"",
            "value": 1883.4364990019594,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 1891.5118000006785 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"",
            "value": 2321.6618360090706,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2330.932299999766 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"",
            "value": 2741.2887780104143,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 2752.1250999967747 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"",
            "value": 3149.7587579746096,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3162.7792999949734 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"",
            "value": 3501.39495000559,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3515.799399996702 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"",
            "value": 3828.8984000128607,
            "unit": "ms/iter",
            "extra": "iterations: 1\ncpu: 3843.9992999902015 ms\nthreads: 1"
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
          "id": "fb5964f6e112b8545561be88d62157d084067a4c",
          "message": "Added .clang-tidy config + whole lot of refactoring",
          "timestamp": "2022-10-23T23:42:47+03:00",
          "tree_id": "b73a48d56e80993e9f4cd3275faabe6067f728c4",
          "url": "https://github.com/m4drat/memplusplus/commit/fb5964f6e112b8545561be88d62157d084067a4c"
        },
        "date": 1666614936771,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 4.664360339339559,
            "unit": "us/iter",
            "extra": "iterations: 149917\ncpu: 4.672319350039831 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 8.288526293370937,
            "unit": "us/iter",
            "extra": "iterations: 84014\ncpu: 8.292127502560627 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 22.0886477896095,
            "unit": "us/iter",
            "extra": "iterations: 31714\ncpu: 22.08654222110009 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 55.0567972345055,
            "unit": "us/iter",
            "extra": "iterations: 12729\ncpu: 55.034299630764934 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 127.79499708096019,
            "unit": "us/iter",
            "extra": "iterations: 5481\ncpu: 127.73389892355928 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 335.958225790854,
            "unit": "us/iter",
            "extra": "iterations: 2086\ncpu: 335.88959731541496 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1370.0733111565005,
            "unit": "us/iter",
            "extra": "iterations: 511\ncpu: 1369.8954990215534 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 546601.3679999833,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 545897.7999999988 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 7.30372852668585,
            "unit": "us/iter",
            "extra": "iterations: 95560\ncpu: 7.3052731268289826 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 14.400543869477607,
            "unit": "us/iter",
            "extra": "iterations: 48633\ncpu: 14.399494170626323 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 30.54690850719626,
            "unit": "us/iter",
            "extra": "iterations: 22887\ncpu: 30.547441779172637 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 62.49424580804926,
            "unit": "us/iter",
            "extra": "iterations: 11212\ncpu: 62.49230288976127 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 141.23438906849768,
            "unit": "us/iter",
            "extra": "iterations: 4958\ncpu: 141.2476401775093 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 290.50938314730524,
            "unit": "us/iter",
            "extra": "iterations: 2409\ncpu: 290.5090909090447 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 630.6349675397222,
            "unit": "us/iter",
            "extra": "iterations: 1109\ncpu: 630.6260595130805 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1683.0239302890138,
            "unit": "us/iter",
            "extra": "iterations: 416\ncpu: 1683.172596153778 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 3.5048682139849654,
            "unit": "us/iter",
            "extra": "iterations: 199528\ncpu: 3.5045432220039223 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 7.003163148214569,
            "unit": "us/iter",
            "extra": "iterations: 100044\ncpu: 7.002531885970141 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 13.9870706838693,
            "unit": "us/iter",
            "extra": "iterations: 50068\ncpu: 13.986694096029321 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 27.94902732720625,
            "unit": "us/iter",
            "extra": "iterations: 25030\ncpu: 27.948345984818367 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 55.925701782431894,
            "unit": "us/iter",
            "extra": "iterations: 12511\ncpu: 55.92205259371732 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 111.89751717526178,
            "unit": "us/iter",
            "extra": "iterations: 6259\ncpu: 111.89098897587482 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 223.99237915600804,
            "unit": "us/iter",
            "extra": "iterations: 3128\ncpu: 223.97519181585676 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 447.7665745361499,
            "unit": "us/iter",
            "extra": "iterations: 1563\ncpu: 447.74203454894285 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 339.4256455945765,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 341.084319999311 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 699.7701271924257,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 703.0052600014657 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1057.282131394686,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1062.000340000776 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1414.3335536098107,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1420.5905999990505 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1776.4422678214717,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1784.1554200005562 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2135.7913271834605,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2145.0328999987223 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2488.350661806885,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2499.253120003138 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2850.103149001154,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2862.9760400055543 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3205.670347404009,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3219.9608399852596 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3562.0750118005044,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3578.0215399828876 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64",
            "value": 26.0657443982055,
            "unit": "us/iter",
            "extra": "iterations: 26866\ncpu: 26.07262711243759 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128",
            "value": 91.95132135900579,
            "unit": "us/iter",
            "extra": "iterations: 7711\ncpu: 91.95624432608176 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256",
            "value": 342.6900611844988,
            "unit": "us/iter",
            "extra": "iterations: 2043\ncpu: 342.67161037718137 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512",
            "value": 1837.9401842088625,
            "unit": "us/iter",
            "extra": "iterations: 380\ncpu: 1837.8694736841944 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024",
            "value": 8409.80682352946,
            "unit": "us/iter",
            "extra": "iterations: 85\ncpu: 8408.96352941025 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048",
            "value": 36766.6292000024,
            "unit": "us/iter",
            "extra": "iterations: 20\ncpu: 36765.529999999555 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64",
            "value": 47.64888016655393,
            "unit": "us/iter",
            "extra": "iterations: 14687\ncpu: 47.63866684828885 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128",
            "value": 140.70240157810895,
            "unit": "us/iter",
            "extra": "iterations: 4943\ncpu: 140.69140198281835 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256",
            "value": 456.8039817346999,
            "unit": "us/iter",
            "extra": "iterations: 1533\ncpu: 456.7699282460071 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512",
            "value": 1597.0130688060894,
            "unit": "us/iter",
            "extra": "iterations: 436\ncpu: 1596.847247705777 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024",
            "value": 8507.28452438813,
            "unit": "us/iter",
            "extra": "iterations: 82\ncpu: 8506.676829267759 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048",
            "value": 43956.39831248843,
            "unit": "us/iter",
            "extra": "iterations: 16\ncpu: 43952.093749998865 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64",
            "value": 27.71285503270621,
            "unit": "us/iter",
            "extra": "iterations: 25254\ncpu: 27.723481428654807 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128",
            "value": 106.12695084238023,
            "unit": "us/iter",
            "extra": "iterations: 6591\ncpu: 106.13096646956944 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256",
            "value": 463.3159907219352,
            "unit": "us/iter",
            "extra": "iterations: 1509\ncpu: 463.2940357851978 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512",
            "value": 2433.210473866684,
            "unit": "us/iter",
            "extra": "iterations: 287\ncpu: 2433.0522648085466 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024",
            "value": 9742.089930555487,
            "unit": "us/iter",
            "extra": "iterations: 72\ncpu: 9741.544444445872 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048",
            "value": 38077.584315793065,
            "unit": "us/iter",
            "extra": "iterations: 19\ncpu: 38075.71578947563 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64",
            "value": 47.63406392823769,
            "unit": "us/iter",
            "extra": "iterations: 14704\ncpu: 47.62693824799016 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128",
            "value": 140.68997673898477,
            "unit": "us/iter",
            "extra": "iterations: 4987\ncpu: 140.67232805292983 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256",
            "value": 451.2195428745304,
            "unit": "us/iter",
            "extra": "iterations: 1551\ncpu: 451.1691166987395 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512",
            "value": 1622.9138468669094,
            "unit": "us/iter",
            "extra": "iterations: 431\ncpu: 1622.7238979112678 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024",
            "value": 8432.753289153983,
            "unit": "us/iter",
            "extra": "iterations: 83\ncpu: 8431.997590358984 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048",
            "value": 43559.18693750027,
            "unit": "us/iter",
            "extra": "iterations: 16\ncpu: 43558.65624999566 us\nthreads: 1"
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
          "id": "fe43b82cecd154319c69f98f2208382e7dceb7d0",
          "message": "Replaced std::set with std::unordered_set (m_activeGcPtrs). Closes #72\n\nThis change should considerably improve allocation speed for chunks request by SharedGcPtr\n\nCo-authored-by: lithium1337mwfgtkam <lithium1337mwfgtkam@users.noreply.github.com>",
          "timestamp": "2022-10-24T16:16:12+03:00",
          "tree_id": "f3b3bb9c3512f845d12e7afefebab38ddaec6c29",
          "url": "https://github.com/m4drat/memplusplus/commit/fe43b82cecd154319c69f98f2208382e7dceb7d0"
        },
        "date": 1666617707705,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 4.451036063725457,
            "unit": "us/iter",
            "extra": "iterations: 157416\ncpu: 4.440878309701012 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 7.7190685686300045,
            "unit": "us/iter",
            "extra": "iterations: 90158\ncpu: 7.703029126644602 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 21.980878902200647,
            "unit": "us/iter",
            "extra": "iterations: 31809\ncpu: 21.964123361312673 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 55.167451191452145,
            "unit": "us/iter",
            "extra": "iterations: 12713\ncpu: 55.13773302918673 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 129.0600403684265,
            "unit": "us/iter",
            "extra": "iterations: 5425\ncpu: 129.01837788022632 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 341.3367305105653,
            "unit": "us/iter",
            "extra": "iterations: 2078\ncpu: 341.3035129932784 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1441.8356125007747,
            "unit": "us/iter",
            "extra": "iterations: 480\ncpu: 1441.5895833333432 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 551260.678999995,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 550648.8000000012 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 7.350257069131952,
            "unit": "us/iter",
            "extra": "iterations: 94955\ncpu: 7.3638944763232725 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 14.324017426443875,
            "unit": "us/iter",
            "extra": "iterations: 48719\ncpu: 14.341148217336103 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 30.023633708384768,
            "unit": "us/iter",
            "extra": "iterations: 23282\ncpu: 30.03082638948513 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 61.34676582887684,
            "unit": "us/iter",
            "extra": "iterations: 11419\ncpu: 61.360697083788814 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 139.67079437009295,
            "unit": "us/iter",
            "extra": "iterations: 5009\ncpu: 139.70547015372443 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 292.4987956536366,
            "unit": "us/iter",
            "extra": "iterations: 2393\ncpu: 292.5199749268252 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 660.98622096342,
            "unit": "us/iter",
            "extra": "iterations: 1059\ncpu: 661.0200188857555 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1756.8861573601182,
            "unit": "us/iter",
            "extra": "iterations: 394\ncpu: 1756.987563451827 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 3.183889971302442,
            "unit": "us/iter",
            "extra": "iterations: 219879\ncpu: 3.183841567407542 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 6.3646541901322085,
            "unit": "us/iter",
            "extra": "iterations: 109913\ncpu: 6.364181670957968 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 12.721988812610872,
            "unit": "us/iter",
            "extra": "iterations: 55062\ncpu: 12.720696669209213 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 25.415778960896244,
            "unit": "us/iter",
            "extra": "iterations: 27235\ncpu: 25.414521755094437 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 50.83485031638663,
            "unit": "us/iter",
            "extra": "iterations: 13749\ncpu: 50.831551385555464 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 102.18138183139533,
            "unit": "us/iter",
            "extra": "iterations: 6880\ncpu: 102.1802906976745 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 203.29897415044525,
            "unit": "us/iter",
            "extra": "iterations: 3443\ncpu: 203.28550682544432 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 407.14348548200235,
            "unit": "us/iter",
            "extra": "iterations: 1722\ncpu: 407.136353077817 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 345.55730160019493,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 349.3158999996325 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 712.3088255944026,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 719.584680001357 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1077.463366805307,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1088.394700001983 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1441.7283566022775,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1456.3990800021004 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1807.1399364019385,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1825.402920000198 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2171.480134393795,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2193.2492799984234 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2534.474148583479,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2560.064160003253 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2896.3513773835984,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2925.466860009755 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3263.990229582828,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3296.7593000057773 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3629.054105004002,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3662.590740006789 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64",
            "value": 17.774451093493173,
            "unit": "us/iter",
            "extra": "iterations: 39371\ncpu: 17.761497041038584 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128",
            "value": 57.99766586633307,
            "unit": "us/iter",
            "extra": "iterations: 12082\ncpu: 57.98516801864292 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256",
            "value": 230.67836876828045,
            "unit": "us/iter",
            "extra": "iterations: 3029\ncpu: 230.65922746785273 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512",
            "value": 612.9210747165279,
            "unit": "us/iter",
            "extra": "iterations: 1151\ncpu: 612.8709817552826 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024",
            "value": 6888.661320000438,
            "unit": "us/iter",
            "extra": "iterations: 100\ncpu: 6882.126000002983 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048",
            "value": 33000.785809525456,
            "unit": "us/iter",
            "extra": "iterations: 21\ncpu: 32998.57142857561 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64",
            "value": 28.353469544643044,
            "unit": "us/iter",
            "extra": "iterations: 24692\ncpu: 28.35451158264232 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128",
            "value": 73.41425743239824,
            "unit": "us/iter",
            "extra": "iterations: 9653\ncpu: 72.84819227179966 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256",
            "value": 177.42877772176604,
            "unit": "us/iter",
            "extra": "iterations: 3941\ncpu: 177.39667597096354 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512",
            "value": 835.8797647056568,
            "unit": "us/iter",
            "extra": "iterations: 833\ncpu: 835.6309723887703 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024",
            "value": 2335.6100566697555,
            "unit": "us/iter",
            "extra": "iterations: 300\ncpu: 2335.277666666021 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048",
            "value": 10630.188090905704,
            "unit": "us/iter",
            "extra": "iterations: 66\ncpu: 10629.640909087788 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64",
            "value": 15.85727040210323,
            "unit": "us/iter",
            "extra": "iterations: 44027\ncpu: 15.850366820361467 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128",
            "value": 44.20467768205938,
            "unit": "us/iter",
            "extra": "iterations: 15857\ncpu: 44.19385129593673 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256",
            "value": 146.55425956154656,
            "unit": "us/iter",
            "extra": "iterations: 4785\ncpu: 146.53402298862147 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512",
            "value": 551.8328983323938,
            "unit": "us/iter",
            "extra": "iterations: 1259\ncpu: 551.8179507542592 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024",
            "value": 3083.993672414773,
            "unit": "us/iter",
            "extra": "iterations: 232\ncpu: 3083.9530172416903 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048",
            "value": 14169.572459998108,
            "unit": "us/iter",
            "extra": "iterations: 50\ncpu: 14169.492000002037 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64",
            "value": 28.297521138970414,
            "unit": "us/iter",
            "extra": "iterations: 24765\ncpu: 28.28766000400179 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128",
            "value": 72.69566995533543,
            "unit": "us/iter",
            "extra": "iterations: 9629\ncpu: 72.68240731108297 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256",
            "value": 189.75583613667868,
            "unit": "us/iter",
            "extra": "iterations: 3686\ncpu: 189.72438958192103 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512",
            "value": 539.8382042078022,
            "unit": "us/iter",
            "extra": "iterations: 1283\ncpu: 539.7391270462417 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024",
            "value": 2585.595195573937,
            "unit": "us/iter",
            "extra": "iterations: 271\ncpu: 2585.1092250926963 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048",
            "value": 10669.840439395315,
            "unit": "us/iter",
            "extra": "iterations: 66\ncpu: 10669.233333332655 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}