# SchottenTotten_CPP
Implementation of the Schotten Totten game in the C++ language.<br>
Project created by: <b>Yahya Atouf</b>, <b>Mohamed Hachelef</b>, <b>Ayoub Elhatri</b>.<br>




Sources: <b>English</b>: <br><ul>
<li><i>Schotten Totten</i> (Base version): https://cdn.1j1ju.com/medias/d5/72/2f-schotten-totten-rulebook.pdf</li>
                          <li><i>Schotten Totten 2</i>: https://cdn.1j1ju.com/medias/77/76/71-schotten-totten-2-rulebook.pdf</li></ul>
         <b>French</b>:<br> <ul><li><i>Schotten Totten</i> (Version de base): https://iello.fr/wp-content/uploads/2022/07/schottentotten_regles.pdf</li>
                        <li><i>Schotten Totten 2</i>: https://iello.fr/wp-content/uploads/2020/11/SchottenTotten-2_rulebook_FR_Light.pdf</li></ul>


# SchottenTotten_CPP

Implementation of the strategic card game **Schotten Totten** in modern C++.  
(Repository: `ZTOUF/SchottenTotten_CPP`)

> Replace (or keep) any placeholder sections after validating the actual project structure and code.

---

## Table of Contents
1. Overview
2. Game Rules (Brief)
3. Features
4. Project Structure
5. Design & Architecture
6. Core Concepts
7. Build & Run
8. Usage
9. AI / bot logic (if applicable)
10. Testing
11. Configuration
12. Roadmap / TODO
13. Contributing
14. License
15. Acknowledgements

---

## 1. Overview
Schotten Totten is a two‑player tactical card game about capturing boundary stones by forming stronger formations (sets) than your opponent. This project aims to provide:
- A clean, extensible C++ implementation.
- Separation of core game logic from UI.
- Potential hooks for AI opponents or network play (future extensions).

---

## 2. Game Rules (Brief)
Each player competes over 9 boundary stones.  
On your turn:
1. Play one card to one stone (on your side).
2. (Optionally) Claim a stone if you can prove your formation is stronger.

Typical formations (from strongest to weakest):
1. Straight Flush (Consecutive ranks, same color)
2. Three of a Kind
3. Flush (Same color)
4. Straight (Consecutive ranks)
5. Sum (Highest total value if none above applies)

A stone is won when:
- Both players have placed 3 cards on that stone and one side is higher, OR
- One player can *prove* the opponent cannot surpass their formation.

Victory:
- First to claim 5 stones total, OR
- First to claim 3 adjacent stones.

(Adjust according to the exact variant your implementation supports.)

---

## 3. Features
- Core rule engine (deck, stones, formations, scoring).
- Deterministic resolution of formation strength.
- Turn sequencing & move validation.
- (Planned / Optional) AI opponent.
- (Planned / Optional) CLI or GUI layer.
- Clean abstractions for future expansion (e.g., online play).

Update this section with the actual implemented features.

---

## 4. Project Structure
(Adapt after verifying actual folders.)

```
SchottenTotten_CPP/
├─ src/
│  ├─ core/           # Core game logic (cards, stones, formations)
│  ├─ engine/         # Turn manager, rule arbitration
│  ├─ ai/             # AI strategies (if implemented)
│  ├─ ui/             # CLI/GUI front-end (if any)
│  └─ main.cpp        # Entry point
├─ include/           # Public headers (if using an include/ layout)
├─ tests/             # Unit / integration tests
├─ assets/            # (If any: e.g., card art placeholders)
├─ CMakeLists.txt     # Build configuration (if using CMake)
└─ README.md
```

If the structure differs, update accordingly.

---

## 5. Design & Architecture

### Core Entities
- Card: (rank, suit/color)
- Deck: Shuffled container producing draws
- Stone: Holds up to 3 cards per player + claim status
- Player: Hand, moves, perspective
- GameState: Aggregate of players, stones, draw pile, turn
- FormationEvaluator: Compares formations and tie-breakers

### Principles
- Separation of concerns: logic vs. presentation
- Minimal global state—pass immutable references where possible
- Potential for deterministic seeds (for reproducible games)

### Error Handling
- Prefer exceptions for fatal rule violations (or status codes if performance-critical)
- Validation before mutating state

---

## 6. Core Concepts

| Concept | Responsibility |
|--------|-----------------|
| Move Validator | Ensures a card placement meets rules |
| Claim Evaluator | Determines if a stone can be legally claimed |
| Formation Ranker | Assigns comparable strength tuple |
| Rule Engine | Orchestrates turn flow |

A typical formation strength tuple might be:
```
(primary_category, primary_value, secondary_value, kicker_sum)
```
Adjust per implementation details.

---

## 7. Build & Run

### Prerequisites
- C++17 or later (adjust if using C++20/23 features)
- CMake ≥ 3.16 (if applicable)
- A supported compiler: GCC, Clang, MSVC

### Build (CMake Example)
```
git clone <private-repo-url>
cd SchottenTotten_CPP
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

### Run
```
./build/bin/schotten_totten   (example)
```

If not using CMake, document your actual build commands (e.g., Makefile, Meson, Bazel, etc.).

---

## 8. Usage

### Starting a Game
- Launch the executable.
- (If CLI) Follow prompts to place cards.
- (If GUI) Interact with board/hand.

### Example (CLI Pseudolog)
```
Your hand: [G5][B3][R7][Y2][G9]
Select card to play: G5
Select stone (0-8): 3
Card placed. Opponent thinking...
```

Add real usage samples as implemented.

---

## 9. AI / Bot Logic (If Implemented)
Potential strategies:
- Greedy: Maximize immediate formation strength
- Probabilistic: Evaluate unseen cards likelihood
- Heuristic scoring of stones (threat level, adjacency)

Document actual heuristics once finalized.

---

## 10. Testing

### Suggested / Expected Tests
- Deck integrity & uniqueness
- Formation ranking edge cases
- Tie-break correctness
- Claim proofs (including “impossible to beat” logic)
- Victory conditions (5 total vs. 3 adjacent)
- Deterministic seed reproducibility

### Example (CTest / GoogleTest)
```
ctest --output-on-failure
```

Add badges or coverage tools (gcov/llvm-cov) if integrated.

---

## 11. Configuration
Environment variables / config file (if any):
- `ST_SEED` : deterministic RNG seed
- `ST_LOG_LEVEL` : verbose / debug / quiet

If not present, remove or update.

---

## 12. Roadmap / TODO
- [ ] Finalize formation evaluator optimization
- [ ] Add full AI opponent
- [ ] Implement GUI (SDL2 / ImGui / Qt?)
- [ ] Add serialization (save/resume game)
- [ ] Add network multiplayer (WebSockets / TCP)
- [ ] Performance profiling & cache-friendly layout
- [ ] Internationalization (messages, logs)

Update according to actual priorities.

---

## 13. Contributing
1. Fork & branch: `feature/<short-description>`
2. Format code (e.g., clang-format)
3. Add / update tests
4. Submit pull request with description of changes

Coding style suggestions:
- Use `#pragma once` in headers.
- Avoid raw new/delete; prefer smart pointers or value types.
- Keep functions short and intention-revealing.

---

## 14. License
No license specified yet.  
Add a `LICENSE` file (MIT / Apache-2.0 / GPL / etc.) so others know permitted usage.

---

## 15. Acknowledgements
- Original game design by Reiner Knizia (credit required for public distribution of implementations referencing his work).
- Inspiration from community rule clarifications.
- Any libraries or assets used (list here once integrated).

---

## Appendix: Formation Ranking Example
Given three cards, compute:
1. Category (enum)
2. Highest rank ordering
3. Auxiliary sums
4. Tiebreak chain

Example tuple ordering (descending compare):
```
(category, primaryRank, secondaryRank, tertiaryRank, sum)
```

---

## Appendix: Claim Proof Logic (Sketch)
To prove opponent cannot surpass:
1. Enumerate remaining unseen cards.
2. Check if any combination could reach a strictly higher category OR equal category with higher tie-break.
3. If none possible -> claim allowed early.

Optimizations:
- Prune by max theoretical category first.
- Cache remaining card multiset.

---

## Badges (Add After Integrations)
(Examples)
- Build: ![Build](https://img.shields.io/badge/build-passing-brightgreen)
- Coverage: ![Coverage](https://img.shields.io/badge/coverage-XX%25-blue)
- C++ Standard: ![C++17](https://img.shields.io/badge/C%2B%2B-17-orange)

---

Feel free to refine sections once the repository contents are fully established.
