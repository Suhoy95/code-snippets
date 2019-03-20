#!/usr/bin/env python
import logging
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--log', default="WARNING")
args = parser.parse_args()

numeric_level = getattr(logging, args.log.upper(), None)
if not isinstance(numeric_level, int):
    raise ValueError('Invalid log level: %s' % loglevel)

logging.basicConfig(
        level=numeric_level,
        filename="example.log",
        format='%(asctime)s:%(levelname)s:%(message)s')

#logging.basicConfig(filename='exmple.log',level=logging.DEBUG)
logging.debug('This message should go to the log file')
logging.info('So should this')
logging.warning('And this, too')

