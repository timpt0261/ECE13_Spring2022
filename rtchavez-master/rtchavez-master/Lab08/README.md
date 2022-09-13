# Lab 8

## Reuben Chavez(rtchavez)

## 5-20-22

Collaborators:

For this lab I attended section twice times this week, from Navid and Xiangjian Gao sections. both times I have asked helped from T.A. there and fellow student. I would also meet with students outside of section to talk over how our code should work.

Summary:
    Lab08 is a project that creates a simple rpg, with the use of files. The progtam itself is made of two libraries (game.c and player.c) and one main. Where the game.c is used to pasrse each file for the room title, item's required , room description, item's contained, and room exits. The player.c is used within the game.c to deterimine which description it should go to depending on the player's inventory, Depending if they have the key or not they cab progress throught the level. the main it self prints all the info on the terminal, and asks for user input on which direction they should go.

Approach:

I started by working on the Game.c. In my first version I thought of implemting all the function of the current helper functions  in each function for the game.c, wher it would parse throught the file looking for something specific and then save it save in the parameter. At the time the helper function only opened the files, but then on my second implementation it's open the file, parrsed the entierily throught the file, saved designated info in the struct, and close the file. The GameGet*() functions would only call strcpy the the desinated thing in the struct and return the size. The GameGo*() on the other hand would call the helper functin with the saved exit number from the file, to then reapaet the process. In the middle of getting my game.c to work, iasked a classmate on how they implemented the player.c and explaned to me that it pratactily used a struct that saved an array and the array length. I then implemeted the file where I create a static verion of the struct the intilazed with 0 and has a size of one. The last thing I implemented was the main, where I had the idea of using the a while and a switch case, but then after attending section I had implemented a passFlag and and a Death flag so thar 1) the game wouln'd prit the room description twice after input, and 2) create a little quircky thing that ends the game whenever the player dies.


Overall Feeling:

The overall result is the lab works pretty well, but I wished I knew alternative ways to have fixed the latest problem, mainly because I have to copy and paste my before the while loop and in the while loop. Intially I just wanted where that same code is only called once. The project itself wasn't so bad, since debugging maily relied on fixing the fread and adding in event flag, ther was also a lot of mental math, when it came to parsing the file correcly. Mainly becuase I just wanted to make sure my code would be running mostly smoothly durring the few try. I am glad that this project is worth a lot less points, but my only complaint is the document was very complicit on how the gam.c and player,c should work as it was pretty vague in the document. What mainly helped was an image in the class discord that showed how the files would be organized, as when opeing it on a hex edtor I was able to easily understand how the game.c should iterate throught the file correclty.  