jc-vend
==========

Vending machine with CLI
  Implementation of "vending machine" assignment for RMIT Advanced Programming Techniques course, Semester 2, 2014

Latest Changes
----------
- minor refactoring of old code to decouple functions from vm struct when they don't need the whole thing
- dispense change done, just need to tie all the purchase functions together
    
- accept payment function
- tidied up test suite  
  
Current TODO:
----------
- [ ] purchase
  - [x] find stock item
  - [x] input coins (also added coin validation)
  - [x] calculate change denominations
  - [ ] vend item / return change
  - [ ] handle cancellation
