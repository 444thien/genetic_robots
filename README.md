Self improving robots in a maze through the use of gene swapping, the top 100 performing robots are replicated to the slots of the bottom 100
(ensuring only the best and most common genes for traversing the maze are passed on). Each robot is assigned 16 sets of 5 genes, the first 4 genes checks
for a match using values North South West East of the robot while the last gene determines the direction the robot goes, if no match then the move of the last set
of genes is used (random move). They are placed in a 10x10 maze with borders and 40 batteries scattered throughout the maze, starting with 5 energy and each battery
= +1 energy. They are to move till their energy runs out. Change the outter most i loop condition ("i < 10") to desired amount of generation you wish to observe.
Through each generation it will display the average amount of batteries collected per robot as well as the robot with the highest and lowest as well.
well as the highest and lowest.
