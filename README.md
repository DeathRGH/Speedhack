# Speedhack
Universal speedhack for PlayStation4 games.

## How It Works
The project compiled to a elf file which can be injected into any game process using any elf loader that returns the entry point such as [Frame4](https://github.com/DeathRGH/frame4).
The elf hooks the supported tick functions in the scope of the game and advances the tick faster/slower depending on the set speed.

## Supported Tick Functions
`sceKernelReadTsc`<br>
`sceKernelGetProcessTimeCounter`

## Compiling
The project makes use of the Post-Build-Event in Visual Studio.<br/>
Make sure you have the linux sub system for windows (wsl) installed.<br/>
If you have issues compiling with older version of visual studio (pre 2022) try to replace the path in the Post-Build-Event with the following:
```
powershell.exe /c C:\Windows\sysnative\wsl.exe
```

## Usage
You can directly write to the value `writeableSetupValue`.<br>
There is currently no way to export this so compiling with symbols will make it easier to find the value offset in the elf.
The offset might change on rebuilding the elf.<br>
It can be found easily by loading the built elf in ida and look for symbolic name `writeableSetupValue`.<br>
Make sure you load it as a standard elf, the ps4 ida loaders usually dont load symbols!<br>
<br>
The offset for the 1.0 release is `0x964`.

C# Example using [Frame4](https://github.com/DeathRGH/frame4).
```cs
ulong entry = ps4.LoadElf(pid, $@"{Application.StartupPath}\files\Speedhack.elf");
ulong valueAddress = entry + 0x964; // fixed offset in elf

ps4.WriteSingle(processID, valueAddress, 1.0f);
```

## Credits
- TLH
