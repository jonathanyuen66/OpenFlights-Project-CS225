# CS 225 Final Project: OpenFlights
## Team Members: zihengc2-haoyu9-yuen9-rmday2

## Deliverables (Also in main branch)
* [Report](https://github-dev.cs.illinois.edu/cs225-sp21/rmday2-yuen9-zihengc2-haoyu9/blob/master/CS%20225%20Final%20Project%20Report.pdf)
* [Presentation Video](https://youtu.be/r_ltZNUqKkw)
* [Presentation Slides](https://github-dev.cs.illinois.edu/cs225-sp21/rmday2-yuen9-zihengc2-haoyu9/blob/master/CS%20225%20Final%20Project%20Presentation.pdf)

## Introduction
Our final project uses [OpenFlights](https://openflights.org/data.html) airports and routes data to construct a graph of airport vertices.
Djikstra's algorithm is used to find the shortest path between two airports, a Landmark Path algorithm
is used to find the shortest path between two airports with landmarks in between, and a Page Rank algorithm is used to find important airports.

## File description(code and data)
Below are some brief descriptions of the files in our codebase.  Function descriptions can be found in the individual files:
* Airport: the Airport class is used for defining the vertices of our graph structure. Each airport is constructed with a name, an ID, a city, a country, and latitude and longitude coordinates (this data is retrieved from airports.dat)
* Flight : The Flights class is used for constructing the edges(flights) between two airports where the weight edge is the distance between the two
* airport_graph : This is our graphs class that supports the creation and insertion of vertices and edges
* BFS : Implementation of a BFS graph traversal
* Djikstras : Implementation of Djikstra's algorithm to find shortest path
* Landmark : Implementation of Landmark Path algorithm
* PageRank : Implementation of the Page Rank algorithm
* main : Where the tests for the algorithms are located

## How to run the program
The program can be ran by using the 'finalproject' executable:
```
make all
./finalproject
```
The user would then choose the dataset that construct our graph.  
Afterwards, the user would be prompted with instructions on how to run the various operations:
```
(0) Using BFS, traverse all of the graph from a given airport 
(1) Using BFS, traverse a given number of moves of the graph from a given airport
(2) Using BFS, traverse the graph until a destination airport from a given airport
(3) Calculate the shortest path between two airports
(4) Calculate the shortest path between two airports passing one landmark
(5) Calculate the shortest path between two airports passing two landmark
(6) PageRank
```  
The operations may require the user to provide custom inputs.  
After computation, the result would be printed out in the terminal.  
To end the program anytime, use `Ctrl+C`.

## Main function description
Our main function consists of 7 cases where the user can interact with the various parts of our project.  
The user will be able to see the results of running a BFS traversal, Pagerank algorith, Landmark Path algorith, and Djikstra's algorithm.

## Test Description
Our tests can be ran with
```
make test
./test
```  
Our tests test the functionality of
* constructing an Airport 
* constructing a graph
* the Pagerank algorithm
* the BFS traversal
* Djikstra's algorithm
* the Landmark Path algorithm

## References
* [Lecture Materials](https://courses.engr.illinois.edu/cs225/sp2021/)
* [Calculating distances from coordinates](https://www.geeksforgeeks.org/program-distance-two-points-earth/)
* [Converting text to string in C++](https://tomeko.net/online_tools/cpp_text_escape.php?lang=en)


## Team Contract (zihengc2-haoyu9-yuen9-rmday2)
### Communication
#### Team Meetings
Our team will meet at least once a week every Tuesday from 6-8 PM using Zoom. Each member will rotate being the designated note-taker, starting with zihengc2. Notes will be stored on a Google document, time-stamped for each meeting. The note-taker is also responsible for drafting the weekly development log entry, which is approved by the team at the start of the following week’s meeting.
#### Assistance 
Each team member can be contacted through GroupMe and email. Outside of emergencies or other commitments, we commit to responding to emails within 24hours.
#### Respect 
The note-taker for the week will also serve as the ‘project lead’ for the weekly meeting. Their role is to ensure that every member of the group has had a chance to speak or state their opinion about a design decision or any other topic related to the final project. All decisions will be accepted by simple majority – while unanimous agreement is preferred, it is not required. By signing this document, each member of the team commits to adhering to the decisions made, even if they personally disagree with them.
### Collaboration
#### Work Distribution
Each week, the necessary deliverables for the week will be determined by the full team and each member will volunteer to work on one or more deliverables. If this leads to an unbalanced workload for the week, we will make adjustments as necessary.
#### Time Commitment
To ensure an equal distribution of work, each member is expected to independently work no less than two and no more than six hours per week on the project. If a deliverable ends up taking more time, the rest of the team should be pulled in to assist with the unforeseen complication, with each member taking an equal share of the workload or programming in pairs. It is the team’s responsibility, not the individual’s responsibility, to make sure a weekly deliverable is finished by the end of the week. However if a team member is habitually not completing their tasks, they may be asked – politely – to explain their circumstances. Based on their explanation further actions, such as alerting a staff member, may be taken on a case by case basis decided by the other team members.
#### Conflict Resolution 
All conflicts within the team will be decided through a group discussion that will include our project mentor if necessary. Any issues that may be best decided by majority rule may be done through vote.
### Signatures: 
Jonathan Yuen, Ziheng Chen, Ryan Day, Kevin Zhou
