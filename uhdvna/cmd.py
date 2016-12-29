import logging

import sys
import argparse

try:
    import coloredlogs
except ImportError:
    coloredlogs = None

from . import _control

log = logging.getLogger(__name__)


def main(args=sys.argv):
    p = argparse.ArgumentParser(
        description='USRP-based Vector Network Analyzer')
    p.add_argument('--verbose', action='store_true')

    opts = p.parse_args(args[1:])

    if coloredlogs:
        coloredlogs.install(level='DEBUG' if opts.verbose else 'INFO')
    else:
        logging.basicConfig(level=logging.DEBUG if opts.verbose else
                            logging.INFO)

    print("Hello result is: %s" % _control.hello())
