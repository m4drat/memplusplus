window.BENCHMARK_DATA = {
  "lastUpdate": 1680026050212,
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
            "email": "39669467+m4drat@users.noreply.github.com",
            "name": "Theodor Arsenij",
            "username": "m4drat"
          },
          "distinct": true,
          "id": "2aba4ae5737a0bcd36f29d52c59020ed3de4646f",
          "message": "Fixed MPP_DEBUG_ASSERT is still present in release builds",
          "timestamp": "2023-03-15T22:53:07+03:00",
          "tree_id": "35b01c8a3185d9b89cda872e934595db71b76d1c",
          "url": "https://github.com/m4drat/memplusplus/commit/2aba4ae5737a0bcd36f29d52c59020ed3de4646f"
        },
        "date": 1678910218847,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.13728843149855,
            "unit": "us/iter",
            "extra": "iterations: 327544\ncpu: 2.1327852135901115 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.294981947840782,
            "unit": "us/iter",
            "extra": "iterations: 212938\ncpu: 3.294417623908783 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 7.35657331986385,
            "unit": "us/iter",
            "extra": "iterations: 94872\ncpu: 7.369925794754598 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 20.38022422022759,
            "unit": "us/iter",
            "extra": "iterations: 34368\ncpu: 20.378648743027203 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 63.74217455832278,
            "unit": "us/iter",
            "extra": "iterations: 10982\ncpu: 63.74223274449887 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 227.3939011307765,
            "unit": "us/iter",
            "extra": "iterations: 3095\ncpu: 227.3769305331424 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1106.8053680889054,
            "unit": "us/iter",
            "extra": "iterations: 633\ncpu: 1106.778199052001 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 555910.5339999917,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 555216.8000000002 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.716802660785038,
            "unit": "us/iter",
            "extra": "iterations: 148227\ncpu: 4.7211061412409006 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.783745273919779,
            "unit": "us/iter",
            "extra": "iterations: 79823\ncpu: 8.782280796266592 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.5656054415974,
            "unit": "us/iter",
            "extra": "iterations: 39842\ncpu: 17.559904121271334 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 35.00007270357932,
            "unit": "us/iter",
            "extra": "iterations: 19999\ncpu: 34.998034901745335 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 74.48055686772562,
            "unit": "us/iter",
            "extra": "iterations: 9399\ncpu: 74.47713586551257 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 163.84733286489268,
            "unit": "us/iter",
            "extra": "iterations: 4269\ncpu: 163.82309674396254 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 394.0831074845648,
            "unit": "us/iter",
            "extra": "iterations: 1777\ncpu: 394.01997749015493 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1130.5233020998485,
            "unit": "us/iter",
            "extra": "iterations: 619\ncpu: 1130.29951534725 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.3499261619704137,
            "unit": "us/iter",
            "extra": "iterations: 518107\ncpu: 1.3497711862607493 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.691832449771403,
            "unit": "us/iter",
            "extra": "iterations: 260310\ncpu: 2.6916115400868206 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 5.371381416688368,
            "unit": "us/iter",
            "extra": "iterations: 130558\ncpu: 5.370696548660381 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 10.740964368468864,
            "unit": "us/iter",
            "extra": "iterations: 65167\ncpu: 10.740621787100835 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 21.510100721190696,
            "unit": "us/iter",
            "extra": "iterations: 32585\ncpu: 21.508666564370035 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 42.953788081502225,
            "unit": "us/iter",
            "extra": "iterations: 16294\ncpu: 42.950816251380985 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 85.90131567329112,
            "unit": "us/iter",
            "extra": "iterations: 8154\ncpu: 85.89898209467803 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 171.6050298946331,
            "unit": "us/iter",
            "extra": "iterations: 4081\ncpu: 171.6008821367313 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 300.13446879999606,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 298.2006400000003 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 530.3282195999998,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 530.2809800000006 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 799.3485514000042,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 799.2528800000002 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1056.7603771999984,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1056.6310599999993 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1313.7639137999997,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1313.6301199999991 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1578.3785932000058,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1577.608999999998 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1856.631318999996,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1856.4283000000019 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2131.9235651999975,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2131.6810000000005 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2403.284015999998,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2403.0384 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2659.197967399996,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2658.8762599999995 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.10810077523606589,
            "unit": "us/iter",
            "extra": "iterations: 6470319\ncpu: 0.14292816165632585 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.20697720560260852,
            "unit": "us/iter",
            "extra": "iterations: 3382234\ncpu: 0.2419572093474314 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.3873965836017972,
            "unit": "us/iter",
            "extra": "iterations: 1807397\ncpu: 0.4224780720561189 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 2.16455146154669,
            "unit": "us/iter",
            "extra": "iterations: 323834\ncpu: 2.2006589796006715 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 4.308614391357917,
            "unit": "us/iter",
            "extra": "iterations: 162945\ncpu: 4.344656786032108 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 8.554427609187409,
            "unit": "us/iter",
            "extra": "iterations: 81654\ncpu: 8.602887794841703 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.10808979506792654,
            "unit": "us/iter",
            "extra": "iterations: 6477003\ncpu: 0.14290505963946556 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.20705294996663393,
            "unit": "us/iter",
            "extra": "iterations: 3381060\ncpu: 0.2420534684388922 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.3814266073192516,
            "unit": "us/iter",
            "extra": "iterations: 1835796\ncpu: 0.41646016224025584 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 3.0568769614469513,
            "unit": "us/iter",
            "extra": "iterations: 228912\ncpu: 3.0929719717620756 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 6.091076955877657,
            "unit": "us/iter",
            "extra": "iterations: 114923\ncpu: 6.126796202674814 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 12.137020405680257,
            "unit": "us/iter",
            "extra": "iterations: 57631\ncpu: 12.172950321875508 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.10817668594826275,
            "unit": "us/iter",
            "extra": "iterations: 6451503\ncpu: 0.1428880680982412 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.20704734829696544,
            "unit": "us/iter",
            "extra": "iterations: 3382255\ncpu: 0.24205566995984099 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.38720337721250037,
            "unit": "us/iter",
            "extra": "iterations: 1808418\ncpu: 0.4222418710718459 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 2.1626423925894334,
            "unit": "us/iter",
            "extra": "iterations: 323816\ncpu: 2.1986578797835734 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 4.2953306907634365,
            "unit": "us/iter",
            "extra": "iterations: 163225\ncpu: 4.331037524889039 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 8.547328655463344,
            "unit": "us/iter",
            "extra": "iterations: 81946\ncpu: 8.595625167793624 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.10825212747582984,
            "unit": "us/iter",
            "extra": "iterations: 6458205\ncpu: 0.1431045003991057 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.20722418751502666,
            "unit": "us/iter",
            "extra": "iterations: 3376999\ncpu: 0.24230439511531454 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.3873980349720339,
            "unit": "us/iter",
            "extra": "iterations: 1806075\ncpu: 0.42244364159848613 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 2.15855431073564,
            "unit": "us/iter",
            "extra": "iterations: 323564\ncpu: 2.1946329010643626 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 4.292290504779639,
            "unit": "us/iter",
            "extra": "iterations: 163061\ncpu: 4.328412066649974 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 8.558193970373223,
            "unit": "us/iter",
            "extra": "iterations: 81796\ncpu: 8.60722284708307 us\nthreads: 1"
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
          "id": "018df12cdb6679297b09a7a43c8909fe38ca214f",
          "message": "Extended fuzzer to support garbage-collection. Closes #53",
          "timestamp": "2023-03-22T21:23:58+03:00",
          "tree_id": "eb1306d7f2a58a0ea0b07f1a3648d60dd2f06280",
          "url": "https://github.com/m4drat/memplusplus/commit/018df12cdb6679297b09a7a43c8909fe38ca214f"
        },
        "date": 1679509656109,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.189706225476628,
            "unit": "us/iter",
            "extra": "iterations: 319878\ncpu: 2.185546677171406 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.0301157295489833,
            "unit": "us/iter",
            "extra": "iterations: 231583\ncpu: 3.0250018351948462 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 6.205915778423257,
            "unit": "us/iter",
            "extra": "iterations: 112857\ncpu: 6.212852547918679 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 18.09436788267102,
            "unit": "us/iter",
            "extra": "iterations: 38621\ncpu: 18.101571683792166 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 57.14781315038946,
            "unit": "us/iter",
            "extra": "iterations: 12395\ncpu: 57.15620814843956 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 200.26694021238927,
            "unit": "us/iter",
            "extra": "iterations: 3479\ncpu: 200.26717447543467 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 840.5854220626724,
            "unit": "us/iter",
            "extra": "iterations: 834\ncpu: 840.5521582733667 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 4637.4854238412945,
            "unit": "us/iter",
            "extra": "iterations: 151\ncpu: 4637.201324503473 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.800895070696299,
            "unit": "us/iter",
            "extra": "iterations: 145984\ncpu: 4.797439445416318 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.731117530555185,
            "unit": "us/iter",
            "extra": "iterations: 80209\ncpu: 8.72770387363491 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.4544536584647,
            "unit": "us/iter",
            "extra": "iterations: 40072\ncpu: 17.450968257130633 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 35.35521399402298,
            "unit": "us/iter",
            "extra": "iterations: 19837\ncpu: 35.34022785704006 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 74.1031344074283,
            "unit": "us/iter",
            "extra": "iterations: 9434\ncpu: 74.08668645326047 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 161.07089811430518,
            "unit": "us/iter",
            "extra": "iterations: 4348\ncpu: 161.05034498620293 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 368.78180042118106,
            "unit": "us/iter",
            "extra": "iterations: 1899\ncpu: 368.74486571882295 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 921.9153390506008,
            "unit": "us/iter",
            "extra": "iterations: 758\ncpu: 921.7048812665927 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.1416026212671628,
            "unit": "us/iter",
            "extra": "iterations: 618098\ncpu: 1.1395487446974466 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.2579173279422156,
            "unit": "us/iter",
            "extra": "iterations: 310637\ncpu: 2.257730727505107 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 4.48171822856809,
            "unit": "us/iter",
            "extra": "iterations: 155761\ncpu: 4.480538132138351 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 8.96980623889775,
            "unit": "us/iter",
            "extra": "iterations: 78251\ncpu: 8.969228508261862 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 17.85245340423913,
            "unit": "us/iter",
            "extra": "iterations: 39113\ncpu: 17.849947587758443 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 35.628859982714594,
            "unit": "us/iter",
            "extra": "iterations: 19669\ncpu: 35.62654939244502 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 71.58178067406634,
            "unit": "us/iter",
            "extra": "iterations: 9821\ncpu: 71.57692699317838 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 142.5622242152455,
            "unit": "us/iter",
            "extra": "iterations: 4906\ncpu: 142.5488177741531 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 271.5401597999971,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 268.31115999999895 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 481.5539457999989,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 480.8425800000009 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 721.3873325999998,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 721.0360600000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 968.5049620000029,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 968.3539800000005 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1220.134310200001,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1219.7054200000011 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1464.3546596000022,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1464.0857799999992 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1710.0994168000002,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1709.8368200000011 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1954.2476484000022,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1954.0076000000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2214.335417799998,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2210.1321000000016 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2455.1325617999964,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2454.868480000002 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.15654459206099575,
            "unit": "us/iter",
            "extra": "iterations: 4470504\ncpu: 0.19431811267812532 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.2924987789180102,
            "unit": "us/iter",
            "extra": "iterations: 2392156\ncpu: 0.3303159158516414 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.5780249174410745,
            "unit": "us/iter",
            "extra": "iterations: 1210879\ncpu: 0.6160529664813785 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 1.547324674518482,
            "unit": "us/iter",
            "extra": "iterations: 452102\ncpu: 1.585746358122721 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 5.14046760912812,
            "unit": "us/iter",
            "extra": "iterations: 136026\ncpu: 5.179003278784941 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 10.235135760184031,
            "unit": "us/iter",
            "extra": "iterations: 68319\ncpu: 10.28359314392761 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.156934692673763,
            "unit": "us/iter",
            "extra": "iterations: 4452150\ncpu: 0.1947130712127827 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.29248300589483206,
            "unit": "us/iter",
            "extra": "iterations: 2393331\ncpu: 0.33032977887304277 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.5774400583734127,
            "unit": "us/iter",
            "extra": "iterations: 1210928\ncpu: 0.6154562451277035 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 1.6067497494246503,
            "unit": "us/iter",
            "extra": "iterations: 437981\ncpu: 1.645133008052845 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 7.2346159063613875,
            "unit": "us/iter",
            "extra": "iterations: 96716\ncpu: 7.272412010422134 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 14.54584771541676,
            "unit": "us/iter",
            "extra": "iterations: 48127\ncpu: 14.597824505994629 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.15659152535818152,
            "unit": "us/iter",
            "extra": "iterations: 4462255\ncpu: 0.1943702007169027 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.2924716010905877,
            "unit": "us/iter",
            "extra": "iterations: 2393332\ncpu: 0.3302947104705916 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.5780301130010287,
            "unit": "us/iter",
            "extra": "iterations: 1211105\ncpu: 0.6162606049847058 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 1.548008743216125,
            "unit": "us/iter",
            "extra": "iterations: 452465\ncpu: 1.586444034345177 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 5.140276164365777,
            "unit": "us/iter",
            "extra": "iterations: 136082\ncpu: 5.179136843961674 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 10.232215343419778,
            "unit": "us/iter",
            "extra": "iterations: 68342\ncpu: 10.282643176963013 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.15665744703261417,
            "unit": "us/iter",
            "extra": "iterations: 4470497\ncpu: 0.19443263243438222 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.2925295271618603,
            "unit": "us/iter",
            "extra": "iterations: 2391069\ncpu: 0.33034835046584327 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.5779600043973726,
            "unit": "us/iter",
            "extra": "iterations: 1211208\ncpu: 0.6162062172640889 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 1.5439423025988839,
            "unit": "us/iter",
            "extra": "iterations: 453296\ncpu: 1.5823058222441966 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 5.129685744002977,
            "unit": "us/iter",
            "extra": "iterations: 136497\ncpu: 5.168249851644927 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 10.225125316141032,
            "unit": "us/iter",
            "extra": "iterations: 68403\ncpu: 10.269511571129835 us\nthreads: 1"
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
          "id": "e47463015a5712bcb29f6f8ed20e5858a0056c9d",
          "message": "Changed SharedGcPtr semantics. Now if it points to nullptr, the references count variable will not be initialized.",
          "timestamp": "2023-03-25T19:35:38+03:00",
          "tree_id": "f55b76ce0f26843fec055c8edbf1a363c080e704",
          "url": "https://github.com/m4drat/memplusplus/commit/e47463015a5712bcb29f6f8ed20e5858a0056c9d"
        },
        "date": 1679762359013,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.188746614011293,
            "unit": "us/iter",
            "extra": "iterations: 319335\ncpu: 2.1918931529582175 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.044226084542136,
            "unit": "us/iter",
            "extra": "iterations: 229799\ncpu: 3.046943198185301 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 6.318125288275156,
            "unit": "us/iter",
            "extra": "iterations: 110569\ncpu: 6.3340249075208375 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 18.330692267257074,
            "unit": "us/iter",
            "extra": "iterations: 38202\ncpu: 18.35124077273921 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 58.61165447607968,
            "unit": "us/iter",
            "extra": "iterations: 12031\ncpu: 58.6177624469967 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 203.18976209804998,
            "unit": "us/iter",
            "extra": "iterations: 3451\ncpu: 203.18638075920387 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 825.7894834931252,
            "unit": "us/iter",
            "extra": "iterations: 848\ncpu: 825.7780660376494 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 4603.699311257517,
            "unit": "us/iter",
            "extra": "iterations: 151\ncpu: 4603.470198675566 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.690417844237171,
            "unit": "us/iter",
            "extra": "iterations: 149101\ncpu: 4.694193868590262 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.552343425505006,
            "unit": "us/iter",
            "extra": "iterations: 81846\ncpu: 8.555181682670773 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.335090442953835,
            "unit": "us/iter",
            "extra": "iterations: 40379\ncpu: 17.333440649839385 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 34.88769666603709,
            "unit": "us/iter",
            "extra": "iterations: 20067\ncpu: 34.88356007375513 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 74.00016078213316,
            "unit": "us/iter",
            "extra": "iterations: 9460\ncpu: 73.99003171245636 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 161.5219140362718,
            "unit": "us/iter",
            "extra": "iterations: 4339\ncpu: 161.50414842129285 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 366.43814450152155,
            "unit": "us/iter",
            "extra": "iterations: 1910\ncpu: 366.4058115183123 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 910.4776823533238,
            "unit": "us/iter",
            "extra": "iterations: 765\ncpu: 910.2287581700947 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.1419569710225572,
            "unit": "us/iter",
            "extra": "iterations: 615376\ncpu: 1.1419054366761134 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.262743047424053,
            "unit": "us/iter",
            "extra": "iterations: 311719\ncpu: 2.2626471277015465 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 4.51825570121034,
            "unit": "us/iter",
            "extra": "iterations: 154704\ncpu: 4.511774744027301 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 9.004641191510814,
            "unit": "us/iter",
            "extra": "iterations: 78220\ncpu: 9.004138327793363 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 17.937247033832882,
            "unit": "us/iter",
            "extra": "iterations: 38602\ncpu: 17.93515880006212 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 35.90157243852529,
            "unit": "us/iter",
            "extra": "iterations: 19520\ncpu: 35.899805327868584 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 72.2123718914479,
            "unit": "us/iter",
            "extra": "iterations: 9691\ncpu: 72.18980497368648 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 144.19232397233174,
            "unit": "us/iter",
            "extra": "iterations: 4914\ncpu: 144.18205128205062 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 266.5153432000011,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 265.30984000000046 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 479.4958061999978,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 479.4700199999994 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 725.303735,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 725.2580800000004 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 973.6014179999984,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 973.5472399999992 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1221.7289530000016,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1221.4779799999988 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1462.869536200003,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1462.7939600000004 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1715.5261645999985,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1715.4161399999994 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1958.7340965999942,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1958.6377199999988 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2204.497489000005,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2204.382200000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2454.425125800003,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2454.2986999999985 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.1565750994436533,
            "unit": "us/iter",
            "extra": "iterations: 4469740\ncpu: 0.19437669752603046 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.2925478095760068,
            "unit": "us/iter",
            "extra": "iterations: 2393244\ncpu: 0.33038357142021524 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.5760583516093066,
            "unit": "us/iter",
            "extra": "iterations: 1212306\ncpu: 0.6136080329553687 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 1.5420710958899317,
            "unit": "us/iter",
            "extra": "iterations: 453247\ncpu: 1.580529159597319 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 5.128414231334484,
            "unit": "us/iter",
            "extra": "iterations: 136361\ncpu: 5.166807958287114 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 10.227853124360774,
            "unit": "us/iter",
            "extra": "iterations: 68398\ncpu: 10.265882043334646 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.15720847762086165,
            "unit": "us/iter",
            "extra": "iterations: 4455140\ncpu: 0.19502837172344667 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.29245956271717105,
            "unit": "us/iter",
            "extra": "iterations: 2395290\ncpu: 0.3302804253347213 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.5761083479556235,
            "unit": "us/iter",
            "extra": "iterations: 1213747\ncpu: 0.6136600955553276 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 1.6355773073367088,
            "unit": "us/iter",
            "extra": "iterations: 428200\ncpu: 1.6741053246146536 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 7.234359379680802,
            "unit": "us/iter",
            "extra": "iterations: 96725\ncpu: 7.272981132075572 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 14.530123490096907,
            "unit": "us/iter",
            "extra": "iterations: 48182\ncpu: 14.568668797476468 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.15651452798807305,
            "unit": "us/iter",
            "extra": "iterations: 4466206\ncpu: 0.1943433867582438 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.2926068862935135,
            "unit": "us/iter",
            "extra": "iterations: 2392547\ncpu: 0.33039898484752905 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.5758470801386987,
            "unit": "us/iter",
            "extra": "iterations: 1215107\ncpu: 0.6133386607105333 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 1.542347175828863,
            "unit": "us/iter",
            "extra": "iterations: 454470\ncpu: 1.580849120954096 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 5.131544686585486,
            "unit": "us/iter",
            "extra": "iterations: 136372\ncpu: 5.170196227964731 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 10.227265899420754,
            "unit": "us/iter",
            "extra": "iterations: 68383\ncpu: 10.266023719345462 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.15666613395274,
            "unit": "us/iter",
            "extra": "iterations: 4463332\ncpu: 0.19445371753658913 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.29254491934353666,
            "unit": "us/iter",
            "extra": "iterations: 2390807\ncpu: 0.33034029932151987 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.5760778862814968,
            "unit": "us/iter",
            "extra": "iterations: 1215580\ncpu: 0.6135662811168293 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 1.540241644217136,
            "unit": "us/iter",
            "extra": "iterations: 454416\ncpu: 1.5786779074680477 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 5.126729706731331,
            "unit": "us/iter",
            "extra": "iterations: 136363\ncpu: 5.165049903566278 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 10.223206775599602,
            "unit": "us/iter",
            "extra": "iterations: 68422\ncpu: 10.261578147379531 us\nthreads: 1"
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
          "id": "183d2b420e2f5dcfcc5ada6a82cfc0c907888a05",
          "message": "FIxes a bug when GcGraph could created 2 vertices which would manage the same object. Fixes #88.\n\n- Added more GC/GcGraph tests\n- Refactoring: find -> contains\n- Clear the cache after each GC iteration",
          "timestamp": "2023-03-26T17:32:21+03:00",
          "tree_id": "01682833375466d8e72d07962d6ec45428264928",
          "url": "https://github.com/m4drat/memplusplus/commit/183d2b420e2f5dcfcc5ada6a82cfc0c907888a05"
        },
        "date": 1679841364471,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.1596866825739953,
            "unit": "us/iter",
            "extra": "iterations: 323343\ncpu: 2.163788917651167 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.338157000982717,
            "unit": "us/iter",
            "extra": "iterations: 210056\ncpu: 3.3338481166919047 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 7.310753122712709,
            "unit": "us/iter",
            "extra": "iterations: 95509\ncpu: 7.31886314378247 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 20.125162329999725,
            "unit": "us/iter",
            "extra": "iterations: 34781\ncpu: 20.12620396193687 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 62.269154781977576,
            "unit": "us/iter",
            "extra": "iterations: 11261\ncpu: 62.26337803036294 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 221.86686489035745,
            "unit": "us/iter",
            "extra": "iterations: 3190\ncpu: 221.82978056422493 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 1109.9402551175315,
            "unit": "us/iter",
            "extra": "iterations: 635\ncpu: 1109.918110236165 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 555908.9029999882,
            "unit": "us/iter",
            "extra": "iterations: 1\ncpu: 555595.5999999966 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.636210780752283,
            "unit": "us/iter",
            "extra": "iterations: 150825\ncpu: 4.6392461461957115 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.648728728182641,
            "unit": "us/iter",
            "extra": "iterations: 81011\ncpu: 8.644098949528285 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.16996151863703,
            "unit": "us/iter",
            "extra": "iterations: 40773\ncpu: 17.162862678739202 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 34.48923705444795,
            "unit": "us/iter",
            "extra": "iterations: 20316\ncpu: 34.48492321323205 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 73.04743769559938,
            "unit": "us/iter",
            "extra": "iterations: 9582\ncpu: 73.02882487997277 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 160.86879715168504,
            "unit": "us/iter",
            "extra": "iterations: 4353\ncpu: 160.84968986905386 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 384.61429489356965,
            "unit": "us/iter",
            "extra": "iterations: 1821\ncpu: 384.60939044483985 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1081.9988338465255,
            "unit": "us/iter",
            "extra": "iterations: 650\ncpu: 1079.1587692308124 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.3431764452030839,
            "unit": "us/iter",
            "extra": "iterations: 519062\ncpu: 1.3431089156979357 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.6671632142408344,
            "unit": "us/iter",
            "extra": "iterations: 262569\ncpu: 2.667100457403587 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 5.323464449315938,
            "unit": "us/iter",
            "extra": "iterations: 132290\ncpu: 5.323112102199712 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 10.602910431425057,
            "unit": "us/iter",
            "extra": "iterations: 65782\ncpu: 10.602328904563556 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 21.234477169575204,
            "unit": "us/iter",
            "extra": "iterations: 32829\ncpu: 21.233324195071546 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 42.4097412051121,
            "unit": "us/iter",
            "extra": "iterations: 16430\ncpu: 42.4073524041387 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 85.05042820668797,
            "unit": "us/iter",
            "extra": "iterations: 8225\ncpu: 85.04571428571403 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 170.4293336599731,
            "unit": "us/iter",
            "extra": "iterations: 4082\ncpu: 170.41962273395367 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 286.53369659999726,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 283.96094000000005 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 500.7564589999958,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 500.36494000000005 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 754.0523631999974,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 753.8662000000002 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1010.9712924000007,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1010.6780400000005 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1259.9390927999991,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1259.462400000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1515.5348430000004,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1515.2694999999994 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1792.3787001999983,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1792.1880000000015 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2042.9451312000026,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2042.7271999999987 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2297.590208399998,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2297.3245399999996 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2564.1625980000017,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2563.9024400000008 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.10819266103818473,
            "unit": "us/iter",
            "extra": "iterations: 6466865\ncpu: 0.1430285308259888 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.2070710858112493,
            "unit": "us/iter",
            "extra": "iterations: 3379873\ncpu: 0.24219025389415508 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.3875284818080436,
            "unit": "us/iter",
            "extra": "iterations: 1809559\ncpu: 0.42254455367302574 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 2.178608547541237,
            "unit": "us/iter",
            "extra": "iterations: 320864\ncpu: 2.2119134586615736 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 4.30307636783871,
            "unit": "us/iter",
            "extra": "iterations: 162647\ncpu: 4.3391528893862 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 8.567169682822037,
            "unit": "us/iter",
            "extra": "iterations: 81782\ncpu: 8.602654618375796 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.10836209371825191,
            "unit": "us/iter",
            "extra": "iterations: 6460203\ncpu: 0.14318387518163292 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.20714822491256657,
            "unit": "us/iter",
            "extra": "iterations: 3377037\ncpu: 0.24227137576520452 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.3821634619477183,
            "unit": "us/iter",
            "extra": "iterations: 1834635\ncpu: 0.417268939053272 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 3.0560060347331794,
            "unit": "us/iter",
            "extra": "iterations: 228676\ncpu: 3.092054260175919 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 6.089693353647602,
            "unit": "us/iter",
            "extra": "iterations: 114875\ncpu: 6.125619151251398 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 12.14490014230284,
            "unit": "us/iter",
            "extra": "iterations: 57622\ncpu: 12.179591128388363 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.10827949657996513,
            "unit": "us/iter",
            "extra": "iterations: 6460043\ncpu: 0.14315240626107228 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.20737498674212684,
            "unit": "us/iter",
            "extra": "iterations: 3374298\ncpu: 0.2425545995048478 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.3873919979019695,
            "unit": "us/iter",
            "extra": "iterations: 1809349\ncpu: 0.4223808673727516 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 2.172166846185994,
            "unit": "us/iter",
            "extra": "iterations: 322147\ncpu: 2.2085457881029757 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 4.299904184466062,
            "unit": "us/iter",
            "extra": "iterations: 162458\ncpu: 4.3359680655923745 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 8.553259340720514,
            "unit": "us/iter",
            "extra": "iterations: 81846\ncpu: 8.589323852112624 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.1080791199184049,
            "unit": "us/iter",
            "extra": "iterations: 6475031\ncpu: 0.14292044316081265 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.20713704008224984,
            "unit": "us/iter",
            "extra": "iterations: 3372393\ncpu: 0.24221945662916816 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.3869127116792908,
            "unit": "us/iter",
            "extra": "iterations: 1809337\ncpu: 0.4220144174357834 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 2.1725088184051167,
            "unit": "us/iter",
            "extra": "iterations: 322337\ncpu: 2.208864945693475 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 4.3032125367040726,
            "unit": "us/iter",
            "extra": "iterations: 162786\ncpu: 4.339118843143779 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 8.556555569132508,
            "unit": "us/iter",
            "extra": "iterations: 81880\ncpu: 8.592300928187642 us\nthreads: 1"
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
          "id": "183d2b420e2f5dcfcc5ada6a82cfc0c907888a05",
          "message": "FIxes a bug when GcGraph could created 2 vertices which would manage the same object. Fixes #88.\n\n- Added more GC/GcGraph tests\n- Refactoring: find -> contains\n- Clear the cache after each GC iteration",
          "timestamp": "2023-03-26T17:32:21+03:00",
          "tree_id": "01682833375466d8e72d07962d6ec45428264928",
          "url": "https://github.com/m4drat/memplusplus/commit/183d2b420e2f5dcfcc5ada6a82cfc0c907888a05"
        },
        "date": 1679851148967,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.2527303338550704,
            "unit": "us/iter",
            "extra": "iterations: 311385\ncpu: 2.25734894102205 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.1796657890073603,
            "unit": "us/iter",
            "extra": "iterations: 220280\ncpu: 3.182974850192044 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 6.560224621575564,
            "unit": "us/iter",
            "extra": "iterations: 106833\ncpu: 6.573446407010958 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 18.738558742476922,
            "unit": "us/iter",
            "extra": "iterations: 37341\ncpu: 18.758386224258345 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 57.7862015517116,
            "unit": "us/iter",
            "extra": "iterations: 11987\ncpu: 57.80704096102735 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 203.600526177357,
            "unit": "us/iter",
            "extra": "iterations: 3438\ncpu: 203.60218150088775 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 818.8221251469043,
            "unit": "us/iter",
            "extra": "iterations: 855\ncpu: 818.8283040935872 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 4502.6437677415015,
            "unit": "us/iter",
            "extra": "iterations: 155\ncpu: 4502.366451613086 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.735204361888797,
            "unit": "us/iter",
            "extra": "iterations: 147689\ncpu: 4.739694899414551 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.632882434158148,
            "unit": "us/iter",
            "extra": "iterations: 81078\ncpu: 8.638111448230896 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.656765895186027,
            "unit": "us/iter",
            "extra": "iterations: 39619\ncpu: 17.65295186651872 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 35.324907072921064,
            "unit": "us/iter",
            "extra": "iterations: 19822\ncpu: 35.32256079104933 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 75.53492453854105,
            "unit": "us/iter",
            "extra": "iterations: 9263\ncpu: 75.52518622478419 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 167.33851172837592,
            "unit": "us/iter",
            "extra": "iterations: 4178\ncpu: 167.3160603159614 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 406.47473387588275,
            "unit": "us/iter",
            "extra": "iterations: 1721\ncpu: 406.451191167916 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1122.899861958024,
            "unit": "us/iter",
            "extra": "iterations: 623\ncpu: 1122.8287319424173 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.231192745314282,
            "unit": "us/iter",
            "extra": "iterations: 567578\ncpu: 1.2311240041016414 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.441617325619431,
            "unit": "us/iter",
            "extra": "iterations: 285023\ncpu: 2.441456654375262 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 4.8643460489140296,
            "unit": "us/iter",
            "extra": "iterations: 144049\ncpu: 4.864317003241985 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 9.643366396760985,
            "unit": "us/iter",
            "extra": "iterations: 72618\ncpu: 9.64296593131173 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 19.347643573685723,
            "unit": "us/iter",
            "extra": "iterations: 36086\ncpu: 19.346294962035046 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 38.52669802773325,
            "unit": "us/iter",
            "extra": "iterations: 18101\ncpu: 38.5249102259546 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 76.87251253298359,
            "unit": "us/iter",
            "extra": "iterations: 9096\ncpu: 76.86691952506536 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 154.10160441988862,
            "unit": "us/iter",
            "extra": "iterations: 4525\ncpu: 154.09328176795722 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 270.50150540000004,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 267.69305999999915 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 479.6503922,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 479.32482000000084 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 721.1336141999993,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 721.0936599999997 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 971.4595174000009,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 971.4022000000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1216.5498516000014,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1216.4764599999999 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1467.1297363999997,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1466.7638599999989 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1727.2112470000025,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1727.1048600000001 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1949.7670805999974,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1949.6439199999998 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2184.5569473999944,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2184.414880000003 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2423.8138907999996,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2423.6754399999995 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.15675609563110265,
            "unit": "us/iter",
            "extra": "iterations: 4467788\ncpu: 0.19452357632009262 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.29249314414197575,
            "unit": "us/iter",
            "extra": "iterations: 2393868\ncpu: 0.3303622004220759 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.576083937735861,
            "unit": "us/iter",
            "extra": "iterations: 1214984\ncpu: 0.6135751581913758 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 1.5402649731731521,
            "unit": "us/iter",
            "extra": "iterations: 454446\ncpu: 1.5787096816783774 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 5.137113419837239,
            "unit": "us/iter",
            "extra": "iterations: 136246\ncpu: 5.175353404870658 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 10.23765633625988,
            "unit": "us/iter",
            "extra": "iterations: 68471\ncpu: 10.275719647733952 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.15696613952138141,
            "unit": "us/iter",
            "extra": "iterations: 4459831\ncpu: 0.194744688756144 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.29216832263093595,
            "unit": "us/iter",
            "extra": "iterations: 2395471\ncpu: 0.3300199835439457 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.5758063624340323,
            "unit": "us/iter",
            "extra": "iterations: 1215322\ncpu: 0.6133689672366642 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 1.5540443976450862,
            "unit": "us/iter",
            "extra": "iterations: 449213\ncpu: 1.5926593843009975 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 7.248734863693622,
            "unit": "us/iter",
            "extra": "iterations: 96622\ncpu: 7.287257560389901 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 14.54707980059833,
            "unit": "us/iter",
            "extra": "iterations: 48145\ncpu: 14.584962093675527 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.15775632300452555,
            "unit": "us/iter",
            "extra": "iterations: 4432187\ncpu: 0.19549181927567494 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.2932021480784754,
            "unit": "us/iter",
            "extra": "iterations: 2387334\ncpu: 0.33093593104274677 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.5757323335197123,
            "unit": "us/iter",
            "extra": "iterations: 1214687\ncpu: 0.6132687680036141 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 1.5399782043651222,
            "unit": "us/iter",
            "extra": "iterations: 455550\ncpu: 1.5785259576336066 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 5.138035521831213,
            "unit": "us/iter",
            "extra": "iterations: 136029\ncpu: 5.176510155922625 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 10.264429392494836,
            "unit": "us/iter",
            "extra": "iterations: 68378\ncpu: 10.285591857029967 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.15711797648655199,
            "unit": "us/iter",
            "extra": "iterations: 4456354\ncpu: 0.1949340649329004 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.2929804254426743,
            "unit": "us/iter",
            "extra": "iterations: 2388714\ncpu: 0.3307727505260144 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.5753771916909366,
            "unit": "us/iter",
            "extra": "iterations: 1218012\ncpu: 0.6129090682193606 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 1.5424203416112519,
            "unit": "us/iter",
            "extra": "iterations: 452206\ncpu: 1.5809573512956214 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 5.144727902076242,
            "unit": "us/iter",
            "extra": "iterations: 136359\ncpu: 5.179947784891367 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 10.231119247961695,
            "unit": "us/iter",
            "extra": "iterations: 68454\ncpu: 10.264038624477896 us\nthreads: 1"
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
          "id": "4fbe17c83299c93447d1946d73f35037a73a4f60",
          "message": "Fixed compilation error with MPP_COLOUR disabled",
          "timestamp": "2023-03-28T20:50:35+03:00",
          "tree_id": "3feed9bef5026e1eaa5295d56c11afad74cf7655",
          "url": "https://github.com/m4drat/memplusplus/commit/4fbe17c83299c93447d1946d73f35037a73a4f60"
        },
        "date": 1680026049833,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_AllocateManyRandom/64",
            "value": 2.2514583009137157,
            "unit": "us/iter",
            "extra": "iterations: 309851\ncpu: 2.2557125844358135 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/128",
            "value": 3.1763106362001023,
            "unit": "us/iter",
            "extra": "iterations: 220145\ncpu: 3.180546912264302 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/256",
            "value": 6.336288537901714,
            "unit": "us/iter",
            "extra": "iterations: 109431\ncpu: 6.345514525132054 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/512",
            "value": 18.6052538612524,
            "unit": "us/iter",
            "extra": "iterations: 37552\ncpu: 18.628456540258714 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/1024",
            "value": 58.935815620273566,
            "unit": "us/iter",
            "extra": "iterations: 11677\ncpu: 58.93351888326006 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/2048",
            "value": 204.80995848010596,
            "unit": "us/iter",
            "extra": "iterations: 3420\ncpu: 204.8160818713524 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/4096",
            "value": 868.158762081852,
            "unit": "us/iter",
            "extra": "iterations: 807\ncpu: 868.1059479554112 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateManyRandom/8192",
            "value": 4691.064079999971,
            "unit": "us/iter",
            "extra": "iterations: 150\ncpu: 4690.905999999752 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/64",
            "value": 4.6688566169093075,
            "unit": "us/iter",
            "extra": "iterations: 149655\ncpu: 4.674520731017925 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/128",
            "value": 8.621731379823137,
            "unit": "us/iter",
            "extra": "iterations: 81014\ncpu: 8.623934134838878 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/256",
            "value": 17.367961700704043,
            "unit": "us/iter",
            "extra": "iterations: 40288\ncpu: 17.36853653694284 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/512",
            "value": 34.69321501166894,
            "unit": "us/iter",
            "extra": "iterations: 20171\ncpu: 34.675048336724764 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/1024",
            "value": 74.93550107104822,
            "unit": "us/iter",
            "extra": "iterations: 9336\ncpu: 74.92775278490718 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/2048",
            "value": 167.41223487175404,
            "unit": "us/iter",
            "extra": "iterations: 4181\ncpu: 167.40107629751498 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/4096",
            "value": 406.21797737872106,
            "unit": "us/iter",
            "extra": "iterations: 1724\ncpu: 406.1823665893741 us\nthreads: 1"
          },
          {
            "name": "BM_DeallocateManyRandom/8192",
            "value": 1123.2489598718098,
            "unit": "us/iter",
            "extra": "iterations: 623\ncpu: 1123.0815409310107 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/64",
            "value": 1.2540342966976024,
            "unit": "us/iter",
            "extra": "iterations: 558771\ncpu: 1.2539949281548268 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/128",
            "value": 2.4900966599083127,
            "unit": "us/iter",
            "extra": "iterations: 281130\ncpu: 2.4900811012698605 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/256",
            "value": 4.963555773812564,
            "unit": "us/iter",
            "extra": "iterations: 141016\ncpu: 4.963247432915389 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/512",
            "value": 9.906681265310429,
            "unit": "us/iter",
            "extra": "iterations: 70623\ncpu: 9.906619656485889 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/1024",
            "value": 19.777980709854543,
            "unit": "us/iter",
            "extra": "iterations: 35303\ncpu: 19.77754298501541 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/2048",
            "value": 39.58602007237124,
            "unit": "us/iter",
            "extra": "iterations: 17686\ncpu: 39.58448490331311 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/4096",
            "value": 79.09760660932741,
            "unit": "us/iter",
            "extra": "iterations: 8836\ncpu: 79.09461294703515 us\nthreads: 1"
          },
          {
            "name": "BM_AllocateDeallocateManyRandom/8192",
            "value": 158.0773476298013,
            "unit": "us/iter",
            "extra": "iterations: 4430\ncpu: 158.0742663656882 us\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 286.9392887999993,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 281.71734000000015 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 483.81304179999916,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 483.6609600000003 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 732.6991786000008,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 732.6321799999988 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 990.7017119999979,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 990.4260199999995 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1234.4199487999958,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1234.3156800000002 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'200'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1478.5836600000039,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1478.1367400000008 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'400'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1726.936560799993,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1726.8364399999996 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'600'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 1980.8944730000007,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 1980.7422599999995 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"1'800'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2232.9252912000015,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2232.4641799999995 ms\nthreads: 1"
          },
          {
            "name": "BM_Complex/\"Total ops: \" \"2'000'000\" \"Transition matrix: ver-1\"/iterations:5",
            "value": 2476.3087150000047,
            "unit": "ms/iter",
            "extra": "iterations: 5\ncpu: 2473.8525799999993 ms\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/64/manual_time",
            "value": 0.15669497983702302,
            "unit": "us/iter",
            "extra": "iterations: 4460774\ncpu: 0.19450653630961828 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/128/manual_time",
            "value": 0.29279958314354115,
            "unit": "us/iter",
            "extra": "iterations: 2390797\ncpu: 0.33063585072258206 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/256/manual_time",
            "value": 0.5766113575469985,
            "unit": "us/iter",
            "extra": "iterations: 1215351\ncpu: 0.6137216326805989 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/512/manual_time",
            "value": 1.5570473030025629,
            "unit": "us/iter",
            "extra": "iterations: 450056\ncpu: 1.5956354320351178 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/1024/manual_time",
            "value": 5.140992678425651,
            "unit": "us/iter",
            "extra": "iterations: 136173\ncpu: 5.1793167514852625 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLinkedList/2048/manual_time",
            "value": 10.27307396419353,
            "unit": "us/iter",
            "extra": "iterations: 68425\ncpu: 10.294228717574022 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/64/manual_time",
            "value": 0.1570896490541584,
            "unit": "us/iter",
            "extra": "iterations: 4456734\ncpu: 0.194885649446431 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/128/manual_time",
            "value": 0.2924689950643159,
            "unit": "us/iter",
            "extra": "iterations: 2394829\ncpu: 0.3301948907416781 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/256/manual_time",
            "value": 0.5751625560715461,
            "unit": "us/iter",
            "extra": "iterations: 1217746\ncpu: 0.6127019099221016 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/512/manual_time",
            "value": 1.6033453145469416,
            "unit": "us/iter",
            "extra": "iterations: 435571\ncpu: 1.6418749182108292 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/1024/manual_time",
            "value": 7.245976208229402,
            "unit": "us/iter",
            "extra": "iterations: 96546\ncpu: 7.284387752988173 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLinkedList/2048/manual_time",
            "value": 14.544406245451171,
            "unit": "us/iter",
            "extra": "iterations: 48131\ncpu: 14.582123787164296 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/64/manual_time",
            "value": 0.15784376041701131,
            "unit": "us/iter",
            "extra": "iterations: 4435739\ncpu: 0.19559277495812982 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/128/manual_time",
            "value": 0.2931221680832777,
            "unit": "us/iter",
            "extra": "iterations: 2387833\ncpu: 0.3308737671353038 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/256/manual_time",
            "value": 0.5759929162381386,
            "unit": "us/iter",
            "extra": "iterations: 1212914\ncpu: 0.6136302326463414 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/512/manual_time",
            "value": 1.558593774111588,
            "unit": "us/iter",
            "extra": "iterations: 449735\ncpu: 1.5970291393820815 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/1024/manual_time",
            "value": 5.1424944892006055,
            "unit": "us/iter",
            "extra": "iterations: 136278\ncpu: 5.180989594798852 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryDefaultLayoutedLinkedList/2048/manual_time",
            "value": 10.232932841275217,
            "unit": "us/iter",
            "extra": "iterations: 68420\ncpu: 10.271708564746998 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/64/manual_time",
            "value": 0.15710328541512547,
            "unit": "us/iter",
            "extra": "iterations: 4456389\ncpu: 0.19489117758795702 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/128/manual_time",
            "value": 0.2931199070174028,
            "unit": "us/iter",
            "extra": "iterations: 2387750\ncpu: 0.3308920950685761 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/256/manual_time",
            "value": 0.5756301029280042,
            "unit": "us/iter",
            "extra": "iterations: 1214500\ncpu: 0.6132177027583441 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/512/manual_time",
            "value": 1.558258016957116,
            "unit": "us/iter",
            "extra": "iterations: 449017\ncpu: 1.5967566929537342 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/1024/manual_time",
            "value": 5.137950797982988,
            "unit": "us/iter",
            "extra": "iterations: 136092\ncpu: 5.17641081033408 us\nthreads: 1"
          },
          {
            "name": "BM_AccessMemoryRandomizedLayoutedLinkedList/2048/manual_time",
            "value": 10.237455263735022,
            "unit": "us/iter",
            "extra": "iterations: 68345\ncpu: 10.274931597044489 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}