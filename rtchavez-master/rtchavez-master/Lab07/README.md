# Lab 7

## Reuben Chavez(rtchavez)

## 5-13-22

Collaborators:

For this lab I attended section twice times this week, from Navid and Xiangjian Gao sections. both times I have asked helped from T.A. there and fellow student. I would also meet with students outside of section to talk over how our code should work.

Summary:

Lab7 was an intro to understanding how to use for finite state machines and how they apply to our everyday appliances. Along with implementing features from the last lab - ADC, Buttons, LEDs, and the OLED, along with time Interrupts - the lab sets to apply how we can make a singular state machine. Highlight in the Lab included : understanding how state machines diagram apply as pseudocode, changing states when certain inputs apply,using global variables as timer, and implementing events;

Approach:

I started by  working on the  pseudocode for the as commits runOvensm at first. I then worked on getting the necessary code for both ISR and the update OLED. I them wrote the necessary data for the ovenData, along with the event flags. After writing over the commits, I would then check the runOven if the case setup and the updateOLED would work. I would then revise the conditional statements for OvenOLED to see it check right mode. I spent a lot of the time seeing why my adc was in accurate, only to figure out it was because it didn't set the event flag to true in the while loop. I spent most of the last day to fix my timer, and the switching between th mode properly.

Overall Feeling:

- Interesting Lab, can be done in less time compared to the previous lab, would have turned earlier if I worked on it more on Tuesday.
- I spent over 20 hours on this lab, mainly because my pick it takes time to upload code properly, and because of my adc not updating
- the hardest part I would say was making the timer and LED update properly since it required extra math
