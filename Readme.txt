# Assignment 2

## Introduction

This file contains instructions on how we proceeded to resolve the exercices of the assignment.

Werner and Gobi have resolved the theoretical part, while Deep and Jules have resolved the programming part.

## Convex Function

You can find the file called _convex-functions_ that contains, in a pdf format, how we resolved the hand-written exercices.

## Convexity Test

As instructed, we have modified the isConvex function in the ConvexityTest.hh file and the solution lies between lines 39 and 77. The algorithm procedure is explained as a comment before the loop that will get two samplings of the domain of the function 1 million times.

After compilation, We ran the following command to test my implementation:

```bash
./Build/bin/ConvexityTests 1
```

Which will test the convexity of a non convex 2-D function. It will output the following text before returning false:
_path: p(t) = (1 - t) * p1 + t * p2;_
_with:_
_p1 = (-12.5129 580.247)_
_p2 = (28.6925 865.696)_
_p (t = 0.1) = (24.5719 837.151)_

Which is the expected result if the function is not convex. We also ran the following command:

```bash
./Build/bin/ConvexityTests 2
```

Which will run the convexity of a 3-D function. The function will output the following text before returning true:
_The function is probably convex._

Which is the expected result if the function is convex.

If we run:

```bash
./Build/bin/ConvexityTests-test
```

All the 7 tests from the suite pass.
