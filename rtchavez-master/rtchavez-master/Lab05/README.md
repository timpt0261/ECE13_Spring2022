# Lab 5

## Reuben Chavez(rtchavez)

## 4-29-22

Collaborators:

- When fixing my first segtaion fault, I was conversing in section with fellow class mates on the LinkedListCreateAfter(), where I then realized that I had to consider nodes staring at diffrent points of the linked list, instead og one size fits all

- Conversed with classmates on Discord to ask my second segfault in my insertion sort, then realixed I had to change the parameter for the while loops, when someone suggested that I should print the list before the segfualt


Results:
    
        
- Selection Sort: 198.738ms
-  Insertion Sort: 202.299ms
    
In hindsight I would probably think they would take the same amount of time, if I were seeing the psuedocode for the first time, but after seeing my final version I know see why my for my Insertion sort is slower because it has to iterate throught the linked list between iterations, costing more ttime to evaluate. More so in the long run with a list having more items.

Summary:
    The following lab was an to implement a word sorting algorthim through the use of a linked list. A Library first need to be creted where it implementd various functions for linked lised. Including a function that creates a linked list, a function the links a linked list, a function that removes a linked list item, a function that returns the size of the linked list, a function the that returns the head of the linked list, a function the returns the end of the linked list, and a function that swaps the data pointer of two list items. The sorting algorthims themselves are a Selection and Insertion Algorthim, where one iterates from front of list to back and the other from back to front, both scanning throught small iterations with which item should be swapped. The lab itself heavily relies on the use of pointers, memory allocations, sorting, to implement linked list and sorting algorthims.


Approach:
    The way I implemented the lab over the course of time was: 
         
- read through lab document
- create first version of linked list (Monday)
- create tests and debug functions in linked List(Monday - Thursday)
- create and debug sorting algorthim (Thursday and Friday)
- finish README.md, complete tests, and polish (Friday)

    What worked really well was that because I have had experiance in implementing LinkedList() before so I was able to get a head start, and spent more time in meticulously testing my functions, while debugging my code.  What went wrong were just my fist few implementations for my LinkedListCreate and LinkedListRemove, with testing it was to cut some test, as they were more overcomplicated to check on as per the specifcation for the function.

Results:
    I spent of the cousre of over 14 - 18 hours on the project manily becuase I overthough how LinkedListCreatAfter() and LinkedListRemove()should be tested. I liked how well I was able to implement the LinkedList() my first attempt, an if I were to this project again, I probably would simplify the test, so I could have been done in maybe 10 hours or less. I think this lab was worthwhile, but I did notice how other students had a hard time implementing the lab becuse they didn't understand memory allcations or the Linked List data structure. So I guess that my only complaint, as I think it's an nformative lab, and think a larg amount of the students don't see that way, becuase they don't understand it.
