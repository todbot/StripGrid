StripGrid an Arduino library for controlling RGB LED strips.

It currently only works with HL1606-based strips.


Assumes strips are wired in a serpentine fashion, minimizing wire length.
For example, a rows=4,cols=7 grid is wired like:

 row/col  0     1     2     3     4     5     6
   0  >-- 00 -- 01 -- 02 -- 03 -- 04 -- 05 -- 06 --+ 
                                                   |
   1  +-- 13 -- 12 -- 11 -- 10 -- 09 -- 08 -- 07 --+
      |
   2  +-- 14 -- 15 -- 16 -- 17 -- 18 -- 19 -- 20 --+
                                                   |
   3  <-- 27 -- 26 -- 25 -- 24 -- 23 -- 22 -- 21 --+


The Arduino is hooked up at 00.
