# Operating-Systems-Course-Work
Coursework from CSCI 3753 Operating Systems. 

Note: Many of the environment/makefiles were lost when the VM Environment for the class was 
taken down and retired but many of the core files containing the code were recovered and 
mostly restored. 

Of Particular Note:

1. PA2 Contains a basic program that provides a menu with options to perform reads, writes, 
   and seeks on a document. Users reference the program and include a file address when using
   this program. 

2. PA3 Contains a character driver that powers all the previously mentioned commands in PA2. 
   Drivers for read, write, and seek were written then loaded in the kernel and were tested
   using PA2 for correctness of operation. 

3. PA4 Contains an array implimentation that is designed to be thread protected. This was 
   subsequently used in PA5 as part of a thread safe DNS Lookup Utility. 
