# Simple Terminal User Interface (TUI)

A simple terminal user interface engine, in development not finished

## Features

This project isn't finished so no features to talk about yet

## Structure

`src/`: contains tui library files \
`example/`: contains project that uses tui library

## Docs

`docs/`: Documentation for TUI library and how to use it

## Contributing

This project is under MIT license and any use of it free of charge or attribution. Any contribution to this project is welcome and greatly appreciated. Have fun!

## Building

This project uses Makefile and to build C++ files

| Command | Builds Library | Builds Example | Runs Program |
| - | - | - | - |
| `make` | ✔️ | ✔️ | ✖️ |
| `make example` | ✖️ | ✔️ | ✖️ |
| `make lib` | ✔️ | ✖️ | ✖️ |
| `make run` | ✔️ | ✔️ | ✔️ |
| `make run_only` | ✖️ | ✖️ | ✔️ |
| `make clean` |  -- | -- | -- |