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
**Results of the test are provided in the same folder.**

