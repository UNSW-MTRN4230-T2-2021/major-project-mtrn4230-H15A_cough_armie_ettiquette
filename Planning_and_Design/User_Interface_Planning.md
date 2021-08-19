# Features:

## Main Window:
### Displays information:
  - Game Difficulty 
  - Robot and Player Win Count (Robot | Player | Draw) 
  - Match number (out of 3)
  - Robot/Player Turn
  - Timer
  - Documentation Info (Help button)
  - New Game Button (should work at any point during a game)
  - Power Off Button (should work at any point during a game) 
  - Virtual Board [Request, Service: UserMoveService] NOTE: Sends piece location in terms of row | col  
  

## Secondary Window: Displays messages and sends messages back.
### Displays message types:
  - Robot Power On [Receive, Topic: MessagesToUser] (int statusNumber = 0)
  - Game Start [Receive, Topic: MessagesToUser] (int statusNumber = 1)
  - Start Robot Turn [Receive, Topic: MessagesToUser] (int statusNumber = 2)
  - Start User Turn [Receive, Topic: MessagesToUser] (int statusNumber = 3)
  - Robot/User Wins or Draw [Receive, Topic: MessagesToUser] (Has a status number)
  - Robot/User Wins Overall or Draw Overall [Receive, Topic: MessagesToUser] (Has a status number)
  - Start New Game Query [direct from UI] (optional)
  - Power Off (should close all windows upon pressing OK button) [Receive, Topic: MessagesToUser OR direct from UI] (int statusNumber = 10)
  
  - Rule Violations [Receive, Topic: RuleViolations] (ruleViolations: )
### Sends message types:
  - Start New Game AND Game Difficulty (Easy/Hard) [Send, Topic: MsgstoController] (Has two possible status numbers)
  - End User Turn [Send, Topic: MsgstoController] (Has a status number)
  - Timer Expired [Send, Topic: MsgstoController] (Has a status number) NOTE: Only sends data if timer expires -> record robot win. If the timer doesn't, the game progresses as normal.
  - Power Off [Send, Topic: MsgstoController] (Has a status number)
  - Violation Resolved [Send, Topic: MsgstoController] (Has a status number) NOTE: Should have a corresponding violation resolution check in Game Controller.
  
## Tertiary Window:
  - Displays documentation (optional: game should pause when viewing the documentation)  
 
 
# Topic Codes
**msgsToUser Topic: (int controllerStatus)**

| **Information**     | **Number** | **Description** |
|---------------------|------------|-----------------|
| No Information      | 0          |                 |
| Position 1          | 1          |                 |
| Position 2          | 2          |                 |
| Position 3          | 3          |                 |
| Position 4          | 4          |                 |
| Position 5          | 5          |                 |
| Position 6          | 6          |                 |
| Position 7          | 7          |                 |
| Position 8          | 8          |                 |
| Position 9          | 9          |                 |
| Robot Power On      | 10         |                 |
| Game Start          | 11         |                 |
| Start User Turn     | 12         |                 |
| Start Robot Turn    | 13         |                 |
| Robot Wins Once     | 14         |                 |
| Player Wins Once    | 15         |                 |
| Draw Happens Once   | 16         |                 |
| Robot Wins Overall  | 17         |                 |
| Player Wins Overall | 18         |                 |
| Draw Overall        | 19         |                 |

**msgstoController Topic: (int uiStatus)**

| **Information**            | **Number** | **Description**                                                                                                         |
|----------------------------|------------|-------------------------------------------------------------------------------------------------------------------------|
| No Information             | 0          |                                                                                                                         |
| Place Piece in Position 1  | 1          | Send to the controller row: 0 and col: 0 after user ends their turn                                                     |
| Place Piece in Position 2  | 2          | Send to the controller row: 0 and col: 1 after user ends their turn                                                     |
| Place Piece in Position 3  | 3          | Send to the controller row: 0 and col: 2 after user ends their turn                                                     |
| Place Piece in Position 4  | 4          | Send to the controller row: 1 and col: 0 after user ends their turn                                                     |
| Place Piece in Position 5  | 5          | Send to the controller row: 1 and col: 1 after user ends their turn                                                     |
| Place Piece in Position 6  | 6          | Send to the controller row: 1 and col: 2 after user ends their turn                                                     |
| Place Piece in Position 7  | 7          | Send to the controller row: 2 and col: 0 after user ends their turn                                                     |
| Place Piece in Position 8  | 8          | Send to the controller row: 2 and col: 1 after user ends their turn                                                     |
| Place Piece in Position 9  | 9          | Send to the controller row: 2 and col: 2 after user ends their turn                                                     |
| Start New Game: Easy       | 10         |                                                                                                                         |
| Start New Game: Hard       | 11         |                                                                                                                         |
| Timer Expired              | 12         | Only sends when timer has expired                                                                                       |
| Pause Game                 | 13         | Used when the player wants to take a break, or is reading the documentation. (optional)                                 |
| Power Off                  | 14         | Can power the robot off mid-game (optional)                                                                             |
| Violation Resolved by User | 15         | Controller should check that all violations actually have been resolved, after receiving this status number. (optional) |

**ruleViolation Topic: (int dataRequest, string message)**

| **Information**                      | **Number** | **Description**                                                                                       |
|--------------------------------------|------------|-------------------------------------------------------------------------------------------------------|
| No Resolution of Violation Necessary | 0          | Controller is only sending information to the UI. No response needed.                                 |
| User Requested to Resolve Violation  | 1          | Controller needs user to resolve violation and then send confirmation of this back to the controller. |
