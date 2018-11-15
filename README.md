# Milne's minidb

A tiny database engine.

---

# Project Status

This project is currently unfit for any purpose.

Current testing status: [![Build Status](https://travis-ci.com/shakna-israel/minidb.svg?branch=master)](https://travis-ci.com/shakna-israel/minidb)

Requires a C99 capable compiler.

For Windows, requires MSVC < VS2013 (_MSC_VER >= 1800). (Earlier versions didn't support C99 size_t format specifiers.) (Or use a non-Microsoft compiler with proper C99 support.)

[TCC](https://bellard.org/tcc/) is explicitly supported, because I love the thing.

Both GCC and Clang are tested by the automated test rig above.

---

# License

Copyright (C) 2018 James Milne

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program (See [LICENSE.md](LICENSE.md)).  If not, see <https://www.gnu.org/licenses/>.
