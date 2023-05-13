[![build](https://github.com/xensik/gsc-tool/workflows/Build/badge.svg)](https://github.com/xensik/gsc-tool/actions)
![license](https://img.shields.io/github/license/xensik/gsc-tool.svg)
[![issues](https://img.shields.io/github/issues/xensik/gsc-tool)](https://github.com/xensik/gsc-tool/issues)
[![releases](https://img.shields.io/github/v/release/xensik/gsc-tool)](https://github.com/xensik/gsc-tool/releases)
[![paypal](https://img.shields.io/badge/PayPal-support-blue.svg?logo=paypal)](https://www.paypal.me/xensik)

# GSC Tool
A utility to compile & decompile IW engine game scripts.

## Supported Games
- **IW5** *(Call of Duty: Modern Warfare 3)* `PC` `PS3` `Xbox 360`
- **IW6** *(Call of Duty: Ghosts)* `PC` `PS3` `PS4` `Xbox 360` `Xbox One`
- **IW7** *(Call of Duty: Infinite Warfare)* `PC` `PS4` `Xbox One`
- **IW8** *(Call of Duty: Modern Warfare (2019) / Warzone)* `PC` `PS4` `PS5` `Xbox One` `Xbox Series X|S`
- **IW9** *(Call of Duty: Modern Warfare II (2022) / Warzone 2)* `PC` `PS4` `PS5` `Xbox One` `Xbox Series X|S`
- **S1** *(Call of Duty: Advanced Warfare)* `PC` `PS3` `PS4` `Xbox 360` `Xbox One`
- **S2** *(Call of Duty: WWII)* `PC` `PS4` `Xbox One`
- **S4** *(Call of Duty: Vanguard)* `PC` `PS4` `PS5` `Xbox One` `Xbox Series X|S`
- **H1** *(Call of Duty: Modern Warfare Remastered)* `PC` `PS4` `Xbox One`
- **H2** *(Call of Duty: Modern Warfare 2 Campaign Remastered)* `PC` `PS4` `PS5` `Xbox One` `Xbox Series X|S`
- **T6** *(Call of Duty: Black Ops II)* `PC` `PS3` `Xbox 360` `Wii U`
- **T7** *(Call of Duty: Black Ops III)* `PC` *(Decompiler)*
- **T8** *(Call of Duty: Black Ops 4)* ***\*WIP\****
- **T9** *(Call of Duty: Black Ops Cold War)* ***\*WIP\****

## Usage
``./gsc-tool.exe <mode> <game> <system> <path>``

**mode**: `asm`, `disasm`, `comp`, `decomp`, `parse`
- *note:* zonetool files (*.cgsc*, *.cgsc.stack*) use: `zasm`, `zdisasm`, `zcomp`, `zdecomp` modes

**game**: `iw5`, `iw6`, `iw7`, `iw8`, `iw9`, `s1`, `s2`, `s4`, `h1`, `h2`, `t6` `t7` `t8` `t9`

**system**: `pc`, `ps3`, `ps4`, `ps5`, `xb2` (*360*), `xb3` (*One*), `xb4` (*Series X|S*), `wiiu`

**path**: `file` or `directory` (recursive process all files inside the directory)

Example: ``./gsc-tool.exe comp iw5 pc ./data/iw5/my_fancy_script.gsc``

| Mode     |Description                | Output      |
|:---------|:--------------------------|:------------|
|`asm`     |assemble a `file.gscasm`   |`file.gscbin`|
|`disasm`  |dissasemble a `file.gscbin`|`file.gscasm`|
|`comp`    |compile a `file.gsc`       |`file.gscbin`|
|`decomp`  |decompile a `file.gscbin`  |`file.gsc`   |
|`parse`   |parse a `file.gsc`         |`file.gsc`   |

## File Format
If you need to extract scripts from fastfiles or game memory, use [Zonetool](https://github.com/ZoneTool/zonetool) or [Jekyll](https://github.com/EthanC/Jekyll).

- gsc-tool `.gscbin` format is a serialized ScriptFile struct: <br/>
***name***: null-terminated string <br/>
***compressedLen***: 4 byte uint <br/>
***len***: 4 byte uint <br/>
***bytecodeLen***: 4 byte uint <br/>
***buffer***: byte array[compressedLen] <br/>
***bytecode***: byte array[bytecodeLen] <br/>

note: for PS3 & Xbox 360 `.gscbin` files *(compressedLen, len, bytecodeLen)* are saved as little-endian!!

- zonetool (IW5) format made of bytecode file `.cgsc` and decompressed stack buffer `.cgsc.stack`.

- treyarch (T6) format is a single buffer with gscobj data `.gsc` or `.csc`.

## Contribute
If you like my work, consider sponsoring/donating! Would allow me to spend more time adding new features & fixing bugs.

BTC: bc1qky7x9kpjlt6nsvt7pckc3wwzk8rk9pgtnmw98u\
ETH: 0x6261BBE1a33F6Fec4b722DbCe2c28B4CC02c9C7B\
[![pypl](https://img.shields.io/badge/PayPal-00457C?style=for-the-badge&logo=paypal&logoColor=white)](https://www.paypal.me/xensik)   [![kofi](https://img.shields.io/badge/Ko--fi-F16061?style=for-the-badge&logo=ko-fi&logoColor=white)](https://ko-fi.com/xensik)

## Credits
This project is based on [*RektInator's* gsc-asm](https://github.com/ZoneTool/gsc-asm). Special thanks to **RektInator**, **JTAG** & **Dasfonia**.

## Disclaimer
This software has been created purely for the purposes of academic research. Project maintainers are not responsible or liable for misuse of the software. Use responsibly.
