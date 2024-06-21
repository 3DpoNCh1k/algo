from pathlib import Path
import sys
import os

print(sys.path)
print(os.getcwd())

from rithm.source_files import *

def main():
    print("Hello!")
    paths = list(Path(".").iterdir())
    print(paths)
    # for p in paths:
    #     if p.is_file():
    #         print(os.path.splitext(p))
    #         # print(SourceFile(p).extension)
    #         # print(SourceFile(p).text)
    #         CppFile(p)
    p = Path("./tests/run.cpp")
    cpp_file = CppFile(p)

if __name__ == "__main__":
    main()