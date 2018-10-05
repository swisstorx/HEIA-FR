#!/bin/env python3

""" simple.py

Run single processes and prevent simple interruption. The goal of this program
is to make experiments with Linux process management.
"""

# Written in 2013 by Jacques Supcik <jacques.supcik@hefr.ch>
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# See <http://creativecommons.org/publicdomain/zero/1.0/>.

__author__ = 'Jacques Supcik'

import os
import signal
import time


def handler(sig_nr, stack_frame):
    print("Nice try with signal {sig}, but I am still running!".format(
        sig=sig_nr
    ))


def main():
    print("Hello. I am the process with PID {pid}. Can you stop me?".format(
        pid=os.getpid()
    ))

    for s in range(1,32):
        try:
            signal.signal(s, handler)
        except Exception:
            pass

    while True:
        time.sleep(5)
        print("I am still alive")


if __name__ == "__main__":
    main()
