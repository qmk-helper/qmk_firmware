"""List the keyboards currently defined within QMK
"""
<<<<<<< HEAD
# We avoid pathlib here because this is performance critical code.
import glob
import json
import os
from pathlib import Path

import qmk.path
=======
>>>>>>> master
from milc import cli

import qmk.keyboard


def locate_info_json(keyboard):
    """Returns the path to a keymap for a specific keyboard.
    """
    if not qmk.path.is_keyboard(keyboard):
        return
        # raise KeyError('Invalid keyboard: ' + repr(keyboard))

    # Check the keyboard folder first, last match wins
    checked_dirs = ''
    info_json_path = ''

    for dir in keyboard.split('/'):
      
        if checked_dirs:
            checked_dirs = '/'.join((checked_dirs, dir))
        else:
            checked_dirs = dir

    
        keyboard_dir = Path('keyboards') / checked_dirs

     

        if (keyboard_dir / 'info.json').exists():           
            info_json_path = keyboard_dir / 'info.json'     
       
    if info_json_path:
        return str(info_json_path)
  

@cli.subcommand("List the keyboards currently defined within QMK")
def test(cli):
    print(locate_info_json("preonic/rev3"))

@cli.subcommand("List the keyboards currently defined within QMK")
def list_keyboards(cli):
    """List the keyboards currently defined within QMK
    """
<<<<<<< HEAD
    # find everywhere we have rules.mk where keymaps isn't in the path
    paths = [path for path in glob.iglob(KB_WILDCARD, recursive=True) if 'keymaps' not in path]

    # Extract the keyboard name from the path and print it
    keyboards = sorted(map(find_name, paths))

    # print("test a")
    test = [{"name": keyboard,"path":locate_info_json(keyboard)} for keyboard in keyboards]     
    # print("test s")
    print(json.dumps(test))
    # print("test e")
   
    # for keyboard_name in keyboards:
    #     print(keyboard_name)
    #     print(locate_info_json(keyboard_name))
    return keyboards
=======
    for keyboard_name in qmk.keyboard.list_keyboards():
        print(keyboard_name)
>>>>>>> master
