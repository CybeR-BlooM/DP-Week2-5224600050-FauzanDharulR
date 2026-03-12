Write the Core Loop

In our mystical card game, the player acts as a spellcaster trying to reach a specific power score each round. Here is the strict core loop:

1. Draw Phase: System draws 5 random mystical cards from the Deck to the Player's Hand.

2. Action Phase: Player selects a valid combination of cards to play (the "PlayHand").

3. Scoring Phase: System evaluates the cards, calculates the Base Power (Chips x Multiplier), and applies any active Relic or Aura effects.

4. Resolution Phase: System compares the Total Power against the Round's Target Score.

5. Reward Phase: System grants Coins based on the power generated.

6. Shop Phase: Player uses Coins to buy new Relics, Runes, or Auras.

7. State Update: System updates the game state (Advances to the next round if the target is met, or triggers Game Over if it fails).

8. Repeat

Identify the Invariants
- Which steps in your loop must NEVER change order?
  The sequence of Draw $\rightarrow$ Action $\rightarrow$ Scoring $\rightarrow$ Reward $\rightarrow$ Shop $\rightarrow$ State Update must never change.
- Which components must always exist for the game to function?
  The GameSession (loop manager), DeckSystem (card provider), ScoringEngine, and GameStateManager.
- What would break if the order changes?
  If the sequence is broken, the game's logic collapses. For example, if the Scoring Phase happens before the Action Phase, the system would calculate a score of zero. If the Shop Phase happens before the Reward Phase, the player would never have the newly earned coins available to make purchases.

Identify Mutable Elements
These elements can be freely changed without breaking the core loop:
1. Scoring Formulas (Aura Effects): The math used to calculate Base Power or Multipliers can change dynamically based on the Auras equipped.
2. Hand Size / Draw Limit: The number of cards drawn per turn can be increased or decreased by certain Relics.
3. Shop Prices and Inventory: The cost of items and the probability of rare Relics appearing in the shop can be adjusted for balancing.
4. Target Score Scaling: The math determining how much the Target Score increases each round (Level difficulty).
