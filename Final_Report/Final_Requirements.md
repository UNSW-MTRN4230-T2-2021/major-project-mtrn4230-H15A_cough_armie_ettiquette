**Requirements Analysis**

**Epic User Story 1**

As a customer, I want to enjoy a game of tic-tac-toe against an
artificial intelligence.

<table>
<colgroup>
<col style="width: 8%" />
<col style="width: 27%" />
<col style="width: 40%" />
<col style="width: 13%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr class="header">
<th>User Stories (UID)</th>
<th><p>Role-Goal-Benefit</p>
<p>(RGB)</p></th>
<th><p>Acceptance Criteria</p>
<p>(Specifications)</p></th>
<th>Time Point (1pt. = 3 hrs)</th>
<th><p>Priority</p>
<p>1 = High 4 = Low</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>US1</td>
<td>As a customer, I want to be able to play a game of tic-tac-toe so that I can feel like I am playing with real people.</td>
<td><ol type="1">
<li><p>Appropriate maximum operation speed, robot joint speeds must always be less than 50cm/s, acceleration less than 200cm/s^2, some testable values.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US2</td>
<td>As a customer, I want the board state to be correctly observed by the application so that I can play a regulated game.</td>
<td><ol type="1">
<li><p>The camera is able to correctly identify the type and location of pieces on the board.</p></li>
<li><p>The camera is able to identify the board.</p></li>
</ol></td>
<td><strong>3</strong></td>
<td><strong>1</strong></td>
</tr>
<tr class="odd">
<td>US3</td>
<td>As a customer, I want to be able to select the difficulty level, so I have a fair chance of winning.</td>
<td><ol type="1">
<li><p>User be able to select a difficulty level.</p>
<ol type="a">
<li><p>Easy (random placement function)</p></li>
<li><p>Hard (intelligence/strategy algorithm)</p></li>
</ol></li>
</ol></td>
<td><strong>2</strong></td>
<td><strong>3</strong></td>
</tr>
<tr class="even">
<td>US4</td>
<td>As a customer, I would like to have a user interface so that I can communicate with the A.I.</td>
<td><ol type="1">
<li><p>User can power off the user interface using a button.</p></li>
<li><p>User can start a new game using a button.</p></li>
<li><p>User can access game documentation using a button.</p></li>
<li><p>UI displays match number, previous games won, difficulty mode and time left to make a move.</p></li>
<li><p>The user is able to specify the position of their move through a virtual board in the UI.</p></li>
<li><p>During the robot’s turn, the user cannot make a move.</p></li>
<li><p>UI correctly displays the moves of the robot on the virtual game board.</p></li>
</ol></td>
<td><strong>2</strong></td>
<td><strong>1</strong></td>
</tr>
<tr class="odd">
<td>US5</td>
<td>As a customer, I want to know when I violate the rules of the game, so that I can play a fair and sensible game.</td>
<td><ol type="1">
<li><p>Alert the player when they make the following violations:</p>
<ul>
<li><p>Using the wrong piece</p></li>
<li><p>Piece overlapping with gridline</p></li>
<li><p>Playing more than one piece at a turn</p></li>
<li><p>Moving a piece already on the board</p></li>
<li><p>Taking too long to make a move.</p></li>
<li><p>Putting pieces out of place.</p></li>
</ul></li>
<li><p>The UI will be designed to prevent the user from making the following illegal moves:</p>
<ul>
<li><p>Moving when it is the robot’s turn</p></li>
<li><p>Making more than one move on their turn</p></li>
<li><p>Placing one of their pieces in a space that is already occupied</p></li>
</ul></li>
<li><p>The intelligence should abide by the same rules and should not make these violations.</p></li>
</ol></td>
<td><strong>4</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US6</td>
<td>As a customer, I want to be able to easily understand how to play the game, so that I can engage with it to my fullest capacity.</td>
<td><ol type="1">
<li><p>The UI notifies the user when a game starts.</p></li>
<li><p>The UI notifies the user of their victory, loss, or draw.</p></li>
<li><p>In one game you can play up to 3 subgames, with the winner determined by best of 3.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>1</strong></td>
</tr>
</tbody>
</table>

**Epic User Story 2**

As an investor, I want to ensure that the system is marketable.

<table>
<colgroup>
<col style="width: 8%" />
<col style="width: 27%" />
<col style="width: 41%" />
<col style="width: 13%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr class="header">
<th>User Stories (UID)</th>
<th><p>Role-Goal-Benefit</p>
<p>(RGB)</p></th>
<th><p>Acceptance Criteria</p>
<p>(Specifications)</p></th>
<th>Time Point (1pt. = 3 hrs)</th>
<th><p>Priority</p>
<p>1 = High 4 = Low</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>US7</td>
<td>As an investor, I want the robot, board, and game pieces simulation to be of good quality so I can have a marketable product.</td>
<td><ol type="1">
<li><p>Tic Tac Toe piece types should be easily distinguishable from each other and the game board by use of different colours and shapes.</p></li>
<li><p>When the robot is in motion, it should not collide with any object in its surroundings.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>4</strong></td>
</tr>
</tbody>
</table>

**Epic User Story 3**

As a client, I want an operational product that benefits my business.

<table>
<colgroup>
<col style="width: 8%" />
<col style="width: 26%" />
<col style="width: 41%" />
<col style="width: 13%" />
<col style="width: 9%" />
</colgroup>
<thead>
<tr class="header">
<th>User Stories (UID)</th>
<th><p>Role-Goal-Benefit</p>
<p>(RGB)</p></th>
<th><p>Acceptance Criteria</p>
<p>(Specifications)</p></th>
<th>Time Point (1pt. = 3 hrs)</th>
<th><p>Priority</p>
<p>1 = High 4 = Low</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>US8</td>
<td>As a client, I want the robot, game board, and game pieces to be similar to real world gameplay experience so I can better market the product.</td>
<td><ol type="1">
<li><p>Game pieces should have a minimum diameter of 4cm and a maximum diameter of 7cm.</p></li>
<li><p>The board should have a minimum size of 40cm and a maximum size of 60cm.</p></li>
<li><p>Simulation should not allow users to interfere with the robot or the game board. The user will only be able to spawn their own pieces.</p></li>
<li><p>All areas of the game board must be reachable by the robot (within the robot’s work envelope).</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US9</td>
<td>As a client, I want the robot system to be easy to troubleshoot so that I can minimise time spent dealing with bugs or program errors.</td>
<td><ol type="1">
<li><p>Program errors will be displayed in the console when they happen.</p></li>
<li><p>Program errors should occur in less 25% of cases when running the application.</p></li>
</ol></td>
<td><strong>3</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="odd">
<td>US10</td>
<td>As a client, I want the simulation to take up minimum amount of storage so that it can be efficiently stored.</td>
<td><ol type="1">
<li><p>The application should be runnable on a virtual machine running the Ubuntu OS.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US11</td>
<td>As a client, I want to be able to access clear guidance through documentation, so I know how to use the system.</td>
<td><ol type="1">
<li><p>Documentation should be accessible through the user interface.</p></li>
<li><p>Documentation should describe the function of each button, menu item and text label in the user interface.</p></li>
</ol></td>
<td><strong>3</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="odd">
<td>US12</td>
<td>As a client, I want there to be a maximum time limit for each game, to maximise the number of games played, and hence profits.</td>
<td><ol type="1">
<li><p>A timer should be used to ensure that user moves do not take longer than two minutes each. If a user takes longer than two minutes to move, the robot should win by default.</p></li>
<li><p>The timer should be visible to the user via the user interface so that they know how much time they have left.</p></li>
<li><p>A single game setting must not take longer than 15 minutes.</p></li>
<li><p>The robot should not take excessive time to make its decision (total robot decision making and movement within 30 seconds)</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>4</strong></td>
</tr>
</tbody>
</table>
