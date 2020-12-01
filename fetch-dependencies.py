import os.path
import pathlib
import subprocess
import json

is_on_windows = os.name == "nt"

vcpkg_dir = pathlib.Path().cwd() / "vcpkg"
vcpkg_exe = vcpkg_dir / ("vcpkg.exe" if is_on_windows else "vcpkg")
vcpkg_bootstrap = vcpkg_dir / ("bootstrap-vcpkg.bat" if is_on_windows else "bootstrap-vcpkg.sh")

def is_vcpkg_initialized():
    return vcpkg_exe.is_file()

if not is_vcpkg_initialized():
    print("Initializing vcpkg")
    subprocess.check_call(str(vcpkg_bootstrap))

dependencies_root = { }

with open("dependencies.json") as deps_file:
    dependencies_root = json.load(deps_file)

for dependency in dependencies_root["dependencies"]:
    print("Installing {0}...".format(dependency["name"]))
    subprocess.call([ str(vcpkg_exe), "install", dependency["VCPKG-ID"] ])