# Cluedo_Algorithm

This is a program designed to help a player in Cluedo to retaining information more efficiently than they normally would be able to. By following the prompts during the game, the player will be able to record more information than they would on paper. This is a project I am working on purely for my own enjoyment and practise - but it has the potential to expand my skills in future advancements of the program.

Current goal:
The current goal is to have the program record information about the cards of other players. It records all accusations that contain new information that we may not know. It does this by creating new rules with accusations, for instance if player 1 was asked if they had Peacock with the Rope in the Ballroom, the program creates a rule combining all those things. The after each turn the rule is evaluated in the following way:
If we know that player 1 does not own two out of the three things, we can assign the third thing to player 1.
Thus, the program will allow the player to record extra information that would be difficult on pen and paper.

Note:
This program currently only takes into account things that we can know for sure, rather than things that are probably true. Thus information about who asks what etc. is not recorded. This information you could make assumptions about (such as the player will probably not have all the cards they ask) but we can not know that for sure. However, things such as this may be able to be taken into account in future updates of the program.

Status: 
The program is currently appearing to be calculating what it is supposed to and delivering that to the user. However, to determine that the program is doing what it is supposed to, it needs to undergo testing. This will be my next step - writing test cases to prove the accuracy (and find any inaccuracies) of the program. There are also some possible inputs a player may type which may lead to the program not functioning as desired - these will be ironed out with testing as well.
After this I would like to try out my algorithm in games to get a feel for whether the extra information it can store is meaningfully advantageous in the game. Currently, I am still brainstorming ideas to properly test this without having to play hundreds of games of Cluedo.
After I am content that the program is working as it should, I am keen to begin working on future advancements and improvements to the user experience.



Possible Future Advancements:
- Advising the player which card to show when facing an accusation (keeping track of what other players know of your hand and thus giving them the least information possible)
  This goal would be relatively simple to implement compared to the other ones.
- Advising the player which rooms on the board would be most helpful to move to (taking into consideration the difficulty of moving there)
- Advising the player what accusation may be the most helpful, both in finding new information and in hiding one’s own cards.

Possible Improvements to User Experience:
- Decreasing the amount of input the user needs to provide to cut down on the time that using this algorithm takes adds to game time. (The amount of time it currently takes is so far untested, however cutting down on this without losing any abilities will always be positive for the user experience.)
- Creating a website interface instead of using the terminal would be a great improvement from a user’s perspective - making the user experience much more enjoyable. This can also help the previous point in allowing the user to communicate with their mouse as well as their keyboard, thus allowing the amount of typing by the user to be reduced.

I have chosen to write this in C in hope to improve my abilities in this language.

