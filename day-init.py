import pathlib
import shutil

number = input("Number? ")
puzzleName = input("Puzzle? ")

targetName = "{}_{}".format(number, puzzleName)
problemSolverName = "{}Solver".format(puzzleName)
inputFileName = "{}_Input.txt".format(puzzleName)

targetDir = pathlib.Path().cwd() / "calendar" / targetName
targetDir.mkdir(exist_ok=True)

targetSolverCpp = targetDir / "{}.cpp".format(problemSolverName)
targetSolverH = targetDir / "{}.h".format(problemSolverName)
targetMain = targetDir / "main.cpp"
targetInput = targetDir / inputFileName
targetCMake = targetDir / "CMakeLists.txt"

targetInput.open("w").close()

templateDir = pathlib.Path().cwd() / "template"

templateCMake = templateDir / "CMakeLists.txt"
templateMain = templateDir / "main.cpp"
templateCpp = templateDir / "TemplateSolver.cpp"
templateH = templateDir / "TemplateSolver.h"

def copy_replace(source, dest):
    with open(source, "rt") as source_file:
        with open(dest, "wt") as dest_file:
            for line in source_file:
                line = line.replace("||PROBLEM_SOLVER||", problemSolverName)
                line = line.replace("||DAY_TARGET_NAME||", targetName)
                line = line.replace("||DAY_TARGET_INPUT||", inputFileName)
                dest_file.write(line)

copy_replace(str(templateCMake), str(targetCMake))
copy_replace(str(templateMain), str(targetMain))
copy_replace(str(templateCpp), str(targetSolverCpp))
copy_replace(str(templateH), str(targetSolverH))

with open("CMakeLists.txt", "at") as root_cmake_file:
    root_cmake_file.write("\nadd_subdirectory(calendar/{})".format(targetName))