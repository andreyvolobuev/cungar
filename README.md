# Cungar
My original [Ungar algorithm](https://github.com/andreyvolobuev/ungar) rewritten in C for the sake of performance and just because.

TODO: Add availability to get values of ranges (not a single particular hand).

## Install
```bash
git clone https://github.com/andreyvolobuev/cungar.git
cd cungar
make install
```

## Use
run *ungar* and give it seven cards as an argument. It will return hands value. The lower - the better.
```bash
./ungar AsKhJdTh9s9sQc  # note: this is a straight
>> 1600

./ungar asksqsjsts2h4h  # note: this is royal flush
>> 1
```
