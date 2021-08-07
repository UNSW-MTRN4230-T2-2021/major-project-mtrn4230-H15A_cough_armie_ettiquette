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
  - Robot Power On [Receive, Topic: MessagesToUser] (Has a status number)
  - Game Start [Receive, Topic: MessagesToUser] (Has a status number)
  - Rule Violations [Receive, Topic: RuleViolations] (Has a range of statuses. Give this a separate topic)
  - End Robot Turn [Receive, Topic: MessagesToUser] (Has a status number)
  - Start User Turn [Receive, Topic: MessagesToUser] (Has a status number)
  - Robot/User Wins or Draw [Receive, Topic: MessagesToUser] (Has a status number)
  - Robot/User Wins Overall or Draw Overall [Receive, Topic: MessagesToUser] (Has a status number)
  - Start New Game Query [direct from UI]
  - Power Off (should close all windows upon pressing OK button) [Receive, Topic: MessagesToUser OR direct from UI] (Has a status number)
  
### Sends message types:
  - Start New Game AND Game Difficulty (Easy/Hard) [Send, Topic: MsgstoController] (Has two possible status numbers)
  - End User Turn [Send, Topic: MsgstoController] (Has a status number)
  - Timer Expired [Send, Topic: MsgstoController] (Has a status number) NOTE: Only sends data if timer expires -> record robot win. If the timer doesn't, the game progresses as normal.
  - Power Off [Send, Topic: MsgstoController] (Has a status number)
  - Violation Resolved [Send, Topic: MsgstoController] (Has a status number) NOTE: Should have a corresponding violation resolution check in Game Controller.
  
## Tertiary Window:
  - Displays documentation (note: game should pause when viewing the documentation)  
  
## To Resolve:
- What areas are Jo and Daniel working on that we need to synchronise with? **Daniel: Computer Vision - seeing the pieces and determining what they are. Rule Violation Check is optional.**
  
