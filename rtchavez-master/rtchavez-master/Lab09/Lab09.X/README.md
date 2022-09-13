# Lab 9

## Reuben Chavez(rtchavez@ucsc.edu)

## 6-2-22

Partner Name: Leo Lin
I Wrote the following files: 
- Agent.c
- Field.c
- MessageTest.c
- NegotiaionTest.c

My Parthner Wrote :
 - Message.c
 - Negotiation.c
 - FeildTest.c
 - AgentTest.c

Collaborators:

For this lab I attended section twice times this week, and attended Eric's Tutoring hours, to ask more so how to test Agent.c. They were very helpful in the end.



Summary:
    Lab09 has been the most difficult project in this class, not just becuase of the extensive libraries we have to implemnt and test before it, but becuase of the lack of info on how to use the explicity use the python files to test the code. The Lab focused on the implementaion of four files, along with their respective test files, Agent.c Field.c Message,c, and Negotiation.c. Negotiation.c was the easiest to implement with it's three simple function; it's NegtionHash implents a BEEF Hash to determine if the recieving player manages to challenging player mchallenge to play. NegotiaionVerify determines that the recieving commintment matches it's secret to detect foul play before fliping the coin. NegotiateCoinFlip Determins which player will attack first. Then there's Message, where simply it just ensures that between the players the correctect info is beeing passed along depeding on which state the game is.
    Feild.c, the file implements from how the game should be dispayed,to determininig how attacks are determined. Lastly, there's Agent.c which run the whole darn thing, and depending on which state it is in it'll check which event is being called so it can appropriately complete tha action when playing the game.

Testing Strategy:
    We found it more effecive when after creating the files, it's best to debug them along with the test, for all the files. For Agent.c it's best to test with having coolterm open on both computer between the me and my parthner to see what the micro-controller is transmitting in between both microcontrolers.

What I learned
  - How Micro-Controlers can communicate with one another
  - How to make more effective tests that use random.h
  - How to use Beef Hash
  - How the NMEA 0183 parser works
  - How to create a an 'AI' with a while loop

What I liked about this Lab:
- It had battleship
- Got to work with an intresting and very helpful partner
- Rassured me how knowlegdable I am at writing better functions

