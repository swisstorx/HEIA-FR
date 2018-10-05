#!/bin/env python3

""" multi.py

Run multiple processes (fork). The goal of this program is to make
experiments with Linux process management.
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
import random


def handler(sig_nr, stack_frame):
    print("Nice try with signal {sig}, but I am still running!".format(
        sig=sig_nr
    ))


def child():
    random.seed(time.time() + os.getpid())
    time.sleep(5)
    while True:
        time.sleep(random.randrange(2, 5))
        print("...me too! And I am {pid}, in group {pgid} and son of {ppid}"\
            .format(pid=os.getpid(), pgid=os.getpgid(0),  ppid=os.getppid()))


def main():
    for s in range(1, 32):
        try:
            signal.signal(s, handler)
        except Exception:
            pass

    print("Hello. I am the process with PID {pid}. Can you stop me?"\
        .format(pid=os.getpid()))

    for i in range(0, 3):
        if os.fork() == 0:
            child()

    while True:
        time.sleep(5)
        print("I am still alive. And by the way, I am in the group {pgid}"\
            .format(pgid=os.getpgid(0)))


if __name__ == "__main__":
    main()