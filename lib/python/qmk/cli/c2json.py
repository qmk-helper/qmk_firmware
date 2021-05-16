"""Generate a keymap.json from a keymap.c file.
"""
import json

from argcomplete.completers import FilesCompleter
from milc import cli

import multiprocessing
import time

import qmk.keymap
import qmk.path
from qmk.json_encoders import InfoJSONEncoder
from qmk.keyboard import keyboard_completer, keyboard_folder



@cli.argument('--no-cpp', arg_only=True, action='store_false', help='Do not use \'cpp\' on keymap.c')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='The keyboard\'s name')
@cli.argument('-km', '--keymap', arg_only=True, required=True, help='The keymap\'s name')
@cli.argument('filename', arg_only=True, completer=FilesCompleter('.c'), help='keymap.c file')
@cli.subcommand('Creates a keymap.json from a keymap.c file.')
def c2json(cli):
    """Generate a keymap.json from a keymap.c file.

    This command uses the `qmk.keymap` module to generate a keymap.json from a keymap.c file. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    if cli.args.filename != '-':
        cli.args.filename = qmk.path.normpath(cli.args.filename)

        # Error checking
        if not cli.args.filename.exists():
            cli.log.error('C file does not exist!')
            cli.print_usage()
            return False

    # Environment processing
    if cli.args.output == ('-'):
        cli.args.output = None

    # Parse the keymap.c
    keymap_json = qmk.keymap.c2json(cli.args.keyboard, cli.args.keymap, cli.args.filename, use_cpp=cli.args.no_cpp)

    # Generate the keymap.json
    try:
        keymap_json = qmk.keymap.generate_json(keymap_json['keymap'], keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'])
    except KeyError:
        cli.log.error('Something went wrong. Try to use --no-cpp.')
        return False

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.parent / (cli.args.output.name + '.bak'))
        cli.args.output.write_text(json.dumps(keymap_json, cls=InfoJSONEncoder))

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(json.dumps(keymap_json))


@cli.subcommand('Generates all keymap json for all keyboards')
def create_all_keymaps(cli):
    print("Collecting keyboards")
    start = time.time()
    #keyboards = ["zvecr/zv48/f411"]
    keyboards = qmk.cli.list.keyboards.list_keyboards("")
    end_keyboards = time.time()
    print("Collected keyboards in " + str(end_keyboards - start))
    print("Converting keymaps")

    if(keyboards):
        pool = multiprocessing.Pool()
        pool.map(create_keymaps, keyboards)
        pool.close()
    # if(keyboards):
    #     for keyboard in keyboards:
    #         create_keymaps(keyboard)

    end = time.time()
    print(end - start)
    print("Converted keymaps in " + str(end - end_keyboards))
    print("Total time: " + str(end - start))


def create_keymaps(keyboard):
    cli.log.info(keyboard)
    keymaps = qmk.keymap.list_keymaps(keyboard)

    if(keymaps):
        # print(keymaps)
        for keymap in keymaps:
            print(keymap)
            keymap_path = qmk.path.normpath(keymap["path"] + "/keymap.c")
            if not keymap_path.exists():
                # cli.log.error(keyboard + " | " + keymap["name"] + ': C file does not exist')
                keymap["error"] = "No C file"
                continue

            try:
                keymap_json = qmk.keymap.c2json(keyboard, keymap['name'], keymap_path, use_cpp=True)
            except UnicodeDecodeError:
                # cli.log.error(keyboard + " | " + keymap["name"] + ': Unable to decode unicode')
                keymap["error"] = "Unicode Decode Error"
                continue

            try:
                keymap_json = qmk.keymap.generate_json(  keymap_json['keymap'], keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'])
            except KeyError:
                # cli.log.warning(keyboard + " | " + keymap["name"] + ': Something went wrong. Retrying with --no-cpp')
                keymap["no-cpp"] = True
                try:
                    try:
                        keymap_json = qmk.keymap.c2json(keyboard, keymap['name'], keymap_path, use_cpp=False)
                    except UnicodeDecodeError:
                        # cli.log.error(keyboard + " | " + keymap["name"] + ': Unable to decode unicode')
                        keymap["error"] = "Unicode Decode Error"
                        continue

                    keymap_json = qmk.keymap.generate_json( keymap_json['keymap'],keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'])
                except KeyError:
                    # cli.log.error(keyboard + " | " + keymap["name"] + ': Something went wrong. Failed on keymap')
                    keymap["error"] = "Unknown Error"
                    continue
            output_path = qmk.path.normpath("keymaps/" + keyboard + "/" + keymap["name"] + ".keymap.json")
            if output_path:
                output_path.parent.mkdir(parents=True, exist_ok=True)
                output_path.write_text(json.dumps(keymap_json))
                # cli.log.info(keyboard + " | " + keymap["name"] + ': Wrote to %s.', output_path)
        summary_path = qmk.path.normpath("keymaps/" + keyboard + "/" + "keymaps.json")
        if summary_path:
            summary_path.parent.mkdir(parents=True, exist_ok=True)
            summary_path.write_text(json.dumps(keymaps))
