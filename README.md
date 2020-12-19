# GSC Tool
A utility to compile & decompile IW engine game scripts.
## Supported Games 
- **IW5** *(Call of Duty: Modern Warfare 3)*
- **IW6** *(Call of Duty: Ghosts)*
- **S1** *(Call of Duty: Advanced Warfare)* ***\*WIP\****
- **H1** *(Call of Duty: Modern Warfare Remastered)* ***\*WIP\****
- **H2** *(Call of Duty: Modern Warfare 2 Campaign Remastered)* ***\*WIP\****
## Usage
``./gsc-tool.exe <game> <mode> <file>``

**game**: `-iw5`, `-iw6`, `-s1`, `-h1`, `-h2`
| Mode     |Description              | Output      |
|:---------|:------------------------|:------------|
|`-asm`    |assemble a `file.gscasm` |`file.xgsc`  |
|`-disasm` |dissasemble a `file.xgsc`|`file.gscasm`|
|`-comp`   |compile a `file.gsc`     |`file.xgsc`  |
|`-decomp` |decompile a `file.xgsc`  |`file.gsc`   |
## Credits
This project is based on  [*RektInator's* gsc-asm](https://github.com/ZoneTool/gsc-asm). Special thanks to **RektInator** & **JTAG**.