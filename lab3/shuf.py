#!/usr/bin/python

"""
Python2 implementation of GNU's shuf.c 
"""

import random, sys, string
from argparse import ArgumentParser, ArgumentError

class shuf:
    def __init__(self, filename=""):
        if filename == "-" or filename == "":
            self.lines = sys.stdin.readlines() 
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def chooseline(self):
        ret = random.choice(self.lines)


def main():
    version_msg = "Python Port of shuf.c 1.0"
    usage_msg = """shuf [OPTION]... [FILE]
    or: shuf -e [OPTION]... [ARG]...
    or: shuf -i LO-HI [OPTION]...

    Output shuffled lines from FILE."""
    desc_msg = """Write a random permutation of the input lines to standard 
    output."""
    
    parser = ArgumentParser(usage=usage_msg, description=desc_msg)


    # Add support for shuf options
    parser.add_argument("filename", action="store", 
                        nargs='?', default="")

    # --input-range (-i)
    #   Treat each number LO through HI as an input line
    #   shuf -i LO-HI [OPTION]...
    parser.add_argument("-i", "--input-range", action="store",
                        nargs=1, dest="input_range",
                        help="""treat each number LO through HI as 
                        an input line""")

    # --head-count (-n) = COUNT
    #   output at most COUNT lines
    parser.add_argument("-n", "--head-count", action="store",
                        dest="count",
                        help="output at most COUNT lines")

    # --repeat (-r)
    #   Output lines can be repeated
    parser.add_argument("-r", "--repeat", action="store_true",
                        dest="repeat",
                        help="output lines can be repeated")

    # --help
    #   Display this help and exit
    # parser.add_argument("--help", action="help")

    # Possible Options: input_range, count, repeat, help
    options = parser.parse_args(sys.argv[1:])

    #
    # Argument Error Checking
    #
    input_range_op = False
    head_count_op = False
    repeat_op = False
    numlines = sys.maxsize

    # Check for input range errors
    if bool(options.input_range):
        # print("-i option activated")
        input_range_op = True
        if len(options.input_range) > 1: 
            parser.error("multiple -i options specified")
        if options.input_range[0] == '':
            parser.error("option requires an argument -- 'i'")
        if options.filename:
            parser.error("extra operand '{0}'".
                         format(options.filename))
        try:
            input_range = options.input_range[0].split("-")
            assert(len(input_range) == 2)
            LO_INPUT = int(input_range[0])
            HI_INPUT = int(input_range[1])
            assert(HI_INPUT > LO_INPUT)
        except:
            parser.error("invalid input range: '{0}'". 
                         format(options.input_range[0]))

    # Check for --head-count errors
    if bool(options.count):
        # print("-i option activated")
        head_count_op = True
        try:
            head_count = int(options.count)
            assert(head_count >= 0)
            numlines = head_count
        except:
            parser.error("invalid line count: '{0}'".format(options.count))

    # Check for --repeat errors
    if options.repeat:
        # print("-r option activated")
        repeat_op = True

    # Shuffle the input and print to stdout
    input_file = options.filename

    try:
        if input_range_op:
            output_lines = list(range(LO_INPUT, HI_INPUT + 1))
            for i in range(len(output_lines)):
                output_lines[i] = str(output_lines[i]) + '\n'
        else:
            generator = shuf(input_file)
            output_lines = generator.lines

        if not head_count_op and not repeat_op:
            numlines = len(output_lines)
        index = 0
        while (index < numlines) and (len(output_lines) > 0):
            out = random.choice(output_lines)
            if not repeat_op:
                output_lines.remove(out)
            sys.stdout.write(out)
            index += 1
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()