window.BENCHMARK_DATA = {
  "lastUpdate": 1678910219145,
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
      }
    ]
  }
}
