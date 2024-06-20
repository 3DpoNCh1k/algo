from pathlib import Path
import re


def submission_command(args):
    filename = args.filename
    text = open(filename, "r").read()
    file_path = Path(filename)

    folder = file_path.parent

    submission_text = ""
    last_index = 0
    for match in re.finditer(r'#include "(?P<path>.*)"', text):
        include_filename = match.group("path")
        include_file_text = open(folder / include_filename, "r").read()
        submission_text += text[last_index : match.start()]
        submission_text += include_file_text
        last_index = match.end()
    submission_text += text[last_index:]

    # remove #pragma once and #include "../header.hpp"
    submission_text = re.sub("#pragma once", "", submission_text)
    submission_text = re.sub('#include "../header.hpp"', "", submission_text)

    name = file_path.name
    new_folder_path = Path(".") / "submit" / folder.name
    new_folder_path.mkdir(parents=True, exist_ok=True)
    open(new_folder_path / f"submission_{name}", "w").write(submission_text)
