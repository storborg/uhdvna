import logging

import sys
import argparse

try:
    import coloredlogs
except ImportError:
    coloredlogs = None

from . import VNA

log = logging.getLogger(__name__)


def main(args=sys.argv):
    p = argparse.ArgumentParser(
        description='USRP-based Vector Network Analyzer')
    p.add_argument('--verbose', action='store_true')
    p.add_argument('--uhdargs', default='')

    opts = p.parse_args(args[1:])

    if coloredlogs:
        coloredlogs.install(level='DEBUG' if opts.verbose else 'INFO')
    else:
        logging.basicConfig(level=logging.DEBUG if opts.verbose else
                            logging.INFO)

    log.info("Initializing VNA with UHD args: [%s]", opts.uhdargs)
    vna = VNA(opts.uhdargs)

    log.info("Sampling point at 2.4GHz with 0dBm.")
    value = vna.point(2.4e9, 0)

    log.info("Value: %s", value)
