#!/usr/bin/env python3


import pandas as pd
import matplotlib.pyplot as plt

# data preparation for omp result
df = pd.read_json('out_runtime_481268.json')
# the 1st 2 lines of the json file originally contains a redundant command output, so
# delete them beforehand

# plot for float
ax = df.plot(x="Number of processors", y="Runtime (seconds)", grid=True, logx=True, style=".-")
ax.set_ylabel("Runtime (seconds)")
ax.set_xlabel("used processors")
ax.set_title("performance of n=10^6 for varying numbers of processors")
plt.savefig("runtime_proc", bbox_inches='tight')
