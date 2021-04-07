# CS4076 Project - GUI based version of Zork using C++ and Qt
## Week02 Introduction:
### We spent our first meeting going through the provided Zork code. We quickly decided that we would start from scratch, as we wanted more flexibility when creating a procedurally generated version of Zork. This session also consisted of us thinking about a unique theme for our game, as we wanted to make it interesting and special.
![Week02](https://imgur.com/7wAzE4A.png)
## Week03 Planning:
### This week was dominated by planning out how we were going to structure our project. This included thinking about the types or classes that we would need and how we would link them to the visual/event driven element of the entire assignment. We found it was very beneficial to brainstorm the kind of functions that would be required from an abstract point of view for each of them too.
![Week03](https://i.imgur.com/vZ53wT7.png)
## Week04 Early Development:
### Our first proper stint of programming consisted of us creating the class/header files that we originally planned out. We then proceeded to begin implementing Room and Item generation. The majority of the session centered around finding the most efficient ways of generating the different rooms and worlds in a procedural manner. We initially implemeted a tree-structure for creating a map.
## Week05 U-Turn:
### We quickly discovered that a tree-structure may not have been the best structure for containing all of the rooms in the worlds in our game. As a result this week resulted in us reworking our generation implementation. We then decided to store them in a 2D array. This solved a lot of the issues that we would face with the earlier structures. We also took this opportunity to migrate our now substantial code into QT itself.
## Week06 Room Generation:
### We spent the majority of this week completing room generation, as well as special room generation. Finishing this code allowed us to clean up our code. We used this aspect of the room generation to implement inheritance.
## Week07 Movement & General Fixes:
### We spent this week implementing the movement of the player. This was an important step that took a bit of time to implement properly. We also spent time working on general bugs and fixes.
## Week08 Map Generation:
### This week was the start of implementing some of the more advanced visual elements. QPainter was used to create a live map of the worlds and rooms in our game. They are drawn to the screen extremely efficiently and they also detail whether there is an item in the room. This feature took a chunk of time to implement due to us having to get to grasps with some of QT's specific features.
![Week08](https://i.imgur.com/vlhjVwN.png)
