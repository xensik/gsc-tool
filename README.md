# GSC Tool
A utility to compile & decompile IW engine game scripts.
## Supported Games 
- **IW5** *(Call of Duty: Modern Warfare 3)*
- **IW6** *(Call of Duty: Ghosts)*
- **IW7** *(Call of Duty: Infinite Warfare)*
- **S1** *(Call of Duty: Advanced Warfare)*
- **S2** *(Call of Duty: WWII)*
- **H1** *(Call of Duty: Modern Warfare Remastered)*
- **H2** *(Call of Duty: Modern Warfare 2 Campaign Remastered)*
## Usage
``./gsc-tool.exe <game> <mode> <file>``

**game**: `-iw5`, `-iw6`, `-s1`, `-s2`, `-h1`, `-h2`
| Mode     |Description                | Output      |
|:---------|:--------------------------|:------------|
|`-asm`    |assemble a `file.gscasm`   |`file.gscbin`|
|`-disasm` |dissasemble a `file.gscbin`|`file.gscasm`|
|`-comp`   |compile a `file.gsc`       |`file.gscbin`|
|`-decomp` |decompile a `file.gscbin`  |`file.gsc`   |
## Credits
This project is based on  [*RektInator's* gsc-asm](https://github.com/ZoneTool/gsc-asm). Special thanks to **RektInator** & **JTAG**.
