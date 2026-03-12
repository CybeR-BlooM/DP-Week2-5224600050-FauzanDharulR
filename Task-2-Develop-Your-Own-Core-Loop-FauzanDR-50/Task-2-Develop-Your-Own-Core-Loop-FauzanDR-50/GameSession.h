#pragma once
#include <iostream>

class GameSession {
private:
    bool isGameOver;
    int currentRound;

    // Deklarasi fase-fase permainan sebagai method terpisah
    void drawPhase() {
        std::cout << "[1. Draw Phase] System draws mystical cards to player's hand.\n";
    }

    void actionPhase() {
        std::cout << "[2. Action Phase] Player selects cards to play (PlayHand).\n";
    }

    void scoringPhase() {
        std::cout << "[3. Scoring Phase] System calculates Base Power and applies Relic/Aura effects.\n";
    }

    void resolutionPhase() {
        std::cout << "[4. Resolution Phase] System compares Total Power with Target Score.\n";
    }

    void rewardPhase() {
        std::cout << "[5. Reward Phase] System grants coins based on performance.\n";
    }

    void shopPhase() {
        std::cout << "[6. Shop Phase] Player visits the shop to buy Relics, Runes, or Auras.\n";
    }

    void updateStatePhase() {
        std::cout << "[7. Update State] Checking win/lose conditions and advancing round...\n";
        currentRound++;

        // Contoh kondisi berhenti sederhana agar loop tidak infinite
        if (currentRound > 3) {
            isGameOver = true;
            std::cout << ">>> Game Over Condition Met! <<<\n";
        }
    }

public:
    // Constructor
    GameSession() {
        isGameOver = false;
        currentRound = 1;
    }

    // Fungsi utama yang menjalankan Core Loop
    void startGame() {
        std::cout << "=== MYSTICAL CARD GAME STARTED ===\n\n";

        while (!isGameOver) {
            std::cout << "--- ROUND " << currentRound << " ---\n";
            drawPhase();
            actionPhase();
            scoringPhase();
            resolutionPhase();
            rewardPhase();
            shopPhase();
            updateStatePhase();
            std::cout << "\n";
        }

        std::cout << "=== GAME SESSION ENDED ===\n";
    }
};