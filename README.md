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

## Reflection (Mandatory)

**1. Apa struktur invariant dari game Anda?**

Struktur invariant dari game kartu mistis saya direpresentasikan oleh kelas `GameSession` dan urutan fasenya yang sangat ketat serta tidak dapat diubah: Fase *Draw*, Fase Aksi, Fase Perhitungan Skor, Fase Resolusi, Fase Hadiah, Fase Toko, dan *Update* Status. *Core loop* ini bertindak sebagai kerangka permanen dari permainan. Struktur ini menjamin bahwa tidak peduli kartu apa yang dipegang pemain atau efek magis apa yang sedang aktif, alur kejadian dasarnya tetap konsisten secara universal. `GameSession` secara ketat mendikte *kapan* sesuatu terjadi, tetapi tidak pernah memedulikan *bagaimana* detail spesifiknya dihitung.

**2. Bagian mana yang bersifat mutable (dapat diubah)?**

Elemen-elemen yang *mutable* adalah mekanik permainan spesifik dan aturan numerik yang "dicolokkan" ke dalam *core loop* yang invariant tersebut. Contohnya termasuk mekanik penarikan kartu dari *deck*, rumus matematika yang digunakan untuk menghitung *Base Power* (yang nilainya berfluktuasi berdasarkan *Aura* yang aktif), dan logika yang menentukan isi inventaris toko. Secara arsitektur, elemen-elemen ini dirancang sebagai kelas-kelas konkret yang mengimplementasikan antarmuka atau *interface* tertentu (seperti `IScoringEngine` atau `IDeckSystem`). Bagian ini dapat terus dimodifikasi, diseimbangkan ulang (*rebalanced*), atau diganti sepenuhnya selama proses pengembangan tanpa pernah perlu mengubah kelas `GameSession`.

**3. Jika Anda ingin menambahkan fitur baru, kelas mana yang akan berubah?**

Jika saya ingin menambahkan fitur baru—misalnya, mekanik "Relic Terkutuk" yang memotong setengah skor pemain pada kondisi tertentu—saya sama sekali tidak akan memodifikasi `GameSession` yang invariant. Sebaliknya, saya akan membuat kelas *mutable* yang benar-benar baru (misalnya, `CursedScoringEngine`) yang mengimplementasikan antarmuka *scoring* yang sudah ada. Saya akan menulis perilaku atau logika baru tersebut sepenuhnya di dalam kelas baru ini, dan kemudian menyuntikkannya ke dalam `GameSession` melalui *Dependency Injection* di file `main.cpp`. Dengan cara ini, *core loop* tetap utuh dan aman dari *error*.

**4. Jika Anda mengubah urutan loop, apa yang akan rusak?**

Mengubah urutan *loop* akan langsung merusak kausalitas logis (sebab-akibat) dari sistem permainan, yang berujung pada kegagalan mekanik yang fatal. Sebagai contoh, jika Fase Perhitungan Skor dieksekusi sebelum Fase Aksi, sistem akan mencoba menghitung skor dari pilihan kartu yang masih kosong, sehingga selalu menghasilkan nol poin. Demikian pula, jika Fase Toko dieksekusi sebelum Fase Hadiah, pemain akan dipaksa untuk membeli barang sebelum mereka menerima koin yang berhak mereka dapatkan dari ronde tersebut. Hal ini akan benar-benar menghancurkan sistem ekonomi dan *progression loop* dari permainan.
