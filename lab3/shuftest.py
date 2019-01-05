from argparse import ArgumentParser
parser = ArgumentParser()
parser.add_argument("filename", action="store", nargs='?', default="")
parser.add_argument("-i", "--input-range", action="store", nargs=1, dest="input_range", help="""treat each number LO through HI as an input line""")
parser.add_argument("-n", "--head-count", action="store", dest="count", help="output at most COUNT lines")
parser.add_argument("-r", "--repeat", action="store_true", dest="repeat", help="output lines can be repeated")
options = parser.parse_args("-i 1-10".split())
ops2 = parser.parse_args("-n 10".split())
