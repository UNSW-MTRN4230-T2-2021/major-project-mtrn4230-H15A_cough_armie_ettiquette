**Requirements Analysis**

**Epic User Story 1**

As a customer, I want to enjoy a game of tic-tac-toe against an
artificial intelligence.

<table>
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
<li><p>Robot arm smoothly places game piece in the correct positions.</p></li>
<li><p>Appropriate maximum operation speed, robot joint speeds must always be less than 50cm/s, acceleration less than 200cm/s^2, some testable values.</p></li>
<li><p>System state is correctly observed through the mounted camera looking over the gameplay area.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US2</td>
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
<tr class="odd">
<td>US3</td>
<td>As a customer, I would like to have a user interface so that I can communicate with the A.I.</td>
<td><ol type="1">
<li><p>User interface is ergonomic.</p></li>
<li><p>Appealing UI</p></li>
<li><p>Clear commands, menu, messages</p></li>
<li><p>System correctly responds to user input.</p></li>
</ol></td>
<td><strong>2</strong></td>
<td><strong>1</strong></td>
</tr>
<tr class="even">
<td>US4</td>
<td>As a customer, I want to know when I violate the rules of the game, so that I can play a fair and sensible game.</td>
<td><ol type="1">
<li><p>Alert the player when they make violations such as</p>
<ul>
<li><p>Using the wrong piece</p></li>
<li><p>Piece overlapping with gridline or another piece</p></li>
<li><p>Playing more than one piece at a turn</p></li>
<li><p>Moving a piece already on the board</p></li>
<li><p>Taking too long to make a move.</p></li>
<li><p>Putting pieces out of place.</p></li>
</ul></li>
<li><p>The intelligence should abide by the same rules and should not make these violations.</p></li>
</ol></td>
<td><strong>4</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="odd">
<td>US5</td>
<td>As a customer, I want to be able to easily understand how to play the game, so that I can engage with it to my fullest capacity.</td>
<td><ol type="1">
<li><p>Clear and common game rules</p></li>
<li><p>Sequential workflow in the interface.</p></li>
<li><p>Notify of their victory, loss, or draw.</p></li>
<li><p>In one turn you can play up to 3 games, with the winner determined by best of 3.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>1</strong></td>
</tr>
</tbody>
</table>

**  
**

**Epic User Story 2**

As an investor, I want to ensure that the system is marketable.

<table>
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
<td>US6</td>
<td>As an investor, I want the robot, board, and game pieces simulation to be of good quality so I can have a marketable product.</td>
<td><ol type="1">
<li><p>Quality and appearance of game board and robot in Gazebo for the tic-tac-toe board and game pieces.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>4</strong></td>
</tr>
</tbody>
</table>

**Epic User Story 3**

As a client, I want an operational product that benefits my business.

<table>
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
<td>As a client, I want the robot, game board, and game pieces to be similar to real world gameplay experience so I can better market the product.</td>
<td><ol type="1">
<li><p>Selected materials must be similar to real game pieces in there they are rigid and appropriately sized.</p></li>
<li><p>Simulation should not allow users to move robot or the game board and only the pieces.</p></li>
<li><p>Pieces and game board must be within robot’s workspace.</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US8</td>
<td>As a client, I want the robot system to be easy to troubleshoot so that I can minimise time spent dealing with bugs or program errors.</td>
<td><ol type="1">
<li><p>All program errors or bugs are caught and visible through error log.</p></li>
<li><p>Comprehensive instruction to overcome system crashes</p></li>
</ol></td>
<td><strong>3</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="odd">
<td>US9</td>
<td>As a client, I want the simulation to take up minimum amount of storage so that it can be efficiently stored.</td>
<td><ol type="1">
<li><p>Compact simulation with minimised data structure and refactored logic</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="even">
<td>US10</td>
<td>As a client, I want to be able to access clear guidance through documentation, so I know how to use the system and can easily troubleshoot problems.</td>
<td><ol type="1">
<li><p>Easily understandable language in documentations</p></li>
<li><p>Documentation on problems I might encounter and possible resolution.</p></li>
</ol></td>
<td><strong>3</strong></td>
<td><strong>2</strong></td>
</tr>
<tr class="odd">
<td>US11</td>
<td>As a client, I want there to be a maximum time limit for each game, to maximise the number of games played, and hence profits.</td>
<td><ol type="1">
<li><p>Each move should not take longer than two minutes.</p></li>
<li><p>A single game setting must not take longer than 10 minutes.</p></li>
<li><p>The robot should not take excessive time to make its decision (total robot decision making and movement within 10 seconds)</p></li>
<li><p>Place a clock or timer on the simulation to let players know how much time they have left</p></li>
</ol></td>
<td><strong>1</strong></td>
<td><strong>4</strong></td>
</tr>
</tbody>
</table>

**Test Plan**

<table>
<thead>
<tr class="header">
<th><strong>Test ID</strong></th>
<th><strong>Test Case</strong></th>
<th><strong>Test Strategy (Steps)</strong></th>
<th><strong>Pass/Fail Requirements</strong></th>
<th><strong>Test Duration</strong></th>
<th><strong>Specification Tested</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>T1</td>
<td><strong>Place Piece in Correct Position</strong></td>
<td><ol type="1">
<li><p>Have the arm place 9 O pieces in all 9 places.</p></li>
<li><p>Have the arm place 9 X pieces in all 9 places.</p></li>
</ol></td>
<td><strong>Test passes if pieces are placed inside the places not on lines or overlapping 9/9 times for all pieces</strong></td>
<td><strong>30 minutes</strong></td>
<td><strong>US1-1</strong></td>
</tr>
<tr class="even">
<td>T2</td>
<td><strong>Movement Quality Test</strong></td>
<td><ol type="1">
<li><p>Run simulation 3 times and check the movement to ensure it moves smoothly and minimise lag</p></li>
</ol></td>
<td><strong>The test passes if the simulation can run 3 times without significant reduction in simulation quality</strong></td>
<td><strong>30 minutes</strong></td>
<td><strong>US1-2</strong></td>
</tr>
<tr class="odd">
<td>T3</td>
<td><strong>Identifying Piece Types</strong></td>
<td><ol type="1">
<li><p>Place different pieces on a board 8 time, with 4 tests being done using X pieces, and 4 done using O pieces.</p></li>
<li><p>Determine piece type and inform user of piece type.</p></li>
</ol></td>
<td><strong>Piece correctly determined 8 times out of 8.</strong></td>
<td><strong>15 minutes</strong></td>
<td><strong>US1-3</strong></td>
</tr>
<tr class="even">
<td>T4</td>
<td><strong>AI Difficulty</strong></td>
<td><ol type="1">
<li><p>AGILE methodology for testing functionality</p></li>
<li><p>For testing each difficulty, pieces are placed in various specified positions, and the AI’s decision is judged on its action.</p></li>
<li><p>Have the robot play 10 easy games and 10 hard games.</p></li>
<li><p>Find the winning percentage on each difficulty</p></li>
</ol></td>
<td><p><strong>For the easy difficulty, the robot may place the piece anywhere.</strong></p>
<p><strong>In playtesting, the robot should win less than 50% of the time.</strong></p>
<p><strong>For the hard difficulty, the robot must not place the piece in a square that enforces a win for the user, where possible.</strong></p>
<p><strong>In playtesting, the user should win less than 50% of the games in hard difficulty</strong></p></td>
<td><strong>30 minutes</strong></td>
<td><strong>US2-1</strong></td>
</tr>
<tr class="odd">
<td>T5</td>
<td><strong>User Experience</strong></td>
<td><ol type="1">
<li><p>Have 5 people try the program.</p></li>
<li><p>Have each tester to rate their experience out of 5.</p></li>
<li><p>If the rating is below 4 then get user input.</p></li>
<li><p>Find average rating, if its below 4 then update UX and repeat test.</p></li>
</ol></td>
<td><strong>Test passes if the rating average exceeds 4/5</strong></td>
<td><strong>1 hour</strong></td>
<td><p><strong>US3-1</strong></p>
<p><strong>US3-2</strong></p>
<p><strong>US3-3</strong></p></td>
</tr>
<tr class="even">
<td>T6</td>
<td><strong>User Interface</strong></td>
<td><ol type="1">
<li><p>GUI Test making sure all features (buttons, labels, etc.) are present.</p></li>
<li><p>Test each feature’s functionality manually (for each object on screen including buttons, images, links, etc.)</p></li>
</ol></td>
<td><strong>All features correctly and professionally presented, and reliably perform the correct action.</strong></td>
<td><strong>30 minutes</strong></td>
<td><strong>US3-4</strong></td>
</tr>
</tbody>
</table>

<table>
<thead>
<tr class="header">
<th>T7</th>
<th><p><strong>Catching</strong></p>
<p><strong>Rule Violations</strong></p></th>
<th><ol type="1">
<li><p>Test for using the wrong piece</p>
<ol type="a">
<li><p>Place a new incorrect piece in an empty square</p></li>
<li><p>Place multiple pieces in empty squares, using mixture of pieces</p></li>
</ol></li>
<li><p>Test for incorrect number of pieces placed</p>
<ol type="a">
<li><p>Place two or more new correct pieces in empty squares</p></li>
<li><p>Place 0 pieces on the board</p></li>
</ol></li>
<li><p>Test moving pieces already on the board</p>
<ol type="a">
<li><p>Remove a piece from the game board</p></li>
<li><p>Replace a piece on the game board with the other piece</p></li>
</ol></li>
<li><p>Test overlapping pieces</p>
<ol type="a">
<li><p>Place a piece over another piece</p></li>
<li><p>Place a piece over a grid line</p></li>
</ol></li>
<li><p>Test removing piece from gameplay area</p>
<ol type="a">
<li><p>Remove piece from gameplay area</p></li>
</ol></li>
</ol></th>
<th><strong>For each test, the system must display the appropriate violation and prompt the user to play again.</strong></th>
<th><strong>45 minutes</strong></th>
<th><p><strong>US4-1</strong></p>
<p><strong>US4-2</strong></p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>T8</td>
<td><strong>Understandable Interface</strong></td>
<td><ol type="1">
<li><p>Have 5 potential target customer interact with the game without directions</p></li>
<li><p>Measure time taken for each customer to complete the entire game workflow</p></li>
<li><p>Measure average time</p></li>
</ol></td>
<td><strong>The test passes if the average time is less than 10 minutes</strong></td>
<td><strong>100 minutes</strong></td>
<td><p><strong>US5-1</strong></p>
<p><strong>US5-2</strong></p></td>
</tr>
<tr class="even">
<td>T9</td>
<td><strong>Win or Lose Check</strong></td>
<td><ol type="1">
<li><p>Play 10 games</p></li>
<li><p>Observe the robot's response when someone should win or if there’s a draw</p></li>
</ol>
<ol type="a">
<li><p>Win: Three of the same piece in a row.</p></li>
<li><p>Draw: when no player can win, as soon as that happens, end game does not wait to fill the board</p></li>
</ol>
<ol start="3" type="1">
<li><p>When an outcome is decided, clear the board and reset pieces to starting location</p></li>
</ol></td>
<td><strong>The test passes if 10 out of 10 games the robot correctly responds to player loss, draw, or victory.</strong></td>
<td><strong>50 minutes</strong></td>
<td><strong>US5-3</strong></td>
</tr>
</tbody>
</table>

<table>
<thead>
<tr class="header">
<th>T10</th>
<th><strong>Game Completion</strong></th>
<th><ol type="1">
<li><p>Play a game through. Observe the system response for the following conditions.</p></li>
</ol>
<ul>
<li><p>User wins overall</p></li>
<li><p>AI wins overall</p></li>
<li><p>3 games are reached, and neither party has won overall</p></li>
</ul></th>
<th><strong>For each specified case, the system must correctly display the final winner, or a draw if neither party has won.</strong></th>
<th><strong>30 mins</strong></th>
<th><strong>US5-4</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>T11</td>
<td><strong>Gameplay Piece Quality Test</strong></td>
<td><ol type="1">
<li><p>Consistent shape for same pieces</p></li>
<li><p>Consistent colour for same group of pieces</p></li>
<li><p>Consistent box sizes in the game board</p></li>
</ol></td>
<td><strong>The test passes if the game pieces of the same type have consistent shape, colour, and size. Additionally, the box size in the game board has to be consistent and need to fit any type of game pieces.</strong></td>
<td><strong>30 minutes</strong></td>
<td><strong>US6-1</strong></td>
</tr>
<tr class="even">
<td>T12</td>
<td><strong>Error Troubleshooting</strong></td>
<td><ol type="1">
<li><p>Trigger different errors from the program.</p></li>
</ol>
<ul>
<li><p>Attempt playing a game without the board available.</p></li>
<li><p>Attempt a game without available pieces.</p></li>
<li><p>Put invalid user inputs</p></li>
</ul>
<ol type="1">
<li><p>More cases will be added as development process continues</p></li>
</ol></td>
<td><strong>Test succeeds if the program handles all errors, logs them, and notifies the user with a friendly message that eases troubleshooting process.</strong></td>
<td><strong>30 minutes</strong></td>
<td><strong>US8-1</strong></td>
</tr>
<tr class="odd">
<td>T13</td>
<td><strong>Test System Crashes can be resolved</strong></td>
<td><ol type="1">
<li><p>Trigger errors during multiples games</p></li>
<li><p>Trigger violations during multiple games</p></li>
<li><p>Trigger safety violations during multiple games</p></li>
<li><p>Observe the robot’s response to each violation.</p></li>
</ol>
<ol start="2" type="1">
<li><p>*Details on triggers will be developed throughout the implementation phase</p></li>
</ol></td>
<td><strong>Test fails if any of the trigger breaks the program without a properly handled error code or message. Test also fails if the robot gives no response to a trigger</strong></td>
<td><strong>1 day</strong></td>
<td><strong>US8-2</strong></td>
</tr>
<tr class="even">
<td>T14</td>
<td><strong>Test efficiency of logic, structure, and simulation</strong></td>
<td><ol type="1">
<li><p>Have code review processes to get different perspective on possible improvements.</p></li>
<li><p>The size of the simulation should be of reasonable simulation size.</p></li>
</ol>
<ol start="3" type="1">
<li><p>The processing time should not be too long</p></li>
</ol></td>
<td><strong>Test passes if the simulation size is not too large, lag is minimised and of reasonable processing time</strong></td>
<td><strong>15 minute</strong></td>
<td><strong>US9</strong></td>
</tr>
</tbody>
</table>

<table>
<thead>
<tr class="header">
<th>T15</th>
<th><strong>User Documentation Quality</strong></th>
<th><ol start="4" type="1">
<li><p>Have 5 potential owners read the user documentation.</p></li>
<li><p>Have them attempt to run the simulation.</p></li>
<li><p>Measure the time taken.</p></li>
<li><p>Find an average of the time taken.</p></li>
<li><p>Have different people to rate out of 5, the user friendliness of the documentation.</p></li>
<li><p>Find the average rating score</p></li>
</ol></th>
<th><strong>Test passes if all owners can safely install in under 1 hour and the rating for user friendliness of the documentation exceeds 4</strong></th>
<th><strong>1 day</strong></th>
<th><strong>US10-1</strong></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>T16</td>
<td><strong>Troubleshooting Documentation Quality</strong></td>
<td><ol type="1">
<li><p>During testing and development, always take note of issues found and check for suggested solution on the documented common issues.</p></li>
<li><p>Follow the steps to resolve the encountered problem</p></li>
</ol></td>
<td><strong>The test fails if there is a problem that goes undocumented or if the documentation for the problem is recorded, but the resolution does not resolve the problem</strong></td>
<td><strong>Throughout the project</strong></td>
<td><strong>US10-2</strong></td>
</tr>
<tr class="even">
<td>T17</td>
<td><strong>Length of move</strong></td>
<td><ol type="1">
<li><p>Play a game with the AI</p></li>
<li><p>Take less than 2 minutes to make a move</p></li>
<li><p>Expected outcome: game should proceed as normal</p></li>
<li><p>Let the AI make a move</p></li>
<li><p>Take more than 2 minutes to make a move</p></li>
<li><p>Expected outcome: game should end with a win for the robot, notification of this should show up for the user then move on the next round</p></li>
<li><p>Play the next round</p></li>
<li><p>Pause the AI</p></li>
<li><p>Expected outcome: it takes longer than 2 minutes to make a move, let player win for the round, show a notification of this for the user and move on to the next game</p></li>
</ol></td>
<td><strong>The test fails if any of the expected outcomes are not met.</strong></td>
<td><strong>10 mins</strong></td>
<td><strong>US11-1</strong></td>
</tr>
<tr class="odd">
<td>T18</td>
<td><strong>Length of game</strong></td>
<td><ol type="1">
<li><p>Play 5 games and constantly take 2 minutes before making a move</p></li>
</ol></td>
<td><strong>The test passes if each game takes between 8 to 10 minutes.</strong></td>
<td><strong>1 hour</strong></td>
<td><strong>US11-2</strong></td>
</tr>
<tr class="even">
<td>T19</td>
<td><strong>Decision making time</strong></td>
<td><ol type="1">
<li><p>Normally play 5 games with the robot in “easy” difficulty level then another 5 in “hard” difficulty level</p></li>
<li><p>Measure the time between ending your move in to when the robot finished its move in all 10 games</p></li>
</ol></td>
<td><strong>The test fails if at any time the robot takes longer than 30 seconds to make its decision</strong></td>
<td><strong>2 hours</strong></td>
<td><strong>US11-3</strong></td>
</tr>
<tr class="odd">
<td>T20</td>
<td><strong>Test timer for decision making</strong></td>
<td><ol type="1">
<li><p>Play 3 complete games of 3 sets.</p></li>
<li><p>In the first game play normally, in the second game always take time close to limit to make a move.</p></li>
<li><p>In the third game always take too long to make a move</p></li>
<li><p>Ensure that timer always resets after every game to 10 minutes.</p></li>
<li><p>Ensure timer limits each player move to 2 minutes.</p></li>
<li><p>Ensure warning appears when player has taken too long</p></li>
</ol></td>
<td><strong>Test passes if no warning shows up in normal time, warning shows up when the move is close to time limit and violation is made when it takes too long. While playing in all mode check that after a set is played time resets to 10 minutes.</strong></td>
<td><strong>2 hours</strong></td>
<td><strong>US11-4</strong></td>
</tr>
</tbody>
</table>
