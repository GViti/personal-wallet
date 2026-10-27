# Personal Wallet — Development Roadmap

## Project vision

Build a command-line personal finance application in C that allows users to manage multiple wallets, record transactions, track balances, and calculate their total net worth.

The project is designed to demonstrate progressive mastery of C programming and foundational software engineering concepts.

The application should evolve from a basic terminal program into a modular, tested, persistent system.

## Milestone 0 — Application fundamentals

**Status: In progress**

### Features

- [x] Application entry point.
- [x] Main menu.
- [x] Login and registration menu options.
- [x] Basic menu navigation.
- [x] Functions for login and registration.
- [x] Basic username/password comparison.
- [ ] Validate menu input.
- [ ] Handle unexpected input and EOF.
- [ ] Handle excessively long strings.
- [ ] Support returning to the main menu.
- [ ] Handle login success and failure consistently.

### Learning objectives

- Variables and data types.
- Conditional statements.
- Loops.
- Functions and return values.
- Scope.
- Character arrays and strings.
- Standard input and output.
- Compiler warnings.
- Basic debugging.

### Completion criteria

The application handles invalid input without crashing, hanging, or entering an unintended infinite loop.

Users can navigate between the implemented screens and exit cleanly.

---

## Milestone 1 — Application navigation

**Status: Planned**

### Features

- [ ] Wallet dashboard.
- [ ] Login-to-dashboard transition.
- [ ] Logout.
- [ ] Return to previous menu.
- [ ] Consistent navigation behavior.
- [ ] Replace numeric menu states with an enum.

### Learning objectives

- Enumerations.
- State machines.
- Separation of responsibilities.
- Control flow.
- Function interfaces.

### Completion criteria

A successful login opens the dashboard.

Users can navigate between screens, log out, and exit without terminating the application unexpectedly.

---

## Milestone 2 — Wallet data structures

**Status: Planned**

### Features

- [ ] Define `struct Wallet`.
- [ ] Store wallet names and balances.
- [ ] Support multiple wallet types.
- [ ] Store wallets in a fixed-size array.
- [ ] Track the number of active wallets.
- [ ] Add a wallet.
- [ ] List wallets.
- [ ] Remove a wallet.
- [ ] Calculate total net worth.

### Learning objectives

- Structures.
- Arrays of structures.
- Function parameters.
- Passing structures to functions.
- Data validation.
- Basic algorithms.
- Separation of data and behavior.

### Completion criteria

Users can create, view, and remove wallets.

The application calculates total net worth correctly.

---

## Milestone 3 — Transaction management

**Status: Planned**

### Features

- [ ] Define `struct Transaction`.
- [ ] Record income.
- [ ] Record expenses.
- [ ] Transfer funds between wallets.
- [ ] Display transaction history.
- [ ] Validate transaction amounts.
- [ ] Prevent invalid wallet references.
- [ ] Define and document the policy for negative balances.

### Learning objectives

- Relationships between structures.
- Searching arrays.
- Updating data consistently.
- Data invariants.
- Error handling.
- Algorithm design.

### Completion criteria

Transactions correctly update wallet balances.

Invalid operations are rejected without corrupting application state.

---

## Milestone 4 — File persistence

**Status: Planned**

### Features

- [ ] Save wallets to disk.
- [ ] Load wallets at startup.
- [ ] Save transactions.
- [ ] Load transaction history.
- [ ] Handle missing files.
- [ ] Handle malformed files.
- [ ] Detect file I/O errors.
- [ ] Document the storage format.

### Learning objectives

- File pointers.
- `fopen`, `fclose`, `fgets`, and `fprintf`.
- Serialization and deserialization.
- Error checking.
- Resource management.
- Data integrity.

### Completion criteria

Users can close and reopen the application without losing valid saved data.

The application handles missing or corrupted files predictably.

---

## Milestone 5 — Modular architecture

**Status: Planned**

### Features

- [ ] Extract authentication logic.
- [ ] Extract wallet operations.
- [ ] Extract transaction operations.
- [ ] Introduce header files.
- [ ] Introduce a Makefile.
- [ ] Define module interfaces.
- [ ] Reduce unnecessary global state.

### Learning objectives

- Header files.
- Compilation and linking.
- Translation units.
- Include guards.
- Internal versus external linkage.
- Modular design.
- Build systems.

### Completion criteria

The project compiles cleanly from multiple source files.

Each module has a clear responsibility and documented interface.

---

## Milestone 6 — Dynamic memory management

**Status: Planned**

### Features

- [ ] Replace fixed-size wallet storage with dynamic storage.
- [ ] Grow storage when necessary.
- [ ] Release allocated memory correctly.
- [ ] Handle allocation failures.
- [ ] Establish clear ownership rules.

### Learning objectives

- Pointers.
- Heap allocation.
- `malloc`, `calloc`, `realloc`, and `free`.
- Memory ownership.
- Memory lifetime.
- Memory leaks.
- Undefined behavior.

### Completion criteria

The application supports dynamically growing collections without memory leaks or invalid memory access in tested scenarios.

---

## Milestone 7 — Testing and reliability

**Status: Planned**

### Features

- [ ] Introduce unit tests.
- [ ] Test wallet calculations.
- [ ] Test transaction operations.
- [ ] Test invalid inputs.
- [ ] Test file persistence.
- [ ] Test edge cases.
- [ ] Run AddressSanitizer.
- [ ] Run UndefinedBehaviorSanitizer.
- [ ] Add automated build and test commands.

### Learning objectives

- Unit testing.
- Test isolation.
- Assertions.
- Regression testing.
- Debugging.
- Memory diagnostics.
- Software quality.

### Completion criteria

Core business logic has automated tests.

The project builds without compiler warnings and passes its documented test suite.

---

## Milestone 8 — Portfolio release

**Status: Planned**

### Features

- [ ] Complete README.
- [ ] Document installation and usage.
- [ ] Explain application architecture.
- [ ] Document important technical decisions.
- [ ] Add terminal screenshots or demonstrations.
- [ ] Document testing procedures.
- [ ] Create a tagged release.
- [ ] Add the project to the personal portfolio.

### Learning objectives

- Technical communication.
- Software documentation.
- Git workflows.
- Release management.
- Explaining design decisions.
- Interview preparation.

### Completion criteria

A developer unfamiliar with the project can build, run, and test it using the documentation.

The student can independently explain its architecture, data structures, memory management, and main algorithms.

---

## Optional advanced extensions

These are not required for the initial portfolio release.

### Advanced terminal interface

- Arrow-key navigation.
- Terminal UI using ncurses.
- Keyboard shortcuts.
- Improved terminal layouts.

### Financial analytics

- Spending categories.
- Monthly reports.
- Budget tracking.
- Transaction filtering.
- Export to CSV.

### Advanced storage

- SQLite integration.
- Database schema design.
- Migration from file-based storage.

### Security

- Persistent user accounts.
- Password hashing using an established library.
- Authentication threat modeling.
- Secure credential handling.

### Advanced algorithms

- Sorting transactions.
- Searching and filtering.
- Performance measurement.
- Time and space complexity analysis.

---

## Engineering decisions to revisit

### Monetary representation

Using `double` for money is convenient for early experiments but can introduce floating-point rounding errors.

Before implementing transactions, evaluate storing amounts as integer minor units, such as cents, using `int64_t`.

### Authentication

Hardcoded credentials are temporary learning scaffolding.

They are not a secure authentication system.

### Data persistence

Begin with a simple documented text format.

Evaluate more advanced storage only after understanding basic file I/O.

### Architecture

Avoid adding complexity before it serves a clear educational or functional purpose.

---

## Development principles

1. Complete one milestone at a time.
2. Learn the required concepts before implementing advanced features.
3. Write code independently whenever possible.
4. Test features before marking them complete.
5. Keep commits focused.
6. Document important design decisions.
7. Prefer correctness and understanding over feature count.
