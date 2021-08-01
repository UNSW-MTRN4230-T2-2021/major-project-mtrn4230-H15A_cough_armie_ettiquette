**Key:**

**AH: Arielle Hui, DL: Daniel Lin, JT: Jovanni Tjuandi, NA: Nethmini
Alahakoon**

<table>
<thead>
<tr class="header">
<th><strong>WBS Level</strong></th>
<th><strong>Task Name</strong></th>
<th><strong>Task Description</strong></th>
<th><strong>Assigned</strong></th>
<th><strong>Resources</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><strong>1</strong></td>
<td><strong>Game Piece and Board Creation</strong></td>
<td></td>
<td><strong>NA</strong></td>
<td></td>
</tr>
<tr class="even">
<td>1.1</td>
<td>Game Piece and Board Design Simulation</td>
<td>Design game pieces and board. Testing of game pieces and board with UI and robot.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td><strong>2</strong></td>
<td><strong>User Interface</strong></td>
<td></td>
<td><strong>AH</strong></td>
<td></td>
</tr>
<tr class="even">
<td>2.1</td>
<td>User Interface Design</td>
<td>Plan the design of the user interface before implementation on the system.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>2.2</td>
<td>User Interface Programming</td>
<td>Implement the design plan for the user interface using simulation software.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>2.3</td>
<td>User Interface Testing</td>
<td>Test that the user interface works as intended in all scenarios, including edge cases.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>2.4</td>
<td>User Interface Finalisation</td>
<td>Make improvements to the user interface as necessary, depending on the results obtained during the testing phase.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td><strong>3</strong></td>
<td><strong>Robot Arm Programming and Control</strong></td>
<td></td>
<td><strong>JT, NA</strong></td>
<td></td>
</tr>
<tr class="odd">
<td>3.1</td>
<td>Robot Waiting Programming</td>
<td>The robot will be programmed to move back to a designated home position, when waiting for the player to make a move, or when the arm is idling.</td>
<td>JT, NA</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>3.2</td>
<td>Robot “Pick Piece” Programming</td>
<td>The robot will be programmed to pick up a piece from a defined location, upon its turn.</td>
<td>JT, NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>3.3</td>
<td>Robot “Place Piece” Programming</td>
<td>The robot will be programmed to be able to place a piece on the board, in any of nine squares, upon its turn.</td>
<td>JT, NA</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>3.4</td>
<td>Smooth Operation of Arm</td>
<td>Robot arm moves smoothly when executing all movements.</td>
<td>JT, NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td><strong>4</strong></td>
<td><strong>Camera Programming and Control</strong></td>
<td></td>
<td><strong>DL</strong></td>
<td></td>
</tr>
<tr class="even">
<td>4.1</td>
<td>Piece Type and Quantity Detection</td>
<td>The output from the camera will be analysed to determine the types of pieces present in the playing area (e.g. X’s or O’s), and how many of each type there are.</td>
<td>DL</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>4.2</td>
<td>Piece Location Detection</td>
<td>The output from the camera will be analysed to determine the x and y coordinates of pieces present in the playing area, and which board square they are in (if applicable).</td>
<td>DL</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td><strong>5</strong></td>
<td><strong>Game Supervisor System</strong></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr class="odd">
<td>5.1</td>
<td>Invalid Piece Placement Check</td>
<td><p>Detection of:</p>
<ul>
<li><p>Wrong piece placed on the board</p></li>
<li><p>Wrong number of pieces placed on the board</p></li>
<li><p>Piece(s) placed at an invalid position on the board</p></li>
<li><p>Piece(s) removed from board</p></li>
<li><p>Invalid change in board state</p></li>
</ul></td>
<td>DL</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>5.2</td>
<td>Board State Saving</td>
<td>The system will be able to save the board state from the previous turn and update this each turn as the game progresses.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>5.3</td>
<td>Game Time-Out System</td>
<td>The system will be programmed such that each move cannot take longer than two minutes, with a single game not taking more than approximately ten minutes.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td><strong>6</strong></td>
<td><strong>Game Logic Algorithm</strong></td>
<td></td>
<td><strong>JT</strong></td>
<td></td>
</tr>
<tr class="odd">
<td><strong>6.1</strong></td>
<td>Winning Algorithm</td>
<td>This algorithm will be programmed to identify whether the robot or player has won, after three X’s or O’s have been placed in a straight line.</td>
<td>JT</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>6.2</td>
<td>Logic for “Easy” Difficulty</td>
<td>This difficulty will be programmed such that on the robot’s turn, it will place pieces in squares randomly.</td>
<td>JT</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>6.3</td>
<td>Logic for “Hard” Difficulty</td>
<td>This difficulty will be programmed such that on the robot’s turn, it will strategically place pieces in squares which increase its likelihood of winning and/or decrease the player’s likelihood of winning.</td>
<td>JT</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>6.4</td>
<td>Overall Winner Logic</td>
<td>The algorithm will determine the overall winner of the games based on a ‘best of three’ system.</td>
<td>JT</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td><strong>7</strong></td>
<td><strong>User Manual and Safety Documentation</strong></td>
<td></td>
<td><strong>NA</strong></td>
<td></td>
</tr>
<tr class="even">
<td>7.1</td>
<td>Documentation Creation</td>
<td>Write instructions for user to assist with possible errors encountered during the game.</td>
<td>NA</td>
<td>Technical Writer</td>
</tr>
<tr class="odd">
<td><strong>8</strong></td>
<td><strong>Test Cases</strong></td>
<td></td>
<td><strong>AH, JT, DL, NA</strong></td>
<td></td>
</tr>
<tr class="even">
<td>9.1</td>
<td>Test: Identification of Piece Type and Location</td>
<td>Test cases T1 completed.</td>
<td>DL</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.2</td>
<td>Test: Pieces Correctly Positioned</td>
<td>Test case T2 completed.</td>
<td>DL</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.3</td>
<td>Test: Accessibility and Ergonomics</td>
<td>Test cases T4 and T5 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.4</td>
<td>Test: Difficulty Levels</td>
<td>Test case T3 completed.</td>
<td>JT</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.5</td>
<td>Test: Game Winner Check</td>
<td>Test cases T9 and T10 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.6</td>
<td>Test: User Interface</td>
<td>Test case T8 completed.</td>
<td>AH</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.7</td>
<td>Test: Movement Quality</td>
<td>Test cases T6 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.8</td>
<td>Test: Rule Violations</td>
<td>Test case T7 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.9</td>
<td>Test: Game Piece Quality</td>
<td>Test case T11 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.10</td>
<td>Test: Troubleshooting</td>
<td>Test case T14, T15 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.11</td>
<td>Test: Documentation Quality</td>
<td>Test case T12 and T13 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.12</td>
<td>Test: Game Time Limits</td>
<td>Test case T17, T18 , T19 and T20 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="even">
<td>9.13</td>
<td>Test: Quality of System</td>
<td>Test case T16 completed.</td>
<td>NA</td>
<td>Programmer</td>
</tr>
<tr class="odd">
<td>9.13</td>
<td>Final Testing</td>
<td>Once the entire system is fully operational, the game will be thoroughly tested before release.</td>
<td>AH, JT, DL, NA</td>
<td>Senior Programmer, Programmer x 3</td>
</tr>
<tr class="even">
<td><strong>9</strong></td>
<td><strong>System Integration</strong></td>
<td></td>
<td><strong>AH, DL, JT</strong></td>
<td></td>
</tr>
<tr class="odd">
<td>9.1</td>
<td>Basic System Integration</td>
<td>Integrate User Interface, Safety Features, Robot Arm Control, Camera Control and Game Logic Algorithm. Get the Basic System working so that a minimum viable product is achieved.</td>
<td>AH, DL, JT</td>
<td>Senior Programmer, Programmer x 2</td>
</tr>
<tr class="even">
<td>9.2</td>
<td>Full System Integration</td>
<td>Integrate Game Supervisor System with the Basic System so that the Full System is created.</td>
<td>AH, DL, JT</td>
<td>Senior Programmer, Programmer x 2</td>
</tr>
</tbody>
</table>

| **Resource**                                  | **Cost ($)**             |                |                                            |                 |        |
| --------------------------------------------- | ------------------------ | -------------- | ------------------------------------------ | --------------- | ------ |
| **Employee**                                  | **Role**                 | **Salary ($)** | **Hourly Rate w/ Company Overhead ($/hr)** | **Total Hours** |        |
|                                               | Project Manager          | 99,525         | 82.02                                      | 210             | 17,224 |
|                                               | Senior Programmer        | 116,149        | 95.73                                      | 96              | 9,190  |
|                                               | Programmer               | 70,114         | 57.79                                      | 306             | 17,683 |
|                                               | Technical Writer         | 81,281         | 66.99                                      | 9               | 603    |
| **General (Hardware, Software, Props, etc.)** | **Component**            |                |                                            |                 |        |
|                                               | UR5e Robot (REMOVED)     | 0              |                                            |                 |        |
|                                               | Vacuum Gripper (REMOVED) | 0              |                                            |                 |        |
|                                               | Camera (REMOVED)         | 0              |                                            |                 |        |
|                                               | Wooden Board (REMOVED)   | 0              |                                            |                 |        |
|                                               | Acrylic (REMOVED)        | 0              |                                            |                 |        |
|                                               | Software (ROS, URSim)    | 0              |                                            |                 |        |
| Total Resource Cost                           | 44,700                   |                |                                            |                 |        |

**References:**

**All Average Australian Employee salaries from PayScale**

**https://www.payscale.com/research/AU**

<https://shxiangjing.en.alibaba.com/product/62225088738-807439491/Universal_UR5_UR5e_robot_arm_price_and_total_station_robot_of_pick_and_place_robot_machine.html>

<https://automationdistribution.com/robotiq-epick-vacuum-gripper-for-universal-robots/>

<https://www.bunnings.com.au/customwood-mdf-3mm-900-x-600mm-white-melamine-backing_p0610153>

<https://www.bunnings.com.au/search/products?q=acrylic%20sheet&sort=BoostOrder&page=1>
