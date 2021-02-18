"""Plots strong and weak scaling for various programs, based off a single run.

Plots strong and weak scaling for:
- OpenMP pi
- MPI pi

This script can be adapted to produce scaling plots using multiple runs of different
sizes to generate error bars.

@author Akash Pallath
"""
import numpy as np
import matplotlib.pyplot as plt

prefixes = ["omp_pi", "mpi_pi"]

for prefix in prefixes:
    # Strong scaling
    f = open(prefix + "_strong_time.txt")
    procs = []
    times = []
    for line in f:
        toks = line.strip().split()
        if len(toks) == 1:
            procs.append(int(toks[0]))
        elif len(toks) == 2 and toks[0] == "real":
            mmss = toks[1].split("m")
            min = int(mmss[0])
            sec = float(mmss[1][:-1])
            tp = min * 60 + sec
            times.append(tp)

    # Check that p=1 data point exists
    assert(procs[0] == 1)

    procs = np.array(procs)
    times = np.array(times)

    # Scaling
    speedup = times[0] / times
    efficiency = times[0] / (procs * times)

    print(speedup, efficiency)

    # Plot
    fig, ax = plt.subplots(1, 2, figsize=(12, 6), dpi=150)
    ax[0].plot(procs, speedup, 'x-')
    ax[0].plot(procs, procs, '--')
    ax[0].set_xlabel(r"Number of processors, $p$")
    ax[0].set_ylabel(r"Strong speedup, $S_p$")
    ax[0].set_xlim([1, procs[-1]])
    ax[0].set_ylim([1, procs[-1]])

    ax[1].plot(procs, efficiency, 'x-')
    ax[1].plot(procs, np.ones(len(procs)), '--')
    ax[1].set_xlabel(r"Number of processors, $p$")
    ax[1].set_ylabel(r"Strong scaling efficiency, $E_s$")
    ax[1].set_xlim([1, procs[-1]])
    ax[1].set_ylim([0, 1])

    fig.suptitle("Intel Core i7 10700K @ 3.80 GHz, 8 cores, 16 threads")

    fig.savefig(prefix + "_strong_scaling.png")

    f.close()

    # Weak scaling
    f = open(prefix + "_weak_time.txt")
    procs = []
    times = []
    for line in f:
        toks = line.strip().split()
        if len(toks) == 1:
            procs.append(int(toks[0]))
        elif len(toks) == 2 and toks[0] == "real":
            mmss = toks[1].split("m")
            min = int(mmss[0])
            sec = float(mmss[1][:-1])
            tp = min * 60 + sec
            times.append(tp)

    # Check that p=1 data point exists
    assert(procs[0] == 1)

    procs = np.array(procs)
    times = np.array(times)

    # Scaling
    speedup = (times[0] * procs) / times
    efficiency = times[0] / times

    print(speedup, efficiency)

    # Plot
    fig, ax = plt.subplots(1, 2, figsize=(12, 6), dpi=150)
    ax[0].plot(procs, speedup, 'x-')
    ax[0].plot(procs, procs, '--')
    ax[0].set_xlabel(r"Number of processors, $p$")
    ax[0].set_ylabel(r"Weak speedup, $S_w$")
    ax[0].set_xlim([1, procs[-1]])
    ax[0].set_ylim([1, procs[-1]])

    ax[1].plot(procs, efficiency, 'x-')
    ax[1].plot(procs, np.ones(len(procs)), '--')
    ax[1].set_xlabel(r"Number of processors, $p$")
    ax[1].set_ylabel(r"Weak scaling efficiency, $E_w$")
    ax[1].set_xlim([1, procs[-1]])
    ax[1].set_ylim([0, 1])

    fig.suptitle("Intel Core i7 10700K @ 3.80 GHz, 8 cores, 16 threads")

    fig.savefig(prefix + "_weak_scaling.png")
