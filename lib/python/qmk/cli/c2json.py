"""Generate a keymap.json from a keymap.c file.
"""
import json
import sys

import qmk.cli.list.keyboards
import qmk.keymap
import qmk.path
from milc import cli


@cli.argument('--no-cpp', arg_only=True, action='store_false', help='Do not use \'cpp\' on keymap.c')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, required=True, help='The keyboard\'s name')
@cli.argument('filename', arg_only=True, help='keymap.c file')
@cli.subcommand('Creates a keymap.json from a keymap.c file.')
def c2json(cli):
    """Generate a keymap.json from a keymap.c file.

    This command uses the `qmk.keymap` module to generate a keymap.json from a keymap.c file. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    cli.args.filename = qmk.path.normpath(cli.args.filename)

    # Error checking
    if not cli.args.filename.exists():
        cli.log.error('C file does not exist!')
        cli.print_usage()
        exit(1)

    if str(cli.args.filename) == '-':
        # TODO(skullydazed/anyone): Read file contents from STDIN
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
        exit(1)

    # Environment processing
    if cli.args.output == ('-'):
        cli.args.output = None

    # Parse the keymap.c
    try:
        keymap_json = qmk.keymap.c2json(cli.args.keyboard, cli.args.filename, use_cpp=cli.args.no_cpp)
    except UnicodeDecodeError:
        cli.log.error('The file encoding is invalid')
        sys.exit(1)

    # Generate the keymap.json
    try:
        keymap_json = qmk.keymap.generate(keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'], type='json')
    except KeyError:        
        cli.log.error('Something went wrong. Try to use --no-cpp.')
        sys.exit(1)

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(json.dumps(keymap_json))

        if not cli.args.quiet:
            cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(json.dumps(keymap_json))


@cli.subcommand('Generates all keymap json for all keyboards')
def create_all_keymaps(cli):  
    # keyboards= ["zvecr/zv48/f411"]
    keyboards= qmk.cli.list.keyboards.list_keyboards("")
    if(keyboards):        
        for keyboard in keyboards:            
            keymaps = qmk.keymap.list_keymaps(keyboard)

            if(keymaps):
                # print(keymaps)
                for keymap in keymaps:             
                    # print(keymap)     
                    keymap_path= qmk.path.normpath(keymap["path"]+"/keymap.c")
                    if not keymap_path.exists():
                        cli.log.error(keyboard+" | "+keymap["name"]+': C file does not exist')
                        keymap["error"]="No C file"
                        continue
                                            
                    try:
                        keymap_json = qmk.keymap.c2json(keyboard, keymap_path, use_cpp=True)
                    except UnicodeDecodeError:
                        cli.log.error(keyboard+" | "+keymap["name"]+': Unable to decode unicode')
                        keymap["error"]="Unicode Decode Error"
                        continue
                                            
                    try:
                        keymap_json = qmk.keymap.generate(keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'], type='json')
                    except KeyError:        
                        cli.log.warning(keyboard+" | "+keymap["name"]+': Something went wrong. Retrying with --no-cpp')
                        keymap["no-cpp"]=True
                        try:
                            try:
                                keymap_json = qmk.keymap.c2json(keyboard, keymap_path, use_cpp=False)
                            except UnicodeDecodeError:
                                cli.log.error(keyboard+" | "+keymap["name"]+': Unable to decode unicode')
                                keymap["error"]="Unicode Decode Error"
                                continue
                                     
                            keymap_json = qmk.keymap.generate(keymap_json['keyboard'], keymap_json['layout'], keymap_json['layers'], type='json')
                        except KeyError:        
                            cli.log.error(keyboard+" | "+keymap["name"]+': Something went wrong. Failed on keymap')
                            keymap["error"]="Unknown Error"
                            continue
                            
                    keymap_json['keymap']= keymap['name']
                    output_path=qmk.path.normpath("keymaps/"+keyboard+"/"+keymap["name"]+".keymap.json")
                    if output_path:
                        output_path.parent.mkdir(parents=True, exist_ok=True)                       
                        output_path.write_text(json.dumps(keymap_json))                       
                        cli.log.info(keyboard+" | "+keymap["name"]+': Wrote to %s.', output_path)                
                summary_path=qmk.path.normpath("keymaps/"+keyboard+"/"+"keymaps.json")
                if summary_path:
                    summary_path.parent.mkdir(parents=True, exist_ok=True)                       
                    summary_path.write_text(json.dumps(keymaps))
