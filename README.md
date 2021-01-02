[![Build status](https://ci.appveyor.com/api/projects/status/defmhg4753c1ap1o?svg=true)](https://ci.appveyor.com/project/xensik/gsc-tool)
![license](https://img.shields.io/github/license/xensik/gsc-tool.svg)
![GitHub issues](https://img.shields.io/github/issues/xensik/gsc-tool)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/xensik/gsc-tool)
# GSC Tool
A utility to compile & decompile IW engine game scripts.
## Supported Games 
- **IW5** *(Call of Duty: Modern Warfare 3)*
- **IW6** *(Call of Duty: Ghosts)*
- **IW7** *(Call of Duty: Infinite Warfare)*
- **IW8** *(Call of Duty: Modern Warfare (2019))* ***\*WIP\****
- **S1** *(Call of Duty: Advanced Warfare)*
- **S2** *(Call of Duty: WWII)*
- **H1** *(Call of Duty: Modern Warfare Remastered)*
- **H2** *(Call of Duty: Modern Warfare 2 Campaign Remastered)*
## Usage
``./gsc-tool.exe <game> <mode> <file>``

**game**: `-iw5`, `-iw6`, `-iw7`, `-s1`, `-s2`, `-h1`, `-h2`
| Mode     |Description                | Output      |
|:---------|:--------------------------|:------------|
|`-asm`    |assemble a `file.gscasm`   |`file.gscbin`|
|`-disasm` |dissasemble a `file.gscbin`|`file.gscasm`|
|`-comp`   |compile a `file.gsc`       |`file.gscbin`|
|`-decomp` |decompile a `file.gscbin`  |`file.gsc`   |

for zonetool files (*.cgsc*, *.cgsc.stack*) use: `-zasm`, `-zdisasm`, `-zcomp`, `-zdecomp`
## Credits
This project is based on  [*RektInator's* gsc-asm](https://github.com/ZoneTool/gsc-asm). Special thanks to **RektInator** & **JTAG**.
