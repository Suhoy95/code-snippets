#!/usr/bin/env python
import logging
import argparse
import sys

parser = argparse.ArgumentParser()
parser.add_argument("--log", default="WARNING")
args = parser.parse_args()

numeric_level = getattr(logging, args.log.upper(), None)
if not isinstance(numeric_level, int):
    raise ValueError("Invalid log level: %s" % args.log)

file_handler = logging.FileHandler(filename="log.txt")
stdout_handler = logging.StreamHandler(sys.stdout)

logging.basicConfig(
        level=numeric_level,
        # filename="log.txt",
        handlers=[file_handler, stdout_handler],
        format="%(asctime)s:%(levelname)s:%(message)s")

# logging.basicConfig(filename="log.txt",level=logging.DEBUG)
logging.debug("This message should go to the log file")
logging.info("So should this")
logging.warning("And this, too")
