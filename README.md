# Purdue Robomasters Control Base Template
This repository contains the shared control code between Purdue Robomasters robots.

# Table of Contents
- [Repository Initialization](https://github.com/RoboMaster-Club/Control_Base_Template/tree/main?tab=readme-ov-file#repository-initialization-guide)
- [VSCode Environment Setup](https://github.com/RoboMaster-Club/Control_Base_Template/tree/main?tab=readme-ov-file#vscode-environment-setup)
- [Development Conventions](https://github.com/RoboMaster-Club/Control_Base_Template/tree/main?tab=readme-ov-file#development-conventions)

## Repository Initialization Guide
``` bash
git clone https://github.com/RoboMaster-Club/Control_Base_Template.git
cd Control_Base_Template
git submodule update --init
```

## VSCode Environment Setup
### Install tools
Download VSCode from [here](https://code.visualstudio.com/download)

**Windows**
- Download MSYS2 from [here](https://www.msys2.org/)
- The default installation path is `C:\msys64`, run `C:\msys64\msys2.exe`.
- Install OpenOCD, arm-none-eabi-gcc, and gdb-multiarch by running these commands in MSYS2 terminal.
```powershell
pacman -S mingw-w64-x86_64-openocd
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
pacman -S mingw-w64-x86_64-gdb-multiarch
```

**MacOS - Apple Silicon**
 - Install Arm embedded toolchain and OpenOCD and arm-none-eabi-gdb using [homebrew](https://docs.brew.sh/Installation).
```zsh
brew install gcc-arm-embedded  
brew install openocd
```

**Make sure to add necessary tools to VSCode settings.json** Alternatively, you can add them to PATH variable to allow them to be accessed globally.

### Set up VSCode
- Add the tool path for OpenOCD and make tools.

- Install the VSCode extension [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) to enable ARM microcontroller debugging.

- Add GDB path by opening your VSCode settings.json in VSCode and add the following to the end of the file.
   - **Windows:** ```"cortex-debug.gdbPath": "c:/msys64/mingw64/bin/gdb-multiarch.exe"```.
   - **MacOS:** ```"cortex-debug.gdbPath": "/opt/homebrew/bin/arm-none-eabi-gdb"```.

## How to use
### Building the Project
Open the Command Palatte in VSCode: [Ctrl+Shift+P].
Then, select **Tasks: Run Build Tasks** and pick the appropriate build task.
- **Windows:** build (Windows). 
- **MacOS:** build (Darwin).

You can use the shortcut [Ctrl+Shift+B] if you set it as the default build task.

### Debugging the Project
Navigate to [Run and Debug] in VSCode or press [Ctrl+Shift+D].
Select the appropriate launch configuration 
- **Windows:** cmsis-dap-debug (Windows)
- **MacOS:** cmsis-dap-debug (Darwin)

Click on the green play button or press [F5] to start debugging.

## Common Issues
### 1. Windows fails to initializing cmsis-dap debugger. 
Solution: Go to device manager and uninstall the usb device (probably having some error message in the list). Unplug and plug in the debugger again.

### 2. Tools (OpenOCD, make tools) not found
```
Failed to launch OpenOCD GDB Server:...
```
or
```
mingw32-make: The term 'mingw32-make' is not recognized as a name of a cmdlet, function, script file, or executable program.
Check the spelling of the name, or if a path was included, verify that the path is correct and try again.
```
**Solution1:**
Add openocd.exe to system environmental variable. If you followed the installation instruction in this README file, then OpenOCD should be install at default location `C:\msys64\mingw64\bin\openocd.exe`, for windows user. Add `C:\msys64\mingw64\bin` to system executable path.

**Solution2:**
If you don't want to mess with the system path, you could also add local openocd path in `.vscode/launch.json`. Add attribute `serverpath` by adding `"serverpath": "C:\\msys64\\mingw64\\bin\\openocd.exe"` in configuration.

**Note**
restarting vscode might be needed for new environment variable to take effect.

## Tips
### VSCode IntelliSense Configuration
```
"C_Cpp.default.compilerPath": "C:/msys64/mingw64/bin/arm-none-eabi-gcc.exe"
```
adding this would link the standard library header files, such as `stdint.h`, `stdlib.h`, `math.h`.

# Development Conventions
**All names must use snake_case.**

Variable names are all lowercase.
```c
 float example_float = 1.5f;
```

Macros should be all UPPERCASE.
```c
 #define EXAMPLE_MACRO 3.14f 
```

Function names should capitalize the first letter of each word.
```c
 float Example_Function() {}
```

Wrapper functions should capitalize the first word.
```c
 float MOTOR_Example_Function() {}
```

Struct names should capitalize the first letter of each word and end in _t. 
```c
 struct Example_Struct_t {} 
```

When using struct pointers, don't put a space between the arrow.
```c
 struct Example_Struct_t {
    int example_struct_member;
 } example_struct;
 // access member
 example_struct->example_struct_member;
```

Enum names should capitalized the first letter of each word and end in _e.
```c
 enum Example_Enum_e {};
```

In general, indent code blocks for functions and if statments as such, but for switches put cases in the same line.
```c
void Example_Func()
{
   if (some_condition)
   {
      switch(some_num)
      {
      case 0:
         break;
      default:
         break;
      }
   }
}
```

For multiline macros, indent as such:
```c
#define YOUR_MACRO        \
   {                      \
      FIRST_LINE = 0,     \
         SECOND_LINE = 1, \
         THIRD_LINE = 2,  \
   }
```
