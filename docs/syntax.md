# GSC / CSC Language Reference

Complete syntax reference for every script dialect `gsc-tool` understands — the Infinity
Ward / Sledgehammer / remaster family (`.gsc` server scripts, `.csc` client scripts) and the
Treyarch / Jupiter family.

The grammar described here is the one implemented by the tool itself: `src/{gsc,arc}/lexer.cpp`,
`src/{gsc,arc}/preprocessor.cpp` and `src/{gsc,arc}/parser.cpp`, with the semantic rules
enforced by `src/{gsc,arc}/compiler.cpp`. Where the tool accepts more than the stock game
compiler did, that is noted.

## Engines

| Engine | Game | Family |
| --- | --- | --- |
| `iw5` | Call of Duty: Modern Warfare 3 | IW |
| `iw6` | Call of Duty: Ghosts | IW |
| `iw7` | Call of Duty: Infinite Warfare | IW |
| `iw8` | Call of Duty: Modern Warfare (2019) | IW |
| `iw9` | Call of Duty: Modern Warfare II (2022) | IW |
| `s1` | Call of Duty: Advanced Warfare | IW |
| `s2` | Call of Duty: WWII | IW |
| `s4` | Call of Duty: Vanguard | IW |
| `h1` | Call of Duty: Modern Warfare Remastered | IW |
| `h2` | Call of Duty: Modern Warfare 2 Campaign Remastered | IW |
| `t6` | Call of Duty: Black Ops II | ARC |
| `t7` | Call of Duty: Black Ops III | ARC |
| `t8` | Call of Duty: Black Ops 4 | ARC — not implemented |
| `t9` | Call of Duty: Black Ops Cold War | ARC — not implemented |
| `jup` | Call of Duty: Modern Warfare III (2023) | ARC — not implemented |

## Three dialects

The two families are separate front ends that happen to share a shape, and the Treyarch one
splits again at Black Ops III:

| Dialect | Engines | Shape |
| --- | --- | --- |
| **IW** | `iw5` `iw6` `iw7` `iw8` `iw9` `s1` `s2` `s4` `h1` `h2` | `#include`, bare `name()` functions, `::func` references |
| **ARC legacy** | `t6` | `#include`, bare `name()` functions, `::func` references, `const`, keyword builtins |
| **ARC modern** (v3) | `t7` | `#using` / `#namespace` / `#precache`, `function name()`, `&func` references, classes, varargs |

Inside the IW family every engine parses the same grammar except for three feature gates
(below). Inside the ARC family the whole split is driven by a single flag, `feature::size64`,
which only `t7` sets — so "ARC modern" and "`t7`" mean the same thing throughout this
document.

`t8`, `t9` and `jup` are registered but unfinished: every CLI mode refuses them with
`not implemented`, and their contexts do not set `size64`. Real Black Ops 4 / Cold War /
MWIII scripts use the ARC modern dialect, but nothing in this document is claimed for them
yet.

## Engine labels

Every construct carries an **Engines** label:

| Label | Means |
| --- | --- |
| `all` | every engine the tool implements: `iw5`–`h2`, `t6`, `t7` |
| `IW` | `iw5` `iw6` `iw7` `iw8` `iw9` `s1` `s2` `s4` `h1` `h2` |
| `ARC` | `t6` `t7` |
| explicit list | exactly those engines, e.g. `iw8` `iw9` `s4` |

**Reading the examples.** Unless a block says otherwise, examples are written in the
IW / `t6` spelling — a bare `main()` function. On `t7` the same body goes inside
`function main()`, and far calls use `namespace::function` instead of `path\function`; see
[3.2](#32-function-declaration--t7) and [7.2](#72-far-call). Blocks that only make sense in
one dialect are marked with a comment on the first line.

Feature gates inside the IW family:

| Difference | Engines | Flag |
| --- | --- | --- |
| `waitframe` statement | `iw8` `iw9` `s1` `s2` `s4` `h1` `h2` | `gsc::feature::waitframe` |
| `isdefined` / `istrue` as operators | `iw8` `iw9` `s4` | `gsc::feature::boolfuncs` |
| `foreach` key/value lowering | `iw9` | `gsc::feature::foreach` |

## Tool support

Syntax support and pipeline support are not the same thing:

| Mode | IW engines | `t6` | `t7` | `t8` `t9` `jup` |
| --- | --- | --- | --- | --- |
| `parse` | all | yes | yes | no |
| `comp` | all | yes | no | no |
| `decomp` | all | yes | yes | no |
| `asm` | all | yes | no | no |
| `disasm` | all | yes | yes | no |
| `rename` | all | no | no | no |

Every example below was checked with `gsc-tool -m parse` on each engine it is labelled for,
and additionally with `-m comp` wherever a compiler exists.

---

# 1. Lexical structure

## 1.1 Source files

**Engines:** all

Scripts are plain ASCII text; LF or CRLF line endings.

| Extension | Role |
| --- | --- |
| `.gsc` | server script |
| `.csc` | client script |
| `.gsh` | header, pulled in with `#inline` (IW, `t6`) or `#insert` (`t7`) |

Compiled output is `.gscbin` for IW (or `.cgsc` + `.cgsc.stack` in zonetool mode) and a
single `\x80GSC` buffer for ARC.

## 1.2 Case sensitivity

**Engines:** all

Identifiers are **case-insensitive** — the parser lowercases every name token, so `Level`,
`LEVEL` and `level` are the same name. Names starting with `_id_`, `_func_` or `_meth_` are
left untouched; the decompiler generates those for unresolved hashes.

String literals keep their case.

```gsc
main()
{
    Level.Health = 100;
    a = level.health; // same field
}
```

## 1.3 Comments

**Engines:** all

```gsc
// line comment

/* block
   comment */

/@ script doc comment,
   also spans lines @/
```

Block comments do not nest.

## 1.4 Line continuation

**Engines:** all

A backslash immediately before the line ending splices the two lines, as in C.

```gsc
main()
{
    a = 1 + \
        2;
}
```

## 1.5 Identifiers

**Engines:** all

`[A-Za-z_][A-Za-z0-9_]*`. An identifier containing backslashes lexes as a **path** token
instead — see [`#include`](#33-include) and [far calls](#82-far-call).

```gsc
main()
{
    my_var  = 1;
    _hidden = 2;
    v3      = 3;
}
```

## 1.6 Keywords — IW

**Engines:** `IW`

| | | | |
| --- | --- | --- | --- |
| `anim` | `assert` | `assertex` | `assertmsg` |
| `break` | `breakpoint` | `call` | `case` |
| `childthread` | `continue` | `default` | `do` |
| `else` | `endon` | `false` | `for` |
| `foreach` | `game` | `if` | `in` |
| `level` | `notify` | `prof_begin` | `prof_end` |
| `return` | `self` | `size` | `switch` |
| `thisthread` | `thread` | `true` | `undefined` |
| `wait` | `waittill` | `waittillframeend` | `waittillmatch` |
| `while` | | | |

Conditional:

| Keyword | Engines | Elsewhere |
| --- | --- | --- |
| `waitframe` | `iw8` `iw9` `s1` `s2` `s4` `h1` `h2` | ordinary identifier |
| `isdefined` | `iw8` `iw9` `s4` | builtin function |
| `istrue` | `iw8` `iw9` `s4` | unresolved — no such builtin |

## 1.7 Keywords — ARC

**Engines:** `ARC`

Shared by `t6` and `t7`:

| | | | |
| --- | --- | --- | --- |
| `abs` | `angleclamp180` | `anglestoforward` | `anglestoright` |
| `anglestoup` | `anim` | `autoexec` | `break` |
| `case` | `codecall` | `const` | `continue` |
| `default` | `do` | `else` | `endon` |
| `false` | `for` | `foreach` | `game` |
| `getdvar` | `getdvarcoloralpha` | `getdvarcolorblue` | `getdvarcolorgreen` |
| `getdvarcolorred` | `getdvarfloat` | `getdvarint` | `getdvarvector` |
| `getfirstarraykey` | `getnextarraykey` | `gettime` | `if` |
| `in` | `isdefined` | `level` | `notify` |
| `private` | `prof_begin` | `prof_end` | `return` |
| `self` | `size` | `switch` | `thread` |
| `true` | `undefined` | `vectorscale` | `vectortoangles` |
| `wait` | `waitrealtime` | `waittill` | `waittillframeend` |
| `waittillmatch` | `while` | | |

`t7` only — on `t6` these are ordinary identifiers:

| | | | |
| --- | --- | --- | --- |
| `class` | `classes` | `constructor` | `destructor` |
| `function` | `new` | `var` | `world` |

Note the words that are **not** ARC keywords: `assert`, `assertex`, `assertmsg`,
`breakpoint`, `call`, `childthread`, `istrue`, `thisthread`. They lex as plain identifiers,
so `childthread foo();` parses as a method call on a variable named `childthread` and fails
later with `local variable 'childthread' not found`.

`size` is contextual in both families: an accessor after `.`, but also usable as a plain
identifier. `wait` is accepted as a field name (`obj.wait`).

## 1.8 Integer literals

**Engines:** all

| Form | Example |
| --- | --- |
| decimal | `42` |
| hexadecimal | `0x2A` |
| binary | `0b101010` |
| octal | `0o52` |
| digit separator | `1'000'000` |

All forms are folded to decimal at lex time. A separator may not sit next to the base
prefix, a `.`, an `f`, an exponent marker, or another separator.

```gsc
main()
{
    a = 42;
    b = 0x2A;
    c = 0b101010;
    d = 0o52;
    e = 1'000'000;
}
```

## 1.9 Float literals

**Engines:** all

A literal is a float when it has a decimal point, an `f` suffix, or an exponent.

```gsc
main()
{
    a = 1.5;
    b = .5;    // leading dot
    c = 2.0f;  // f suffix
    d = 1e5;   // exponent, float even though the value is integral
    e = 1.5e-3;
}
```

## 1.10 String literals

**Engines:** all

Double-quoted, single-line. Recognized escapes are `\t`, `\r`, `\n`, `\"` and `\\`; any
other escaped character is passed through unchanged.

```gsc
main()
{
    a = "hello";
    b = "tab\there\nnewline \"quoted\" back\\slash";
}
```

## 1.11 Localized string literals

**Engines:** all

`&"…"` marks a localized string reference — the game resolves it through the localization
table at runtime instead of using the literal text.

```gsc
main()
{
    objective_add( 1, "current", &"DUBAI_OBJ_KILL_MAKAROV" );
}
```

## 1.12 Hashed string literals

**Engines:** `ARC`

`#"…"` compiles to the hash of the string instead of the string itself. Treyarch code uses
these for event names and lookup keys. There must be no space between `#` and the quote.

```gsc
// t6
main()
{
    self notify( #"player_downed" );
}
```

```gsc
// t7
function main()
{
    self callback::callback( #"on_player_spawned" );
}
```

The IW front end recognizes `#` but has no hash-literal rule yet, so `#"…"` is an error
there.

## 1.13 Animation literals

**Engines:** all

`%name` references an animation from the animtree selected with `#using_animtree`. ARC also
accepts a tree-qualified form.

```gsc
#using_animtree( "generic_human" );

main()
{
    level.anims["idle"] = %generic_human_idle;
}
```

```gsc
// ARC only: %tree::anim
#using_animtree( "generic_human" );

main()
{
    a = %root::idle;
}
```

## 1.14 `#animtree`

**Engines:** all

Evaluates to the animtree selected by the enclosing `#using_animtree`, for passing to
functions that take a tree.

```gsc
#using_animtree( "player" );

main()
{
    level.scr_animtree["player_rig"] = #animtree;
}
```

## 1.15 Operators and punctuation

**Engines:** as marked

| Class | Tokens | Engines |
| --- | --- | --- |
| arithmetic | `+` `-` `*` `/` `%` | all |
| bitwise | `&` `\|` `^` `~` `<<` `>>` | all |
| logical | `&&` `\|\|` `!` | all |
| relational | `==` `!=` `<` `<=` `>` `>=` | all |
| strict equality | `===` `!==` | `t7` |
| assignment | `=` `+=` `-=` `*=` `/=` `%=` `&=` `\|=` `^=` `<<=` `>>=` | all |
| increment | `++` `--` | all |
| ternary | `?` `:` | all |
| access | `.` `[` `]` `::` | all |
| member call | `->` | `t7` |
| reference | `&` prefix | `t7` |
| varargs | `...` | `t7` |
| grouping | `(` `)` `{` `}` | all |
| separators | `,` `;` | all |
| preprocessor | `#` `##` | all |
| dev block | `/#` `#/` | all |

`..` is lexed but has no grammar rule in either family.

---

# 2. Preprocessor

Both families ship the same C-style preprocessor, running between the lexer and the parser.
Clang's `-E` behaviour is the reference for macro semantics. Only the directive set differs.

## 2.1 `#define` — object-like macro

**Engines:** all

```gsc
#define MAX_HEALTH 100
#define DEBUG_NAME "player"

main()
{
    self.health = MAX_HEALTH;
}
```

## 2.2 `#define` — function-like macro

**Engines:** all

Supports parameters, stringize `#`, token paste `##`, variadics via `__VA_ARGS__`, and
`__VA_OPT__`. Recursive expansion is blocked the way C blocks it ("blue paint").

```gsc
#define SQR( x )        ( ( x ) * ( x ) )
#define STR( x )        #x
#define CAT( a, b )     a##b
#define LOG( f, ... )   println( f __VA_OPT__(,) __VA_ARGS__ )

main()
{
    a = SQR( 3 );      // ( ( 3 ) * ( 3 ) )
    b = STR( hello );  // "hello"
    CAT( va, r ) = 1;  // var = 1
    LOG( "hi" );
    LOG( "hi %d", 2 );
}
```

## 2.3 `#undef`

**Engines:** all

```gsc
#define TEMP 1
#undef TEMP
```

## 2.4 Conditional compilation

**Engines:** all

`#if` `#ifdef` `#ifndef` `#elif` `#elifdef` `#elifndef` `#else` `#endif`, arbitrarily
nested. `#if` evaluates a C-style integer constant expression, including `defined( X )`,
arithmetic, comparison, bitwise and logical operators.

```gsc
#define VERSION 2

#if VERSION >= 2 && !defined( LEGACY )
    #define SPAWN_FUNC spawn_v2
#elif defined( LEGACY )
    #define SPAWN_FUNC spawn_v1
#endif

#ifdef T6
    // Black Ops II only
#endif
```

## 2.5 Predefined macros

**Engines:** all

| Macro | Expands to |
| --- | --- |
| `__FILE__` | current file name |
| `__LINE__` | current line number |
| `__DATE__` | compilation date |
| `__TIME__` | compilation time |
| engine name | `IW5` … `H2`, `T6` … `T9` — uppercase, only the current engine is defined |

`jup` has no engine macro.

```gsc
#ifdef IW9
    // MWII-only path
#endif

main()
{
    a = __FILE__;
    b = __LINE__;
}
```

## 2.6 Unsupported directives

**Engines:** all

`#pragma`, `#warning`, `#error` and `#line` are recognized and **rejected** with a
preprocessor error. Inside a skipped conditional branch they are ignored, as in C.

## 2.7 Directive availability

| Directive | IW | `t6` | `t7` |
| --- | --- | --- | --- |
| `#define` `#undef` `#if…#endif` | yes | yes | yes |
| `#include` | yes | yes | — |
| `#inline` | yes | yes | — |
| `#using_animtree` | yes | yes | yes |
| `#using` | — | — | yes |
| `#insert` | — | — | yes |
| `#namespace` | — | — | yes |
| `#precache` | — | — | yes |

Using a directive outside its column is a preprocessor error
(`invalid preprocessing directive 'using'` on `t6`), or a parse error when the token exists
but the dialect wants the other spelling (`expected '#using', got '#include'` on `t7`).

## 2.8 Developer blocks

**Engines:** all

Code between `/#` and `#/` is developer-only. In the IW family the lexer skips it entirely
unless the tool runs with `-d` / `--dev`; in the ARC family the tokens are always produced.
Dev blocks work at file scope and inside a function body, and do not nest in IW.

```gsc
main()
{
    /#
        println( "debug only" );
    #/
}

/#
debug_only_function()
{
}
#/
```

---

# 3. File structure

```
program     : ( include | inline | declaration )*
declaration : namespace | precache | usingtree | class | constant | function | devblock
```

## 3.1 Function declaration — IW and `t6`

**Engines:** `IW` `t6`

Every function is public; there is no visibility modifier. A function with no explicit
`return` returns `undefined`.

```gsc
give_weapon( weapon, ammo )
{
    self giveweapon( weapon );
    self givemaxammo( weapon );
    return weapon;
}
```

## 3.2 Function declaration — `t7`

**Engines:** `t7`

The `function` keyword is mandatory, and one optional export flag may follow it.

| Flag | Meaning |
| --- | --- |
| `autoexec` | runs automatically when the script loads |
| `private` | callable only from the declaring script |
| `codecall` | callable from engine code |

```gsc
function main( weapon )
{
    return weapon;
}

function autoexec __init__()
{
    system::register( "zm", &__init__, undefined, undefined );
}

function private helper( a )
{
    return a;
}
```

## 3.3 `#include`

**Engines:** `IW` `t6`

Makes another script's functions callable unqualified from this file. Backslash path, no
extension, terminated with `;`.

```gsc
#include maps\_utility;
#include common_scripts\utility;

main()
{
    flag_set( "started" ); // resolved from common_scripts\utility
}
```

When compiling, the included script must exist under the working directory (`-w`) as
compiled bytecode.

## 3.4 `#using`

**Engines:** `t7`

The ARC modern spelling of `#include`.

```gsc
#using scripts\shared\util_shared;
#using scripts\shared\array_shared;

function main()
{
    a = 1;
}
```

## 3.5 `#inline`

**Engines:** `IW` `t6`

Splices a `.gsh` header at that point. Headers may contain **preprocessor definitions
only** — no function declarations, no `#include`, no `#using_animtree`.

```gsc
// shared.gsh
#define TEAM_AXIS "axis"

// script.gsc
#inline shared;

main()
{
    a = TEAM_AXIS;
}
```

## 3.6 `#insert`

**Engines:** `t7`

The ARC modern spelling of `#inline`, with the same macro-only restriction. The path is
written **without** the extension — the front end appends `.gsh` itself.

```gsc
#insert scripts\shared\shared;

function main()
{
    a = TEAM_AXIS;
}
```

Stock Treyarch source spells the extension out (`#insert scripts\shared\shared.gsh;`), which
this front end does not accept yet: the `.` ends the path token.

## 3.7 `#namespace`

**Engines:** `t7`

Declares the namespace this file's functions belong to. Other scripts then call them as
`namespace::function()`.

```gsc
#namespace util;

function wait_till( str )
{
    a = str;
}
```

## 3.8 `#precache`

**Engines:** `t7`

Declares an asset the script needs. Takes an asset type and an asset name.

```gsc
#precache( "material", "hud_chalk_1" );
#precache( "eventstring", "zombie_spawn" );

function main()
{
    a = 1;
}
```

## 3.9 `#using_animtree`

**Engines:** all

Selects the animtree that `%anim` literals and `#animtree` resolve against, from its
position to the end of the file.

```gsc
#using_animtree( "generic_human" );
```

## 3.10 Class declaration

**Engines:** `t7`

A class holds `var` members, an optional `constructor` and `destructor`, and `function`
members. `: base` declares single inheritance. Instances come from `new`.

```gsc
class cScene : cScriptBundleBase
{
    var _str_name;
    var _n_object_id;

    constructor()
    {
        _str_name = "";
        _n_object_id = 0;
    }

    destructor()
    {
    }

    function play( str_state )
    {
        _str_name = str_state;
        return _str_name;
    }
}
```

## 3.11 Constant declaration (deprecated)

**Engines:** `IW`

A file-scope `NAME = expr;` declares a compile-time constant. The parser accepts it but
prints a deprecation notice — use `#define` instead. ARC has no file-scope constants; use
the [`const` statement](#427-const) inside a function.

```gsc
MAX_PLAYERS = 18; // deprecated, prefer: #define MAX_PLAYERS 18
```

---

# 4. Statements

## 4.1 Expression statement

**Engines:** all

Only a call, a method call, an assignment, or an increment/decrement may stand alone as a
statement. A bare value (`1;`, `a;`) is rejected.

```gsc
main()
{
    a = 1;      // assignment
    a++;        // increment
    foo();      // call
    self foo(); // method call
}
```

## 4.2 Compound statement

**Engines:** all

```gsc
main()
{
    {
        a = 1;
    }
}
```

## 4.3 Empty statement

**Engines:** all

A stray `;` is legal and does nothing.

## 4.4 `if` / `else`

**Engines:** all

The condition is any expression; there is no boolean type. `undefined`, `0` and `""` are
false. Braces are optional for a single statement.

```gsc
main()
{
    if ( self.health <= 0 )
        self kill();
    else if ( self.health < 25 )
        self setlowhealthoverlay();
    else
    {
        self.status = "ok";
    }
}
```

## 4.5 `while`

**Engines:** all

```gsc
main()
{
    while ( self.health > 0 )
    {
        wait 0.05;
    }
}
```

## 4.6 `do … while`

**Engines:** all

Body runs at least once. The trailing `;` is required.

```gsc
main()
{
    i = 0;

    do
    {
        i++;
    }
    while ( i < 10 );
}
```

## 4.7 `for`

**Engines:** all

Init and iteration must each be an assignment, an increment/decrement, or empty — a bare
call is not accepted there. All three clauses may be omitted; `for ( ;; )` is the idiomatic
infinite loop.

```gsc
main()
{
    for ( i = 0; i < 10; i++ )
        println( i );

    for ( ;; )
    {
        wait 0.05;
    }
}
```

## 4.8 `foreach`

**Engines:** all

Iterates an array. The single-variable form binds the value; the two-variable form binds key
and value. Both families lower it to a `for` loop over hidden temporaries, so it compiles on
engines whose stock compiler never emitted it. `iw9` uses a dedicated lowering
(`gsc::feature::foreach`).

```gsc
main()
{
    foreach ( player in level.players )
        player thread watch_death();

    foreach ( team, players in level.teams )
        println( team + ": " + players.size );
}
```

## 4.9 `switch` / `case` / `default`

**Engines:** all

Case labels must be an integer literal, a negative integer literal, or a string literal —
not an expression. Cases fall through when they do not `break`. `default` may appear
anywhere among the cases. `continue` is not valid directly inside a switch body.

```gsc
main()
{
    switch ( self.team )
    {
        case "allies":
        case "axis":
            self.score = 1;
            break;
        case -1:
            self.score = 0;
            break;
        default:
            break;
    }
}
```

## 4.10 `break`

**Engines:** all

Exits the innermost loop or switch.

## 4.11 `continue`

**Engines:** all

Jumps to the next iteration of the innermost loop.

## 4.12 `return`

**Engines:** all

With or without a value.

```gsc
get_health()
{
    if ( !isdefined( self ) )
        return;

    return self.health;
}
```

## 4.13 `wait`

**Engines:** all

Suspends the thread for a number of seconds. The operand is an expression, not a call — it
takes no parentheses of its own.

```gsc
main()
{
    wait 0.05;
    wait level.delay * 2;
}
```

## 4.14 `waitrealtime`

**Engines:** `ARC`

Waits in real time rather than game time, so it keeps running while the game is paused or
time-scaled. Treyarch code always writes the argument parenthesized.

```gsc
main()
{
    waitrealtime( 1 );
}
```

## 4.15 `waittillframeend`

**Engines:** all

Resumes at the end of the current frame. IW also accepts an empty parameter list; ARC does
not.

```gsc
main()
{
    waittillframeend;
}
```

```gsc
// IW only
main()
{
    waittillframeend();
}
```

## 4.16 `waitframe`

**Engines:** `iw8` `iw9` `s1` `s2` `s4` `h1` `h2`

Waits one full frame. Elsewhere the word is not a keyword and there is no such opcode.

```gsc
main()
{
    waitframe;
}
```

## 4.17 `endon`

**Engines:** all

Kills the current thread when the object sends the notify.

```gsc
main()
{
    self endon( "death" );
    level endon( "game_ended" );

    for ( ;; )
        wait 0.05;
}
```

## 4.18 `notify`

**Engines:** all

Sends an event with optional payload values.

```gsc
main()
{
    level notify( "objective_complete" );
    level notify( "player_damaged", attacker, 50 );
}
```

## 4.19 `waittill`

**Engines:** all

Blocks until the object sends the event. Extra arguments receive the notify payload. The IW
compiler requires them to be plain local variable names; the ARC parser currently accepts
arbitrary expressions there.

```gsc
main()
{
    self waittill( "death" );
    self waittill( "damage", amount, attacker );
}
```

## 4.20 `waittillmatch`

**Engines:** all

Blocks until the object sends the event *and* the payload matches the given values.

```gsc
main()
{
    self waittillmatch( "single anim", "end" );
}
```

## 4.21 `assert`

**Engines:** `IW`

Aborts the script when the expression is false. On ARC engines `assert` is an ordinary
function name, not a keyword.

```gsc
main()
{
    assert( isdefined( self.origin ) );
}
```

## 4.22 `assertex`

**Engines:** `IW`

`assert` with a message.

```gsc
main()
{
    assertex( isdefined( level.players ), "players array missing" );
}
```

## 4.23 `assertmsg`

**Engines:** `IW`

Unconditional assertion failure with a message.

```gsc
main()
{
    assertmsg( "unreachable state" );
}
```

## 4.24 `breakpoint`

**Engines:** `IW`

Emits a script debugger breakpoint.

```gsc
main()
{
    breakpoint;
}
```

## 4.25 `prof_begin` / `prof_end`

**Engines:** all

Opens and closes a named profiler scope.

```gsc
main()
{
    prof_begin( "ai_update" );
    update_ai();
    prof_end( "ai_update" );
}
```

## 4.26 Tuple assignment

**Engines:** `IW`

Destructures an array into several lvalues in one statement, in index order. ARC has no
equivalent.

```gsc
main()
{
    coords = get_coords();      // [ x, y ]
    [ x, y ] = coords;
}
```

## 4.27 `const`

**Engines:** `ARC`

Declares a function-scoped compile-time constant. It cannot be reassigned.

```gsc
main()
{
    const N_MAX_DAMAGE = 500;

    self.damage = N_MAX_DAMAGE;
}
```

---

# 5. Expressions

## 5.1 Precedence

Highest to lowest. All binary operators are left-associative; the ternary is
right-associative. The ordering matches C in both families.

| Level | Operators |
| --- | --- |
| 1 | postfix: `[ ]` `.` `->` method call |
| 2 | unary: `!` `~` `-` `%anim` `&ref` |
| 3 | `*` `/` `%` |
| 4 | `+` `-` |
| 5 | `<<` `>>` |
| 6 | `<` `<=` `>` `>=` |
| 7 | `==` `!=` `===` `!==` |
| 8 | `&` |
| 9 | `^` |
| 10 | `\|` |
| 11 | `&&` |
| 12 | `\|\|` |
| 13 | `? :` |

## 5.2 Parenthesized expression

**Engines:** all

```gsc
main()
{
    a = ( 1 + 2 ) * 3;
}
```

## 5.3 Vector literal

**Engines:** all

Exactly three components, comma-separated, in parentheses. Components may be expressions.

```gsc
main()
{
    up    = ( 0, 0, 1 );
    above = ( self.origin[0], self.origin[1], self.origin[2] + 64 );
}
```

## 5.4 Arithmetic

**Engines:** all

`+` also concatenates strings and adds vectors; `%` is integer modulo.

```gsc
main()
{
    a = 1 + 2 - 3 * 4 / 5 % 6;
    s = "hp: " + self.health;
    v = self.origin + ( 0, 0, 64 );
}
```

## 5.5 Bitwise

**Engines:** all

```gsc
main()
{
    flags = ( 1 << 3 ) | ( 1 << 4 );
    mask  = flags & ~0x0F;
    x     = flags ^ 0xFF;
    y     = flags >> 2;
}
```

## 5.6 Relational and equality

**Engines:** all

`==` and `!=` compare by value for numbers and strings, by reference for entities and
arrays.

```gsc
main()
{
    if ( self.health < 25 && self.team != "axis" )
        a = 1;
}
```

## 5.7 Strict equality

**Engines:** `t7`

`===` and `!==` compare without the type coercion `==` performs — the idiom for
distinguishing `false` from `undefined`.

```gsc
function main()
{
    if ( self.scene_takedamage === false )
        a = 1;

    if ( self.state !== "idle" )
        a = 2;
}
```

## 5.8 Logical

**Engines:** all

`&&` and `||` short-circuit.

```gsc
main()
{
    if ( isdefined( self.owner ) && self.owner.health > 0 )
        a = 1;

    if ( !isdefined( level.mode ) || level.mode == "dm" )
        b = 1;
}
```

## 5.9 Unary

**Engines:** all

```gsc
main()
{
    a = -self.health; // negate
    b = !self.alive;  // logical not
    c = ~self.flags;  // bitwise complement
}
```

## 5.10 Ternary

**Engines:** all

```gsc
main()
{
    name = isdefined( self.name ) ? self.name : "unknown";
}
```

## 5.11 Assignment

**Engines:** all

`=` plus the compound forms `+=` `-=` `*=` `/=` `%=` `&=` `|=` `^=` `<<=` `>>=`. The target
must be an lvalue: a local variable, a field, or an array element. Assignment is a statement,
not an expression — `a = b = c;` is not valid.

```gsc
main()
{
    self.health  = 100;
    self.health -= 25;
    level.flags |= 1 << 2;
    arr[0]      *= 2;
}
```

## 5.12 Increment / decrement

**Engines:** all

Prefix and postfix are both accepted and, since these are statements rather than
expressions, behave identically.

```gsc
main()
{
    i = 0;
    i++;
    ++i;
    i--;
    --i;
}
```

## 5.13 `isdefined`

**Engines:** all (operator on `iw8` `iw9` `s4` and all ARC, builtin function on the rest)

True when the value exists. The universal null test — there is no `null`, only `undefined`.

```gsc
main()
{
    if ( isdefined( self.owner ) )
        a = 1;
}
```

## 5.14 `istrue`

**Engines:** `iw8` `iw9` `s4`

True when the value is defined *and* truthy — shorthand for `isdefined( x ) && x`. Not
available elsewhere; on ARC it is not a keyword and no such builtin exists.

```gsc
main()
{
    if ( istrue( self.is_hero ) )
        a = 1;
}
```

## 5.15 ARC keyword builtins

**Engines:** `ARC`

The ARC front end compiles nineteen engine calls to dedicated opcodes rather than to a
builtin call, so they are grammar, not library. IW spells the same operations as ordinary
builtin function calls.

| Keyword | Arguments |
| --- | --- |
| `abs` | 1 |
| `gettime` | 0 |
| `getdvar` | 1 |
| `getdvarint` | 1 (`t7`: 1 or 2) |
| `getdvarfloat` | 1 (`t7`: 1 or 2) |
| `getdvarvector` | 1 |
| `getdvarcolorred` / `getdvarcolorgreen` / `getdvarcolorblue` / `getdvarcoloralpha` | 1 |
| `getfirstarraykey` | 1 |
| `getnextarraykey` | 2 |
| `vectorscale` | 2 |
| `anglestoup` / `anglestoright` / `anglestoforward` | 1 |
| `angleclamp180` | 1 |
| `vectortoangles` | 1 |

The vector-valued ones may be subscripted directly: `vectorscale( v, 2 )[0]`.

```gsc
main()
{
    a   = abs( -1 );
    t   = gettime();
    d   = getdvar( "scr_mode" );
    key = getfirstarraykey( level.players );
    key = getnextarraykey( level.players, key );
    v   = vectorscale( ( 0, 0, 1 ), 64 );
    up  = anglestoup( self.angles )[2];
}
```

## 5.16 Literals `undefined` / `true` / `false`

**Engines:** all

`true` and `false` compile to the integers 1 and 0.

```gsc
main()
{
    a = undefined;
    b = true;
    c = false;
}
```

## 5.17 Empty array

**Engines:** all

`[]` creates a new empty array. Arrays are dynamic and double as string-keyed maps.

```gsc
main()
{
    level.players = [];
}
```

## 5.18 Array literal

**Engines:** `IW`

`[ a, b, c ]` builds an array and appends each element in order, giving keys `0 … n-1`. ARC
has no array literal — `[ 1, 2 ]` is a parse error there.

```gsc
main()
{
    weapons = [ "ak47_sp", "m4_sp", "usp_sp" ];
}
```

## 5.19 Array subscript

**Engines:** all

Integer or string keys. Reading a missing key yields `undefined`; writing one creates it.

```gsc
main()
{
    a = weapons[0];
    b = level.teams["allies"];
    level.spawns["axis"][3] = self;
}
```

## 5.20 Field access

**Engines:** all

Fields on entities and structs. Reading an unset field yields `undefined`.

```gsc
main()
{
    self.health      = 100;
    level.round.time = 90;
}
```

## 5.21 `.size`

**Engines:** all

Element count of an array, or character count of a string.

```gsc
main()
{
    n = level.players.size;
    m = "hello".size;      // 5
}
```

## 5.22 `level` / `game` / `self` / `anim` / `world` / `classes`

**Engines:** as marked

| Name | Engines | Meaning | Constraint |
| --- | --- | --- | --- |
| `level` | all | per-level global struct | must be followed by `.` |
| `game` | all | persists across level loads | must be followed by `[` |
| `self` | all | the entity the current function was called on | none |
| `anim` | all | animation-script global struct | must be followed by `.` |
| `world` | `t7` | world entity struct | none |
| `classes` | `t7` | class registry | none |

```gsc
main()
{
    level.players       = [];
    game["difficulty"]  = "hard";
    self.health         = 100;
    anim.notetracks     = [];
}
```

```gsc
// t7
function main()
{
    world.roundnumber = 1;
}
```

## 5.23 Function reference — `::`

**Engines:** `IW` `t6`

`::name` references a function in the current file (or a builtin); `path::name` references
one in another script. The result is a function pointer, usually passed around and later
invoked with `[[ ]]`.

```gsc
main()
{
    f = ::on_player_spawn;
    g = maps\_utility::waittill_dead;

    level thread run_callback( f );
}
```

On `t7` this form is rejected with `use '&' for function references`.

## 5.24 Function reference — `&`

**Engines:** `t7`

`&name` references a function in the current namespace; `&namespace::name` references one in
another.

```gsc
function main()
{
    f = &on_player_spawn;
    g = &util::waittill_dead;

    system::register( "zm", &__init__, undefined, undefined );
}
```

## 5.25 `thisthread`

**Engines:** `IW`

A handle to the currently running thread, for passing to functions that need to notify or
kill it.

```gsc
main()
{
    level thread watchdog( thisthread );
}
```

## 5.26 `new`

**Engines:** `t7`

Instantiates a class, running its `constructor`.

```gsc
function main()
{
    o_scene = new cScene();
}
```

---

# 6. Parameters

## 6.1 Plain parameters

**Engines:** all

Names only — no types.

```gsc
give_weapon( weapon, ammo )
{
    a = weapon;
}
```

## 6.2 Default values

**Engines:** `ARC`

A parameter may carry a default expression, used when the caller omits the argument.

```gsc
// t7
function get( kvp_value, kvp_key = "targetname" )
{
    return kvp_key;
}

function spawn( v_origin = ( 0, 0, 0 ), v_angles = ( 0, 0, 0 ) )
{
    return v_origin;
}
```

The `t6` front end accepts and compiles the same form.

## 6.3 Reference parameters

**Engines:** `t7`

`&name` passes the argument by reference, so the callee's writes are visible to the caller.

```gsc
function filter( &array, b_keep_keys )
{
    array = [];
}
```

## 6.4 Varargs

**Engines:** `t7`

`...` must be the last parameter. Extra arguments arrive in the implicit array `vararg`.

```gsc
function flagsys_wait_any_flag( &array, ... )
{
    foreach ( str_flag in vararg )
        a = str_flag;
}
```

---

# 7. Calls

## 7.1 Local call

**Engines:** all

An unqualified name resolves in this order: **builtin function or method**, then a function
declared in the same file, then a function from an included script. A builtin therefore
shadows a same-named local function.

```gsc
main()
{
    setup();
    give_weapon( "ak47_sp", 300 );
}
```

## 7.2 Far call

**Engines:** as marked

IW and `t6` qualify with a script path; `t7` qualifies with a namespace.

```gsc
// IW / t6 — path::function
main()
{
    maps\_utility::flag_wait( "start" );
    common_scripts\utility::spawn_tag_origin();
}
```

```gsc
// t7 — namespace::function
function main()
{
    util::wait_till( "start" );
    array::add( level.things, self, false );
}
```

## 7.3 Method call

**Engines:** all

An object expression followed by a call runs that function with `self` bound to the object.
There is no `.` or `->` for this; juxtaposition is the syntax.

**The call must begin on the same line as the start of the object expression** — otherwise
the parser reads it as a new statement and reports an error.

```gsc
main()
{
    self giveweapon( "ak47_sp" );
    level.player takeallweapons();
    self maps\_utility::waittill_dead();
}
```

## 7.4 `thread`

**Engines:** all

Starts the call on a new script thread and returns immediately. Works on plain calls, far
calls, method calls and pointer calls.

```gsc
main()
{
    thread watch_spawns();
    self thread maps\_utility::watch_death();
    thread [[ level.callback ]]( self );
}
```

## 7.5 `childthread`

**Engines:** `IW`

Like `thread`, but the new thread is killed when the parent thread ends.

```gsc
main()
{
    childthread common_scripts\utility::delaycall( 1, ::cleanup );
}
```

## 7.6 Pointer call `[[ ]]`

**Engines:** all

Invokes a function reference. Works standalone or as a method call, and combines with
`thread` (and `childthread` on IW).

```gsc
main()
{
    f = ::on_spawn;

    [[ f ]]();
    self [[ f ]]( 1, 2 );
    self thread [[ level.callback ]]();
}
```

## 7.7 `call [[ ]]`

**Engines:** `IW`

The explicit builtin-invocation form of a pointer call, used by stock code when the
reference may point at an engine builtin.

```gsc
main()
{
    self call [[ level.func ]]( level.args[0] );
}
```

## 7.8 `::name( … )`

**Engines:** `IW` `t6`

An immediately-invoked reference — equivalent to a plain local call, written with the
reference syntax.

```gsc
main()
{
    ::setup();
}
```

## 7.9 Member call `->`

**Engines:** `t7`

Calls a method on a class instance. The instance goes inside `[[ ]]`.

```gsc
function main()
{
    a_scene_ents = [[ _o_bundle ]]->get_ents();
    thread [[ scene() ]]->play();

    if ( [[ scene() ]]->allows_multiple() )
        a = 1;
}
```

---

# 8. Semantic notes

Not syntax, but they decide whether syntactically valid code compiles.

## 8.1 Lvalues

**Engines:** all

Assignment targets, `++`/`--` operands and tuple elements must be a local variable, a field,
or an array element. An array element is only an lvalue when nothing in its chain is a call:
`foo()[0] = 1;` is rejected.

## 8.2 Statement expressions

**Engines:** all

A statement-level expression must be a call, a method call, an assignment, or an
increment/decrement. `1;` and `a + b;` are rejected.

## 8.3 `waittill` parameters

**Engines:** `IW`

Only plain identifiers. `self waittill( "damage", undefined, amount );` parses but does not
compile.

## 8.4 `continue` in `switch`

**Engines:** all

`continue` is only valid inside a loop; a `switch` body alone does not accept it.

## 8.5 Same-line method calls

**Engines:** all

```gsc
main()
{
    self
        foo();   // error: parsed as two statements
}
```

## 8.6 Identifiers that look like keywords

**Engines:** `ARC`

`assert`, `assertex`, `assertmsg`, `breakpoint`, `call`, `childthread`, `istrue` and
`thisthread` are IW keywords with no ARC counterpart. On ARC they lex as ordinary names, so
`childthread foo();` parses as a method call on a variable named `childthread` and fails
with `local variable 'childthread' not found`. The same applies to `class`, `function`,
`new`, `var`, `world` and `classes` on `t6`.

## 8.7 Not implemented

- IW hash literals (`#"string"`, `iw9`) are recognized by the engine but not by this front end.
- `t7` has no compiler or assembler — parse, disassemble and decompile only.
- `t8`, `t9` and `jup` are refused by every mode.
- `..` lexes in both families but has no grammar rule.
- `#insert path.gsh;` — the stock `t7` spelling with the extension — is rejected; write the
  path without it.
