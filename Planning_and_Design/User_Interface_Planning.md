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
| Robot Power On      | 1          |                 |
| Game Start          | 2          |                 |
| Start Robot Turn    | 3          |                 |
| Start User Turn     | 4          |                 |
| Robot Wins Once     | 10         |                 |
| Player Wins Once    | 11         |                 |
| Draw Happens Once   | 12         |                 |
| Robot Wins Overall  | 20         |                 |
| Player Wins Overall | 21         |                 |
| Draw Overall        | 22         |                 |

**msgstoController Topic: (int uiStatus)**

| **Information**            | **Number** | **Description**                                                                                                         |
|----------------------------|------------|-------------------------------------------------------------------------------------------------------------------------|
| No Information             | 0          |                                                                                                                         |
| Start New Game: Easy       | 1          |                                                                                                                         |
| Start New Game: Hard       | 2          |                                                                                                                         |
| End User Turn              | 3          | Lets the controller know that the robot can now take its turn                                                           |
| Timer Expired              | 4          | Only sends when timer has expired                                                                                       |
| Pause Game                 | 5          | Used when the player wants to take a break, or is reading the documentation. (optional)                                 |
| Power Off                  | 6          | Can power the robot off mid-game (optional)                                                                             |
| Violation Resolved by User | 7          | Controller should check that all violations actually have been resolved, after receiving this status number. (optional) |

**ruleViolation Topic: (int dataRequest, string message)**

| **Information**                      | **Number** | **Description**                                                                                       |
|--------------------------------------|------------|-------------------------------------------------------------------------------------------------------|
| No Resolution of Violation Necessary | 0          | Controller is only sending information to the UI. No response needed.                                 |
| User Requested to Resolve Violation  | 1          | Controller needs user to resolve violation and then send confirmation of this back to the controller. |
