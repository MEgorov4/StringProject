import sys
import subprocess
import os

BAT_DIR = os.path.join(os.path.dirname(__file__), "automation")

flags = {
    "-b": "build.bat",
    "-g": "gen.bat",
    "-r": "run.bat",
    "-rt": "runt.bat",
    "-c": "clear.bat"
}

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} {' '.join(flags.keys())}")
    sys.exit(1)

for arg in sys.argv[1:]:
    bat_name = flags.get(arg)
    if not bat_name:
        print(f"Invalid flag: {arg}")
        sys.exit(1)

    bat_path = os.path.join(BAT_DIR, bat_name)
    if not os.path.exists(bat_path):
        print(f"Command file not exists: {bat_path}")
        sys.exit(1)

    print(f"Running {bat_name}...")
    result = subprocess.run([bat_path], shell=True)
    if result.returncode != 0:
        print(f"Command {bat_name} failed with exit code {result.returncode}")
        sys.exit(result.returncode)

