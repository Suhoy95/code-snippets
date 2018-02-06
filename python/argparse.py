import argparse


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--filename', type=str, required=True)
    return parser.parse_args()
