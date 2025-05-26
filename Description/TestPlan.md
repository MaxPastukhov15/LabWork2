# Detailed Test Plan
## Unit Testing:
- Classes and Methods: Test each class and its methods individually to ensure they function correctly.
- Coverage: Include tests for inventory management, combat calculations, quest progression, and environment interactions.
Here's a concise breakdown of what `test.cpp` verifies, grouped by class:

### 1. **Menu System (MenuTest)**
- **Tests Quest Workflow**:
  - Starting quests (`start_quest()`)
  - Updating quest progress (`update_quest_progress()`)
  - Completing quests (`complete_quest()`)
- **Validates**:
  - Progress tracking (0% → 100%)
  - Completion state transitions
  - Output messages for quest events

### 2. **Player Character (CharactersTest)**
- **Tests Core Mechanics**:
  - Health restoration (`restore_hp()` after damage)
  - Stamina consumption (`attack()` reduces stamina)
- **Validates**:
  - Health bounds (0-100)
  - Stamina depletion (attacks reduce stamina below 50)

### 3. **Game Objects (ThingTest)**
- **Tests Interactions**:
  - **Bed**: Full health restoration (`restore()`)
  - **Chest**: Item storage/retrieval (`put_item()`, `retrieve_item()`)
- **Validates**:
  - Item persistence in containers
  - Correct healing mechanics

### 4. **Locations (LocationTest)**
- **Tests Navigation**:
  - Entering locations (`enter_location()` prints description)
  - Moving between connected locations (`move_to_neighbor()`)
- **Validates**:
  - Location description output
  - Neighbor linkage correctness

### 5. **House System (HouseTest)**
- **Tests Features**:
  - Chest management (`getChest()`)
  - Object interaction (`interactWithThing()`)
- **Validates**:
  - Object storage in houses
  - Interaction output messages

### 6. **Game Core (GameTest)**
- **Tests Main Loop**:
  - Game initialization (`start_game()` prints starting area)
  - Turn progression (`advance_turn()`)
  - Location navigation (`move_to_neighbor()`)
- **Validates**:
  - Basic game flow
  - Output consistency
This breakdown shows the test file focuses on **core systems** (quests, stats, items, navigation) with **isolated class tests**. Each test group verifies basic functionality through method calls and output checks.
## **Results of the test**

### Test output 1:

[==========] Running 14 tests from 6 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from MenuTest
[ RUN      ] MenuTest.StartQuestTest
Quest not found or already completed!
Quest not found or already completed!
Quest not found or already completed!
[       OK ] MenuTest.StartQuestTest (0 ms)
[ RUN      ] MenuTest.CompleteQuestTest
Quest not found or already completed!
Quest not found or already completed!
Quest not found or already completed!
Quest not found!
Quest not found or not completed!
test.cpp:86: Failure
Expected equality of these values:
  quest1->check_completion()
    Which is: false
  true
[  FAILED  ] MenuTest.CompleteQuestTest (0 ms)
[ RUN      ] MenuTest.UpdateQuestProgressTest
Quest not found or already completed!
Quest not found or already completed!
Quest not found or already completed!
Quest not found!
test.cpp:95: Failure
Expected equality of these values:
  quest1->get_progress()
    Which is: 0
  40
Quest not found!
test.cpp:98: Failure
Expected equality of these values:
  quest1->get_progress()
    Which is: 0
  100
test.cpp:99: Failure
Expected equality of these values:
  quest1->check_completion()
    Which is: false
  true
[  FAILED  ] MenuTest.UpdateQuestProgressTest (0 ms)
[----------] 3 tests from MenuTest (0 ms total)

[----------] 2 tests from CharactersTest
[ RUN      ] CharactersTest.PlayerHealthRestoration
HP restored to 100
[       OK ] CharactersTest.PlayerHealthRestoration (0 ms)
[ RUN      ] CharactersTest.PlayerStaminaManagement
[       OK ] CharactersTest.PlayerStaminaManagement (0 ms)
[----------] 2 tests from CharactersTest (0 ms total)

[----------] 2 tests from ThingTest
[ RUN      ] ThingTest.BedInteraction
HP restored to 100
Stamina restored to 50
You feel refreshed after sleeping.
[       OK ] ThingTest.BedInteraction (0 ms)
[ RUN      ] ThingTest.ChestItemManagement
Added Health Potion to the chest.
Retrieved Health Potion from the chest.
[       OK ] ThingTest.ChestItemManagement (0 ms)
[----------] 2 tests from ThingTest (0 ms total)

[----------] 2 tests from LocationTest
[ RUN      ] LocationTest.EnterLocationTest
[       OK ] LocationTest.EnterLocationTest (0 ms)
[ RUN      ] LocationTest.MoveToNeighborTest
[       OK ] LocationTest.MoveToNeighborTest (0 ms)
[----------] 2 tests from LocationTest (0 ms total)

[----------] 2 tests from HouseTest
[ RUN      ] HouseTest.ChestManagementTest
[       OK ] HouseTest.ChestManagementTest (0 ms)
[ RUN      ] HouseTest.InteractWithThingTest
test.cpp:237: Failure
Expected: (output.find("Treasure Chest")) != (std::string::npos), actual: 18446744073709551615 vs 18446744073709551615
[  FAILED  ] HouseTest.InteractWithThingTest (0 ms)
[----------] 2 tests from HouseTest (0 ms total)

[----------] 3 tests from GameTest
[ RUN      ] GameTest.StartGameTest
[       OK ] GameTest.StartGameTest (0 ms)
[ RUN      ] GameTest.AdvanceTurnTest
[       OK ] GameTest.AdvanceTurnTest (0 ms)
[ RUN      ] GameTest.MoveToNeighborTest
[       OK ] GameTest.MoveToNeighborTest (0 ms)
[----------] 3 tests from GameTest (0 ms total)

[----------] Global test environment tear-down
[==========] 14 tests from 6 test suites ran. (1 ms total)
[  PASSED  ] 11 tests.
[  FAILED  ] 3 tests, listed below:
[  FAILED  ] MenuTest.CompleteQuestTest
[  FAILED  ] MenuTest.UpdateQuestProgressTest
[  FAILED  ] HouseTest.InteractWithThingTest

 3 FAILED TESTS

### Test output 2:

[==========] Running 14 tests from 6 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from MenuTest
[ RUN      ] MenuTest.StartQuestTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
[       OK ] MenuTest.StartQuestTest (1 ms)
[ RUN      ] MenuTest.CompleteQuestTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
Quest progress updated: 50
Quest not found or not completed!
test.cpp:84: Failure
Expected equality of these values:
  quest1->check_completion()
    Which is: false
  true
[  FAILED  ] MenuTest.CompleteQuestTest (0 ms)
[ RUN      ] MenuTest.UpdateQuestProgressTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
Quest progress updated: 40
test.cpp:90: Failure
Expected equality of these values:
  quest1->get_progress()
    Which is: 0
  40
Quest progress updated: 100
Quest completed: Quest One
Rewards obtained: Gold
test.cpp:93: Failure
Expected equality of these values:
  quest1->get_progress()
    Which is: 0
  100
test.cpp:94: Failure
Expected equality of these values:
  quest1->check_completion()
    Which is: false
  true
[  FAILED  ] MenuTest.UpdateQuestProgressTest (0 ms)
[----------] 3 tests from MenuTest (1 ms total)

[----------] 2 tests from CharactersTest
[ RUN      ] CharactersTest.PlayerHealthRestoration
HP restored to 100
[       OK ] CharactersTest.PlayerHealthRestoration (0 ms)
[ RUN      ] CharactersTest.PlayerStaminaManagement
[       OK ] CharactersTest.PlayerStaminaManagement (0 ms)
[----------] 2 tests from CharactersTest (0 ms total)

[----------] 2 tests from ThingTest
[ RUN      ] ThingTest.BedInteraction
HP restored to 100
Stamina restored to 50
You feel refreshed after sleeping.
[       OK ] ThingTest.BedInteraction (0 ms)
[ RUN      ] ThingTest.ChestItemManagement
Added Health Potion to the chest.
Retrieved Health Potion from the chest.
[       OK ] ThingTest.ChestItemManagement (0 ms)
[----------] 2 tests from ThingTest (0 ms total)

[----------] 2 tests from LocationTest
[ RUN      ] LocationTest.EnterLocationTest
[       OK ] LocationTest.EnterLocationTest (0 ms)
[ RUN      ] LocationTest.MoveToNeighborTest
[       OK ] LocationTest.MoveToNeighborTest (0 ms)
[----------] 2 tests from LocationTest (0 ms total)

[----------] 2 tests from HouseTest
[ RUN      ] HouseTest.ChestManagementTest
[       OK ] HouseTest.ChestManagementTest (0 ms)
[ RUN      ] HouseTest.InteractWithThingTest
[       OK ] HouseTest.InteractWithThingTest (0 ms)
[----------] 2 tests from HouseTest (0 ms total)

[----------] 3 tests from GameTest
[ RUN      ] GameTest.StartGameTest
[       OK ] GameTest.StartGameTest (0 ms)
[ RUN      ] GameTest.AdvanceTurnTest
[       OK ] GameTest.AdvanceTurnTest (0 ms)
[ RUN      ] GameTest.MoveToNeighborTest
[       OK ] GameTest.MoveToNeighborTest (0 ms)
[----------] 3 tests from GameTest (0 ms total)

[----------] Global test environment tear-down
[==========] 14 tests from 6 test suites ran. (2 ms total)
[  PASSED  ] 12 tests.
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] MenuTest.CompleteQuestTest
[  FAILED  ] MenuTest.UpdateQuestProgressTest

 2 FAILED TESTS

### Test output 3:

[==========] Running 14 tests from 6 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from MenuTest
[ RUN      ] MenuTest.StartQuestTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
[       OK ] MenuTest.StartQuestTest (0 ms)
[ RUN      ] MenuTest.CompleteQuestTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
Quest progress updated: 50
Quest completed: Quest One
Rewards obtained: Gold
Quest progress updated: 100
Quest completed: Quest One
Rewards obtained: Gold
Quest completed: Quest One
[       OK ] MenuTest.CompleteQuestTest (0 ms)
[ RUN      ] MenuTest.UpdateQuestProgressTest
Quest started: Quest One
Started quest: Quest One
Quest started: Quest Two
Started quest: Quest Two
Quest started: Quest One
Started quest: Quest One
Quest progress updated: 40
Quest completed: Quest One
Rewards obtained: Gold
Quest progress updated: 100
[       OK ] MenuTest.UpdateQuestProgressTest (0 ms)
[----------] 3 tests from MenuTest (0 ms total)

[----------] 2 tests from CharactersTest
[ RUN      ] CharactersTest.PlayerHealthRestoration
HP restored to 100
[       OK ] CharactersTest.PlayerHealthRestoration (0 ms)
[ RUN      ] CharactersTest.PlayerStaminaManagement
[       OK ] CharactersTest.PlayerStaminaManagement (0 ms)
[----------] 2 tests from CharactersTest (0 ms total)

[----------] 2 tests from ThingTest
[ RUN      ] ThingTest.BedInteraction
HP restored to 100
Stamina restored to 50
You feel refreshed after sleeping.
[       OK ] ThingTest.BedInteraction (0 ms)
[ RUN      ] ThingTest.ChestItemManagement
Added Health Potion to the chest.
Retrieved Health Potion from the chest.
[       OK ] ThingTest.ChestItemManagement (0 ms)
[----------] 2 tests from ThingTest (0 ms total)

[----------] 2 tests from LocationTest
[ RUN      ] LocationTest.EnterLocationTest
[       OK ] LocationTest.EnterLocationTest (0 ms)
[ RUN      ] LocationTest.MoveToNeighborTest
[       OK ] LocationTest.MoveToNeighborTest (0 ms)
[----------] 2 tests from LocationTest (0 ms total)

[----------] 2 tests from HouseTest
[ RUN      ] HouseTest.ChestManagementTest
[       OK ] HouseTest.ChestManagementTest (0 ms)
[ RUN      ] HouseTest.InteractWithThingTest
[       OK ] HouseTest.InteractWithThingTest (0 ms)
[----------] 2 tests from HouseTest (0 ms total)

[----------] 3 tests from GameTest
[ RUN      ] GameTest.StartGameTest
[       OK ] GameTest.StartGameTest (0 ms)
[ RUN      ] GameTest.AdvanceTurnTest
[       OK ] GameTest.AdvanceTurnTest (0 ms)
[ RUN      ] GameTest.MoveToNeighborTest
[       OK ] GameTest.MoveToNeighborTest (0 ms)
[----------] 3 tests from GameTest (0 ms total)

[----------] Global test environment tear-down
[==========] 14 tests from 6 test suites ran. (0 ms total)
[  PASSED  ] 14 tests.


