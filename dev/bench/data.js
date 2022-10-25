window.BENCHMARK_DATA = {
  "lastUpdate": 1666687735045,
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
      },
      {
        "commit": {
          "author": {
            "name": "m4drat",
            "username": "m4drat"
          },
          "committer": {
            "name": "m4drat",
            "username": "m4drat"
          },
          "id": "a845b8ac7cb95110f5f33b3018f29900b6a30f6a",
          "message": "Issue 70 updating ChunksInUse",
          "timestamp": "2022-10-11T17:29:58Z",
          "url": "https://github.com/m4drat/memplusplus/pull/74/commits/a845b8ac7cb95110f5f33b3018f29900b6a30f6a"
        },
        "date": 1666687694672,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 4.607842965505788,
            "unit": "us/iter",
            "extra": "iterations: 145503\ncpu: 4.611103551129311 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 7.675173511631937,
            "unit": "us/iter",
            "extra": "iterations: 86974\ncpu: 7.6762676202075 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 23.315627575467033,
            "unit": "us/iter",
            "extra": "iterations: 29410\ncpu: 23.315317919071422 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 57.497982693659125,
            "unit": "us/iter",
            "extra": "iterations: 12481\ncpu: 57.47583526962527 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 141.62278313022625,
            "unit": "us/iter",
            "extra": "iterations: 5335\ncpu: 141.55664479850083 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 355.09342900291654,
            "unit": "us/iter",
            "extra": "iterations: 1986\ncpu: 355.0799093655441 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1425.0446413940992,
            "unit": "us/iter",
            "extra": "iterations: 488\ncpu: 1425.0219262294754 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 577354.4850000576,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 576418.300000002 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 7.7470787236952985,
            "unit": "us/iter",
            "extra": "iterations: 96286\ncpu: 7.748715285717586 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 15.114081404862512,
            "unit": "us/iter",
            "extra": "iterations: 46066\ncpu: 15.11511526939854 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 31.28480829900168,
            "unit": "us/iter",
            "extra": "iterations: 22509\ncpu: 31.282300413169743 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 65.2776856341631,
            "unit": "us/iter",
            "extra": "iterations: 10351\ncpu: 65.27169355619105 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 146.34492519211125,
            "unit": "us/iter",
            "extra": "iterations: 4692\ncpu: 146.3599531116721 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 314.38564830020124,
            "unit": "us/iter",
            "extra": "iterations: 2323\ncpu: 314.41541110634347 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 701.0846027989326,
            "unit": "us/iter",
            "extra": "iterations: 929\ncpu: 701.0597416577835 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1898.5325027017552,
            "unit": "us/iter",
            "extra": "iterations: 370\ncpu: 1898.739729729845 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 3.4452866165966687,
            "unit": "us/iter",
            "extra": "iterations: 211837\ncpu: 3.4450332094960063 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 6.57882536602098,
            "unit": "us/iter",
            "extra": "iterations: 105117\ncpu: 6.577911279812015 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 13.2348637161508,
            "unit": "us/iter",
            "extra": "iterations: 50703\ncpu: 13.233155829043685 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 26.329564576064747,
            "unit": "us/iter",
            "extra": "iterations: 26372\ncpu: 26.326501592598206 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 54.76086904404869,
            "unit": "us/iter",
            "extra": "iterations: 13348\ncpu: 54.75448007192066 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 109.32755629039184,
            "unit": "us/iter",
            "extra": "iterations: 6653\ncpu: 109.3167593566815 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 217.47972596717577,
            "unit": "us/iter",
            "extra": "iterations: 3412\ncpu: 217.44196951934325 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 423.50627879502895,
            "unit": "us/iter",
            "extra": "iterations: 1693\ncpu: 423.45965741287927 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 337.55392379611067,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 339.4963399994836 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 696.9521258031591,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 700.4670400015868 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1035.8678010024164,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1041.2687999983973 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1391.0598374148776,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1397.7838599990905 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1789.1640322026547,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1798.0165199963042 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2221.4938084141863,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2232.4224399999284 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2657.0156959911174,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2670.2074799960055 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2859.4024380070323,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2873.7587800055676 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3204.354888821524,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3220.325619990723 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 3473.755913224727,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 3490.7958600007537 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64",
            "value": 18.457992622263536,
            "unit": "us/iter",
            "extra": "iterations: 39173\ncpu: 18.439517014313186 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128",
            "value": 38.50954306768812,
            "unit": "us/iter",
            "extra": "iterations: 17902\ncpu: 38.5008881690187 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256",
            "value": 160.0154122850704,
            "unit": "us/iter",
            "extra": "iterations: 4640\ncpu: 159.99614224130895 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512",
            "value": 648.8304798854183,
            "unit": "us/iter",
            "extra": "iterations: 1044\ncpu: 648.7784482758755 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024",
            "value": 6888.561597935976,
            "unit": "us/iter",
            "extra": "iterations: 97\ncpu: 6888.195876288208 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048",
            "value": 37236.91199999419,
            "unit": "us/iter",
            "extra": "iterations: 18\ncpu: 37225.088888893275 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64",
            "value": 33.13861661387487,
            "unit": "us/iter",
            "extra": "iterations: 21584\ncpu: 33.12372127498356 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128",
            "value": 77.76196631638767,
            "unit": "us/iter",
            "extra": "iterations: 8936\ncpu: 77.7346687555731 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256",
            "value": 210.47921278555484,
            "unit": "us/iter",
            "extra": "iterations: 3191\ncpu: 210.4251018491754 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512",
            "value": 913.651436411274,
            "unit": "us/iter",
            "extra": "iterations: 747\ncpu: 913.3970548860232 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024",
            "value": 2196.9676196708037,
            "unit": "us/iter",
            "extra": "iterations: 305\ncpu: 2195.5937704910493 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048",
            "value": 12667.524464290076,
            "unit": "us/iter",
            "extra": "iterations: 56\ncpu: 12666.271428570955 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64",
            "value": 15.568350667525236,
            "unit": "us/iter",
            "extra": "iterations: 46229\ncpu: 15.558268619256227 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128",
            "value": 44.179105000950656,
            "unit": "us/iter",
            "extra": "iterations: 15657\ncpu: 44.16078431378993 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256",
            "value": 142.0901572536069,
            "unit": "us/iter",
            "extra": "iterations: 4922\ncpu: 142.06856968717798 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512",
            "value": 589.3615884734312,
            "unit": "us/iter",
            "extra": "iterations: 1232\ncpu: 589.1099025974581 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024",
            "value": 3292.6458728069433,
            "unit": "us/iter",
            "extra": "iterations: 228\ncpu: 3292.2907894732284 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048",
            "value": 14760.410586958367,
            "unit": "us/iter",
            "extra": "iterations: 46\ncpu: 14758.302173911663 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64",
            "value": 29.05272222241412,
            "unit": "us/iter",
            "extra": "iterations: 24372\ncpu: 29.036418841339422 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128",
            "value": 75.33028216428515,
            "unit": "us/iter",
            "extra": "iterations: 9537\ncpu: 75.2920100659408 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256",
            "value": 193.00402957949225,
            "unit": "us/iter",
            "extra": "iterations: 3685\ncpu: 192.9274626865254 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512",
            "value": 737.7609296472816,
            "unit": "us/iter",
            "extra": "iterations: 995\ncpu: 737.582512562799 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024",
            "value": 2807.5623412699238,
            "unit": "us/iter",
            "extra": "iterations: 252\ncpu: 2806.7230158719153 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048",
            "value": 12585.460196429412,
            "unit": "us/iter",
            "extra": "iterations: 56\ncpu: 12584.18214285736 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "39669467+m4drat@users.noreply.github.com",
            "name": "Theodor Arsenij",
            "username": "m4drat"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "6861e00d69e9c644b7149ebb0b9b266c4a230695",
          "message": "Issue 70 updating ChunksInUse (#74)\n\n* Updating chunksInUse in Allocate/Deallocate results in performance degradation with each allocation.\r\n\r\n* Moved logic from Allocate to GC::Collect. Closes #70\r\n\r\nCo-authored-by: lithium1337mwfgtkam <lithium1337mwfgtkam@users.noreply.github.com>\r\n\r\nCo-authored-by: Grigory <pepecezar5@gmail.com>\r\nCo-authored-by: lithium1337mwfgtkam <lithium1337mwfgtkam@users.noreply.github.com>",
          "timestamp": "2022-10-25T11:43:15+03:00",
          "tree_id": "8fb114b65e26cb3d1c8ee07fa4432f1372b3d666",
          "url": "https://github.com/m4drat/memplusplus/commit/6861e00d69e9c644b7149ebb0b9b266c4a230695"
        },
        "date": 1666687734319,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.0571669323195843,
            "unit": "us/iter",
            "extra": "iterations: 341318\ncpu: 2.058066670964465 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.096235456124573,
            "unit": "us/iter",
            "extra": "iterations: 225834\ncpu: 3.1004056076575868 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 6.755226046628677,
            "unit": "us/iter",
            "extra": "iterations: 96918\ncpu: 6.7587661734656415 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 17.85994237684601,
            "unit": "us/iter",
            "extra": "iterations: 38127\ncpu: 17.895834972587323 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 58.27642069205676,
            "unit": "us/iter",
            "extra": "iterations: 11821\ncpu: 58.30616699099437 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 217.74236746012227,
            "unit": "us/iter",
            "extra": "iterations: 3448\ncpu: 217.87082366588749 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1035.5378930723095,
            "unit": "us/iter",
            "extra": "iterations: 664\ncpu: 1035.7177710843666 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 628022.551000015,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 627371.1999999989 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 5.000538555696967,
            "unit": "us/iter",
            "extra": "iterations: 141302\ncpu: 5.006293612259743 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 9.716895995016342,
            "unit": "us/iter",
            "extra": "iterations: 72958\ncpu: 9.721180679300899 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 18.61167479120178,
            "unit": "us/iter",
            "extra": "iterations: 34135\ncpu: 18.61087153947336 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 35.709483032346256,
            "unit": "us/iter",
            "extra": "iterations: 18771\ncpu: 35.65560705341487 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 76.88142625387447,
            "unit": "us/iter",
            "extra": "iterations: 9309\ncpu: 76.83344075624312 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 184.56747480523111,
            "unit": "us/iter",
            "extra": "iterations: 3850\ncpu: 184.4703376623724 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 477.8295951440908,
            "unit": "us/iter",
            "extra": "iterations: 1524\ncpu: 477.6921259842138 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1157.6357827472962,
            "unit": "us/iter",
            "extra": "iterations: 626\ncpu: 1156.9923322683528 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.1700584688195947,
            "unit": "us/iter",
            "extra": "iterations: 512598\ncpu: 1.1699277016297382 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.839771563677615,
            "unit": "us/iter",
            "extra": "iterations: 287393\ncpu: 2.8391102079730626 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 5.793271313440646,
            "unit": "us/iter",
            "extra": "iterations: 90084\ncpu: 5.792473691221525 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 9.262475148709118,
            "unit": "us/iter",
            "extra": "iterations: 65228\ncpu: 9.260811308027279 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 21.954083844019678,
            "unit": "us/iter",
            "extra": "iterations: 32799\ncpu: 21.953083935485903 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 39.657049728425115,
            "unit": "us/iter",
            "extra": "iterations: 16570\ncpu: 39.653313216656876 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 79.05585914012349,
            "unit": "us/iter",
            "extra": "iterations: 9513\ncpu: 79.05002627982769 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 141.8070702702728,
            "unit": "us/iter",
            "extra": "iterations: 4810\ncpu: 141.7916008316012 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 276.474623197862,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 277.7286000002434 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 575.5847119997497,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 578.5283200008691 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 881.1686315934082,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 886.410859998405 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1223.879823211837,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1230.7427599982716 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1706.4124494084979,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1721.4323400014334 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1981.024768192765,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1992.4100599971098 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2127.4071956053604,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2140.039079999605 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2278.282688610358,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2290.2404200023343 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2631.9755675817364,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2645.9050799942875 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2890.0550376432307,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2900.2139400174656 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64",
            "value": 11.499432490242473,
            "unit": "us/iter",
            "extra": "iterations: 56577\ncpu: 11.486897502538884 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128",
            "value": 27.44959576759484,
            "unit": "us/iter",
            "extra": "iterations: 25045\ncpu: 27.457244959029172 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256",
            "value": 113.89820662989705,
            "unit": "us/iter",
            "extra": "iterations: 6335\ncpu: 113.90958168890762 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512",
            "value": 536.0195707797631,
            "unit": "us/iter",
            "extra": "iterations: 1321\ncpu: 536.0161241478448 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024",
            "value": 5988.350409998021,
            "unit": "us/iter",
            "extra": "iterations: 100\ncpu: 5989.191999999548 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048",
            "value": 35056.08171428505,
            "unit": "us/iter",
            "extra": "iterations: 21\ncpu: 35054.62380952568 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64",
            "value": 21.65387298279126,
            "unit": "us/iter",
            "extra": "iterations: 32468\ncpu: 21.638628803853706 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128",
            "value": 65.8569146019575,
            "unit": "us/iter",
            "extra": "iterations: 10855\ncpu: 65.8258498388542 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256",
            "value": 152.21792786636252,
            "unit": "us/iter",
            "extra": "iterations: 4561\ncpu: 152.15928524450584 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512",
            "value": 653.4502460837971,
            "unit": "us/iter",
            "extra": "iterations: 1085\ncpu: 653.2489400927656 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024",
            "value": 3958.2710542125446,
            "unit": "us/iter",
            "extra": "iterations: 166\ncpu: 3957.841566264174 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048",
            "value": 9365.685934216266,
            "unit": "us/iter",
            "extra": "iterations: 76\ncpu: 9361.472368422446 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64",
            "value": 11.468732636168605,
            "unit": "us/iter",
            "extra": "iterations: 61564\ncpu: 11.463351958898265 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128",
            "value": 28.560650357890605,
            "unit": "us/iter",
            "extra": "iterations: 24016\ncpu: 28.552610759355403 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256",
            "value": 85.46465073370793,
            "unit": "us/iter",
            "extra": "iterations: 8243\ncpu: 85.48037122421118 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512",
            "value": 355.7625292023416,
            "unit": "us/iter",
            "extra": "iterations: 1969\ncpu: 355.8501777551504 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024",
            "value": 2448.447928083954,
            "unit": "us/iter",
            "extra": "iterations: 292\ncpu: 2448.791438355165 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048",
            "value": 12686.664303566478,
            "unit": "us/iter",
            "extra": "iterations: 56\ncpu: 12686.64821428597 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64",
            "value": 21.69364508361993,
            "unit": "us/iter",
            "extra": "iterations: 32850\ncpu: 21.686237442930953 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128",
            "value": 57.180653478497874,
            "unit": "us/iter",
            "extra": "iterations: 12865\ncpu: 57.14828604728553 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256",
            "value": 143.45775151078368,
            "unit": "us/iter",
            "extra": "iterations: 4797\ncpu: 143.3042735043503 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512",
            "value": 444.06582165987646,
            "unit": "us/iter",
            "extra": "iterations: 1542\ncpu: 443.7487678337342 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024",
            "value": 2462.95666197107,
            "unit": "us/iter",
            "extra": "iterations: 284\ncpu: 2462.604929576173 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048",
            "value": 9546.783371794512,
            "unit": "us/iter",
            "extra": "iterations: 78\ncpu: 9545.40641025549 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}