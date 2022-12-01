# Matrix calculator
## Build
```bash
# in project directory:
make
```
## Run
```
./main
```

## Exapmple output
```
$:~/project/matrix$ ./main 
Matrix dump [8 x 8] 1:
   0   1   2   3   4   5   6   7
  27  28  29  30  31  32  33   8
  26  47  48  49  50  51  34   9
  25  46  59  60  61  52  35  10
  24  45  58  63  62  53  36  11
  23  44  57  56  55  54  37  12
  22  43  42  41  40  39  38  13
  21  20  19  18  17  16  15  14

Matrix dump [4 x 4] 2:
   1   3   5   4
   0   1   0   6
   9   0   0   0
   8   1   1   7

Matrix dump [3 x 4] 2:
   1   3   5   4
   0   1   0   6
   8   1   1   7

Matrix dump [3 x 3] 3:
   1   1   1
   1   1   0
   1   1  -1

Matrix dump [3 x 2] 3:
   0   1
   0   0
   0  -1

Matrix dump [4 x 4] 4:
  42  57  20  38
  54  85   6   4
  77  73  54  18
  48  28  31  69

Row    0: 157
Row    1: 149
Row    2: 222
Row    3: 176

Col    0: 221
Col    1: 243
Col    2: 111
Col    3: 129
```

## Description
`matrix.hpp` - contains API (application programm interface) for matrix class (defined in `matrix.cc`)

`main.cc` - contains 4 tasks (1 matrix on every task); every task prints input matrix and output matrix. You can change the order. Also it contains minor functions for better code.

All API functions are marked by comment.

Good luck.