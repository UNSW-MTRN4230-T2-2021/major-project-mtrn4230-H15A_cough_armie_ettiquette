**Work Breakdown Structure and Baseline Schedule**

**Key:**

**AH: Arielle Hui, DL: Daniel Lin, JT: Jovanni Tjuandi, NA: Nethmini
Alahakoon**

<table>
<thead>
<tr class="header">
<th><p><strong>WBS</strong></p>
<p><strong>Code</strong></p></th>
<th><strong>Task Name</strong></th>
<th><strong>Task Description</strong></th>
<th><strong>Duration</strong></th>
<th><strong>Start Date</strong></th>
<th><strong>End Date</strong></th>
<th><strong>Assigned</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><strong>1</strong></td>
<td><strong>Game Piece and Board Creation</strong></td>
<td></td>
<td><strong>2 days</strong></td>
<td><strong>W8 Thurs</strong></td>
<td><strong>W10 Mon</strong></td>
<td><strong>NA</strong></td>
</tr>
<tr class="even">
<td>1.1</td>
<td>Game Piece and Board Design Simulation</td>
<td>Design game pieces and board. Testing of game pieces and board with UI and robot.</td>
<td>2 hours</td>
<td>W8 Thurs</td>
<td>W10 Mon</td>
<td>NA</td>
</tr>
<tr class="odd">
<td><strong>2</strong></td>
<td><strong>User Interface</strong></td>
<td></td>
<td><strong>10 days</strong></td>
<td><strong>W8 Wed</strong></td>
<td><strong>W10 Tue</strong></td>
<td><strong>AH</strong></td>
</tr>
<tr class="even">
<td>2.1</td>
<td>User Interface Design</td>
<td>Plan the design of the user interface before implementation on the system.</td>
<td>3 hours</td>
<td>W8 Wed</td>
<td>W9 Thurs</td>
<td>AH</td>
</tr>
<tr class="odd">
<td>2.2</td>
<td>User Interface Programming</td>
<td>Implement the design plan for the user interface using simulation software.</td>
<td>6 hours</td>
<td>W8 Thurs</td>
<td>W9 Sat</td>
<td>AH</td>
</tr>
<tr class="even">
<td>2.3</td>
<td>User Interface Testing</td>
<td>Test that the user interface works as intended in all scenarios, including edge cases.</td>
<td>6 hours</td>
<td>W9 Sat</td>
<td>W9 Sun</td>
<td>AH</td>
</tr>
<tr class="odd">
<td>2.4</td>
<td>User Interface Finalisation</td>
<td>Make improvements to the user interface as necessary, depending on the results obtained during the testing phase.</td>
<td>1 day</td>
<td>W9 Sun</td>
<td>W10 Mon</td>
<td>AH</td>
</tr>
<tr class="even">
<td><strong>3</strong></td>
<td><strong>Robot Arm Programming and Control</strong></td>
<td></td>
<td><strong>4 days</strong></td>
<td><strong>W8 Thurs</strong></td>
<td><strong>W9 Mon</strong></td>
<td><strong>JT, NA</strong></td>
</tr>
<tr class="odd">
<td>3.1</td>
<td>Robot Waiting Programming</td>
<td>The robot will be programmed to move back to a designated home position, when waiting for the player to make a move, or when the arm is idling.</td>
<td>3 hours</td>
<td>W8 Thurs</td>
<td>W8 Fri</td>
<td>JT, NA</td>
</tr>
<tr class="even">
<td>3.2</td>
<td>Robot “Pick Piece” Programming</td>
<td>The robot will be programmed to pick up a piece from a defined location, upon its turn.</td>
<td>3 hours</td>
<td>W8 Fri</td>
<td>W8 Sat</td>
<td>JT, NA</td>
</tr>
<tr class="odd">
<td>3.3</td>
<td>Robot “Place Piece” Programming</td>
<td>The robot will be programmed to be able to place a piece on the board, in any of nine squares, upon its turn.</td>
<td>3 hours</td>
<td>W8 Sat</td>
<td>W8 Sun</td>
<td>JT, NA</td>
</tr>
<tr class="even">
<td>3.4</td>
<td>Smooth Operation of Arm</td>
<td>Robot arm moves smoothly when executing all movements.</td>
<td>2 hours</td>
<td>W8 Sun</td>
<td>W9 Mon</td>
<td>JT, NA</td>
</tr>
<tr class="odd">
<td><strong>4</strong></td>
<td><strong>Camera Programming and Control</strong></td>
<td></td>
<td><strong>4 days</strong></td>
<td><strong>W8 Thurs</strong></td>
<td><strong>W10 Mon</strong></td>
<td><strong>DL</strong></td>
</tr>
<tr class="even">
<td>4.1</td>
<td>Piece Type and Quantity Detection</td>
<td>The output from the camera will be analysed to determine the types of pieces present in the playing area (e.g. X’s or O’s), and how many of each type there are.</td>
<td>4 hours</td>
<td>W8 Thurs</td>
<td>W9 Thurs</td>
<td>DL</td>
</tr>
<tr class="odd">
<td>4.2</td>
<td>Piece Location Detection</td>
<td>The output from the camera will be analysed to determine the x and y coordinates of pieces present in the playing area, and which board square they are in (if applicable).</td>
<td>8 hours</td>
<td>W8 Thurs</td>
<td>W10 Mon</td>
<td>DL</td>
</tr>
<tr class="even">
<td><strong>5</strong></td>
<td><strong>Game Supervisor System</strong></td>
<td></td>
<td><strong>5 days</strong></td>
<td><strong>W7 Wed</strong></td>
<td><strong>W9 Fri</strong></td>
<td></td>
</tr>
<tr class="odd">
<td>5.1</td>
<td>Rule Violation Check</td>
<td><p>Detection of:</p>
<ul>
<li><p>Wrong piece placed on the board</p></li>
<li><p>Piece(s) placed at an invalid position on the board</p></li>
<li><p>Invalid change in board state</p></li>
</ul></td>
<td>2 days</td>
<td>W7 Wed</td>
<td>W9 Mon</td>
<td>DL</td>
</tr>
<tr class="even">
<td>5.2</td>
<td>Board State Saving</td>
<td>The system will be able to save the board state from the previous turn and update this each turn as the game progresses.</td>
<td>2 hours</td>
<td>W9 Tues</td>
<td>W9 Thurs</td>
<td>DL</td>
</tr>
<tr class="odd">
<td>5.3</td>
<td>Game Time-Out System</td>
<td>The system will be programmed such that each move cannot take longer than two minutes, with a single game not taking more than approximately eight to ten minutes.</td>
<td>1 hour</td>
<td>W9 Fri</td>
<td>W9 Fri</td>
<td>AH</td>
</tr>
<tr class="even">
<td><strong>6</strong></td>
<td><strong>Game Logic Algorithm</strong></td>
<td></td>
<td><strong>7 days</strong></td>
<td><strong>W7 Wed</strong></td>
<td><strong>W8 Wed</strong></td>
<td><strong>JT</strong></td>
</tr>
<tr class="odd">
<td>6.1</td>
<td>Logic for “Easy” Difficulty</td>
<td>This difficulty will be programmed such that on the robot’s turn, it will place pieces in squares randomly.</td>
<td>1 hour</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>JT</td>
</tr>
<tr class="even">
<td>6.2</td>
<td>Logic for “Hard” Difficulty</td>
<td>This difficulty will be programmed such that on the robot’s turn, it will strategically place pieces in squares which increase its likelihood of winning and/or decrease the player’s likelihood of winning.</td>
<td>1 day</td>
<td>W7 Wed</td>
<td>W7 Thurs</td>
<td>JT</td>
</tr>
<tr class="odd">
<td>6.3</td>
<td>Winning Algorithm</td>
<td>This algorithm will be programmed to identify whether the robot or player has won, after three X’s or O’s have been placed in a straight line.</td>
<td>1 day</td>
<td>W7 Thurs</td>
<td>W7 Fri</td>
<td>JT</td>
</tr>
<tr class="even">
<td>6.4</td>
<td>Overall Winner Logic</td>
<td>The algorithm will determine the overall winner of the games based on a ‘best of three’ system.</td>
<td>2 hours</td>
<td>W7 Fri</td>
<td>W7 Sat</td>
<td>JT</td>
</tr>
<tr class="odd">
<td>6.5</td>
<td>Implementation of algorithms in C++</td>
<td>Having the implementation of each algorithm in isolation and acting as black boxes, this should be implemented in C++</td>
<td>5 days</td>
<td>W7 Sat</td>
<td>W8 Wed</td>
<td>JT</td>
</tr>
<tr class="even">
<td><strong>7</strong></td>
<td><strong>Documentation Write-Up</strong></td>
<td></td>
<td><strong>1 day</strong></td>
<td><strong>W11 Mon</strong></td>
<td><strong>W11 Fri</strong></td>
<td><strong>NA</strong></td>
</tr>
<tr class="odd">
<td>7.1</td>
<td>Documentation Creation</td>
<td>Write instructions for user to assist with possible errors encountered during the game.</td>
<td>1 day</td>
<td>W11 Mon</td>
<td>W11 Fri</td>
<td>NA</td>
</tr>
<tr class="even">
<td><strong>8</strong></td>
<td><strong>Test Cases</strong></td>
<td></td>
<td><strong>3 days</strong></td>
<td><strong>W6 Mon</strong></td>
<td><strong>W11 Fri</strong></td>
<td><strong>AH, JT, DL, NA</strong></td>
</tr>
<tr class="odd">
<td>8.1</td>
<td>Test: Identification of Piece Type and Location</td>
<td>Test cases T1 completed.</td>
<td>1 hour</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>DL</td>
</tr>
<tr class="even">
<td>8.2</td>
<td>Test: Pieces Correctly Positioned</td>
<td>Test case T2 completed.</td>
<td>1 hour</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>DL</td>
</tr>
<tr class="odd">
<td>8.3</td>
<td>Test: Accessibility and Ergonomics</td>
<td>Test cases T4 and T5 completed.</td>
<td>2 hours</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.4</td>
<td>Test: Difficulty Levels</td>
<td>Test case T3 completed.</td>
<td>1 hour</td>
<td>W9 Fri</td>
<td>W9 Fri</td>
<td>JT</td>
</tr>
<tr class="odd">
<td>8.5</td>
<td>Test: Game Winner Check</td>
<td>Test cases T9 and T10 completed.</td>
<td>1 hour</td>
<td>W10 Mon</td>
<td>W10 Mon</td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.6</td>
<td>Test: User Interface</td>
<td>Test case T8 completed.</td>
<td>1 hour</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>AH</td>
</tr>
<tr class="odd">
<td>8.7</td>
<td>Test: Movement Quality</td>
<td>Test cases T6 completed.</td>
<td>1 hour</td>
<td>W7 Wed</td>
<td>W7 Wed</td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.8</td>
<td>Test: Rule Violations</td>
<td>Test case T7 completed.</td>
<td>2 hours</td>
<td>W10 Mon</td>
<td>W10 Mon</td>
<td>NA</td>
</tr>
<tr class="odd">
<td>8.9</td>
<td>Test: Game Piece Quality</td>
<td>Test case T11 completed.</td>
<td>1 hour</td>
<td>W6 Tues</td>
<td>W6 Tues</td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.10</td>
<td>Test: Troubleshooting</td>
<td>Test case T14, T15 completed.</td>
<td>1 hour</td>
<td>W10 Fri</td>
<td>W10 Fri</td>
<td>NA</td>
</tr>
<tr class="odd">
<td>8.11</td>
<td>Test: Documentation Quality</td>
<td>Test case T12 and T13 completed.</td>
<td>1 hour</td>
<td>W10 Thurs</td>
<td>W10 Thurs</td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.12</td>
<td>Test: Game Time Limits</td>
<td>Test case T17, T18 , T19 and T20 completed.</td>
<td>1 hour</td>
<td>W10 Mon</td>
<td>W10 Mon</td>
<td>NA</td>
</tr>
<tr class="odd">
<td>8.13</td>
<td>Test: Quality of System</td>
<td>Test case T16 completed.</td>
<td></td>
<td></td>
<td></td>
<td>NA</td>
</tr>
<tr class="even">
<td>8.14</td>
<td>Final Testing</td>
<td>Once the entire system is fully operational, the game will be thoroughly tested before release.</td>
<td>2 days</td>
<td>W11 Thurs</td>
<td>W11 Fri</td>
<td>AH, JT, DL, NA</td>
</tr>
<tr class="odd">
<td><strong>9</strong></td>
<td><strong>System Integration</strong></td>
<td></td>
<td><strong>10 days</strong></td>
<td><strong>W10 Mon</strong></td>
<td><strong>W11 Wed</strong></td>
<td><strong>AH, DL, JT</strong></td>
</tr>
<tr class="even">
<td>9.1</td>
<td>Basic System Integration</td>
<td>Integrate User Interface, Safety Features, Robot Arm Control, Camera Control and Game Logic Algorithm. Get the Basic System working so that a minimum viable product is achieved.</td>
<td>1 week</td>
<td>W10 Mon</td>
<td>W10 Fri</td>
<td>AH, DL, JT, NA</td>
</tr>
<tr class="odd">
<td>9.2</td>
<td>Full System Integration</td>
<td>Integrate Game Supervisor System with the Basic System so that the Full System is created.</td>
<td>3 days</td>
<td>W11 Mon</td>
<td>W11 Wed</td>
<td>AH, DL, JT, NA</td>
</tr>
</tbody>
</table>

**Notes:**

At completion of game, user clears the board and resets game piece
piles.

We will need to initialise board location on the robot before starting
the game. This may be done via teaching it a new plane.

Will it be extra work to identify pieces (e.g. X pieces) at different
orientations on the board?

I think it will be too much work for four of us to implement a token
system.

Game Interface: Detection of user placing piece and pressing button on
message screen

**Game Supervisor System Functions**

  - The ability to save the board state

  - Detection of single piece placed correctly

  - Detection of user placing no pieces

  - Detection of user placing more than one piece

  - Detection of piece placed at an invalid location

  - Detection of wrong piece placed

  - Detection of foreign object on game board (too complicated I think)

  - Detection of piece removed from game board

  - Invalid change in board state (e.g. piece locations changed)

We have from Saturday Week 5 to Friday Week 12 (7 weeks -\> 7x5=35 days)
