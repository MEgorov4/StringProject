import os
import sys
import shutil
import subprocess

BUILD_DIR = "build"

def clear():
    if os.path.exists(BUILD_DIR):
        print("===> Removing build/")
        shutil.rmtree(BUILD_DIR)
    os.makedirs(BUILD_DIR)
    print("===> build/ folder recreated")

def generate(with_compile_commands=False):
    print("===> Generating CMake project into build/")
    os.makedirs(BUILD_DIR, exist_ok=True)

    cmake_cmd = ["cmake", "-S", ".", "-B", BUILD_DIR]
    if with_compile_commands:
        cmake_cmd.append("-DCMAKE_EXPORT_COMPILE_COMMANDS=ON")

    subprocess.run(cmake_cmd, check=True)

    if with_compile_commands:
        src = os.path.join(BUILD_DIR, "compile_commands.json")
        if os.path.exists(src):
            shutil.copy(src, ".")

def main():
    if len(sys.argv) < 2:
        print("Flags:")
        print("  -g      generate cmake (no compile_commands)")
        print("  -gcc    generate cmake with compile_commands.json")
        print("  -c      clear build/")
        sys.exit(1)

    for arg in sys.argv[1:]:
        if arg == "-g":
            generate(with_compile_commands=False)
        elif arg == "-gcc":
            generate(with_compile_commands=True)
        elif arg == "-c":
            clear()
        else:
            print(f"Unknown flag: {arg}")
            sys.exit(1)

if __name__ == "__main__":
    main()
