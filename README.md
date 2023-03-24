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
   
4. PA% Contains a thread safe DNS Lookup Utility that would be able to recieve a list of 
   web addresses and return their IPs. The address to IP function was given as part of a 
   document that was lost post VM retirement. Overall this implementation scored well and
   was able to quickly and efficently process thousands of address and return correct output. 
