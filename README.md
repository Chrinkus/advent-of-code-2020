# Advent of Code 2020

## Goals for this year:
- Create some visualizations
- Try to find alternatives to `std::regex`ing all the things
- Try to stream data to the solutions as much as possible
- Run hard at graph traversal, not away from..
- Most importantly have fun and don't lose too much sleep trying to get solutions done before going to bed!

## Description of Puzzles

### Day 1 - Report Repair

#### Input
- random integers in the range of 1 to 2020, unsorted

#### Part 1
- find the two entries that sum to 2020
- multiply the two entries

#### Part 2
- find three entries that sum to 2020
- multiply the three entries

### Day 2 - Password Philosophy

#### Input
- passwords in the form `1-3 a: abcde`

#### Part 1
- count the valid passwords according to a policy
- the range `1-3` indicates the lowest and highest number of times `a` must appear in the password

#### Part 2
- count the valid passwords according to a different policy
- the digits `1` and `3` are the locations in the password that the letter `a` must appear once
    - either at the first location or second but not both
- not zero-indexed, first character is position 1
