# Tombstone · ![GitHub Logo](https://img.shields.io/badge/release-v1.0.0-blue.svg) ![GitHub Logo](https://img.shields.io/badge/dependencies-up--to--date-green.svg) ![GitHub Logo](https://img.shields.io/badge/Linux%20build-passing-brightgreen.svg) ![GitHub Logo](https://img.shields.io/badge/Windows%20build-passing-brightgreen.svg)
The official repository of the Tombstone C++ namespace.

Usage of this repository is publicly available, under the [Mozilla Public License v2.0](https://www.mozilla.org/en-US/MPL/2.0/).

## Syntatical Conventions
* Tombstone's naming convention follows `lowerCamelCase` standards, for ease of development (with the exception of classes, structures, and namespaces) and to remain consistent, through the source code:
  * Class: `class Foo`
  * Struct: `struct Foo`
  * Method: `bool fooBar()`
  * Variable: `auto fooBar`
* Curly-brace placement is placed immediately after the identifying operator or keyword, taking after the [K&R Style](https://en.wikipedia.org/wiki/Indentation_style#K&R_style).
## Developers' Notes
* Tested and stable on Windows-based platforms.
* Tested and stable on Linux-based platforms.
* Potentially unstable parts of the source code are identified using the keyword [volatile](https://en.wikipedia.org/wiki/Volatile_(computer_programming)) -- a valid C++ identifier.
* A handful of methods you may encounter are extremely volatile and can possibly cause deadly runtime errors for you and/or the application(s) you are testing with; only experienced C++ programmers are advised to utilize or modify these types of designated methods, though some variables may have the identifier simply becase their state is always changing (e.g. time).
