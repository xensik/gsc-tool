# GSC Tool
A utility to assemble/disassemble, compile & decompile IW engine game scripts.
## Supported Games 
- **IW5** (*Call of Duty: Modern Warfare 3*)
- **IW6** (*Call of Duty: Ghosts*)
- **S1** (*Call of Duty: Advanced Warfare*)
- **H1** (*Call of Duty: Modern Warfare Remastered*)
## Usage
``./gsc-tool.exe <game> <mode> <file>``

**game**: `-iw5`, `-iw6`, `-sh1`
| Modes    |Description                                  | Output                        |
|:---------|:--------------------------------------------|:------------------------------|
|`-asm`    |assemble a `file.gscasm`                     |`file.cgsc` + `file.cgsc.stack`|
|`-disasm` |dissasemble a `file.cgsc` + `file.cgsc.stack`|`file.gscasm`                  |
|`-comp`   |compile a `file.gsc`                         |`file.cgsc` + `file.cgsc.stack`|
|`-decomp` |decompile a `file.cgsc` + `file.cgsc.stack`  |`file.gsc`                     |
## Credits
This project is based on  [*RektInator's* gsc-asm](https://github.com/ZoneTool/gsc-asm). Special thanks to **RektInator** & **JTAG**.