# Personal Wallet

An educational command-line personal finance application written in C.

## Overview

Personal Wallet is a project developed while studying Computer Science, with the goal of learning C programming, data structures, memory management, algorithms, and software engineering through practical development.

The long-term objective is to build a terminal-based application for managing wallets, tracking transactions, and calculating personal net worth.

**Status: Early development — learning project.**

## Current functionality

- Interactive terminal menu.
- Basic login using hardcoded credentials.
- Username and password comparison.
- Initial registration screen placeholder.
- Menu navigation using application states.

The current authentication mechanism is for educational purposes only and is not secure for real-world use.

## Planned functionality

- Multiple wallets.
- Income and expense tracking.
- Wallet transfers.
- Net worth calculation.
- Persistent data storage.
- Modular architecture.
- Automated testing.

See `ROADMAP.md` for development milestones and learning objectives.

## Build and run

Requirements: a C compiler supporting C17.

From the project root:

```bash
cp src/credentials.example.h src/credentials.h
```

For a fresh checkout, copy the example once, then edit `src/credentials.h` to set
your educational username and password. If that file already exists, edit it
directly instead of copying over it. Git ignores `credentials.h` to keep local
values out of future commits. The values are still embedded in the executable;
use a made-up password. Recompile after changing them.

```bash
gcc -std=c17 -Wall src/main.c -o wallet
./wallet
```

## Learning objectives

This project explores:

- C programming fundamentals.
- Data structures and algorithms.
- Pointers and memory management.
- File I/O.
- Modular software design.
- Testing and debugging.
- Software engineering practices.

## Development approach

The application is developed incrementally, with an emphasis on understanding each implementation decision.

AI-assisted development tools are used for explanations, code reviews, debugging guidance, writing documentation and learning support.

The objective is to independently understand and maintain the resulting code.

## Project documentation

- `AGENTS.md` — AI development assistant instructions.
- `ROADMAP.md` — Planned features and learning milestones.

## Disclaimer

This project is educational software and should not be used to store sensitive financial credentials or manage real financial assets.
