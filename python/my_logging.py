import logging


logging.basicConfig(
    format='%(levelname)s:%(name)s:%(asctime)s:%(message)s',
    level=logging.DEBUG,
)
logging.warning('Watch out!')  # will print a message to the console
logging.info('I told you so')  # will not print anything
