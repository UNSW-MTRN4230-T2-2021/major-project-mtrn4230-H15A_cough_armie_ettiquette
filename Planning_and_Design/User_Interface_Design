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
  

## Secondary Window: Displays messages and sends messages back.
### Displays message types:
  - Robot Power On [Receive, Topic: MessagesToUser]
  - Game Start [Receive, Topic: MessagesToUser]
  - Rule Violations [Receive, Topic: MessagesToUser]
  - End Robot Turn [Receive, Topic: MessagesToUser]
  - Start User Turn [Receive, Topic: MessagesToUser]
  - Robot/User Wins or Draw [Receive, Topic: MessagesToUser]
  - Robot/User Wins Overall or Draw Overall [Receive, Topic: MessagesToUser]
  - Start New Game Query
  - Power Off (should close all windows upon pressing OK button) [Topic: MessagesToUser]
  
### Sends message types:
  - Game difficulty (easy/hard) [Send, Topic: MessagesToUser]
  - End User Turn [Send, Topic: MessagesToUser]
  - Timer Expired (Yes/No) [Send, Topic: MessagesToUser]
  - Start New Game [Send, Topic: MessagesToUser]
  - Power Off [Send, Topic: MessagesToUser]
  - Violation Resolved (should lead to a violation resolution check) [Send, Topic: MessagesToUser]
  
## Tertiary Window:
  - Displays documentation (note: game should pause when viewing the documentation)  
  
## To Resolve:
- Will the UI take in the player's actual move, or just the confirmation that the player has ended their turn? If the latter, then the game controller needs to request a user move.
- Shouldn't the game controller be making the image requests to determine the board state? Otherwise how will it know when 
- 
  
  
