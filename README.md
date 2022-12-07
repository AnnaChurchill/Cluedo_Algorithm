# Cluedo_Algorithm

This is a program designed to help a player in Cluedo. By following the prompts during the game, the player will be able to record more information than they would on paper.

Current goal:
The current goal is to have the program record information about the cards of other players. It records all accusations that contain new information that we may not know. It does this by creating new rules with accustions, for instance if player 1 was asked if the had Peacock with the Rope in the Ballroom, the program creates a rule combining all those things. The after each turn the rule is evaluated in the following way:
if we know that player 1 does not own two our of the three things, we can assign the third thing to player 1.
Thus, the program will allow the player to record extra information that would be difficult on pen and paper.

Note:
This program currently only takes into account things that we can know for sure, rather than things that are probably true. Thus information about who asks what etc. is not recorded. This information you could make assumptions about (such as the player will probably not have all the cards they ask) but we can not know that for sure. However, things such as this may be able to be taken into account in future updates of the program.



Future Goals:
- Advising the player which card to show when facing an accusation.
- Advising the player what accusation may be the most helpful, both in finding new information and in hiding ones own cards.


This algorithm hopes to compete with another algorithm by Anja Drayton written in python. I have written this in C as a challenge to myself and in hope to improve my C.

