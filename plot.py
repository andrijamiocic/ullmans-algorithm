import os
import matplotlib.pyplot as plt
import numpy as np

g_n_list = [20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40]
gh_ratio = 0.25
g_p = 0.3
h_p = 0.2

TIMEOUT_VAL = 60000000 

dfs_times = []
ullman_times = []
focus_times = []
cm_times = []

for g_n in g_n_list:
    def load_mean_time(algorithm_id):
        filename = f"rezultati/directed_{algorithm_id}_{g_n}_{gh_ratio:.6f}_{g_p:.6f}_{h_p:.6f}"
        
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            if data.size == 0:
                return 0
            if data.ndim == 0:
                data = np.array([data])
            data[data == -1] = np.nan
            
            return np.nanmean(data)
        return np.nan

    dfs_times.append(load_mean_time(1))
    ullman_times.append(load_mean_time(2))
    focus_times.append(load_mean_time(3))
    cm_times.append(load_mean_time(4))

plt.figure(figsize=(8, 5))
plt.plot(g_n_list, dfs_times, label='DFS', marker='o')
plt.plot(g_n_list, ullman_times, label='Ullman', marker='s')
plt.plot(g_n_list, focus_times, label='FocusSearch', marker='d')
plt.plot(g_n_list, cm_times, label='Čibej-Mihelič', marker='^')

plt.xlabel(r'Broj vrhova grafa G ($g\_n$)')
plt.ylabel(r'Prosječno vrijeme izvođenja ($\mu s$)')
plt.title(f'Usporedba algoritama (gh_ratio={gh_ratio}, g_p={g_p}, h_p={h_p})')
plt.legend()
plt.grid(True)
#plt.yscale('log') 

plt.savefig('graf_usporedba_direktni.pdf', format='pdf', bbox_inches='tight')
plt.show()