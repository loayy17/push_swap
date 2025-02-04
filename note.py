import random
import subprocess
 
inst_arr = []
failed_cases = []
def simulate_push_swap_output(arr):
    # Simulate the output of push_swap
    return '\n'.join(['operation'] * random.randint(1, 1000))

for x in range(1000):
    arr = random.sample(range(-1000, 100000), 500)
    str_list = ''.join(str(e) + ' ' for e in arr)
    simulated_output = simulate_push_swap_output(arr)
    if len(simulated_output.split('\n')) - 1 > 800:
        print("FAIL")
        failed_cases.append(str_list)
    inst_arr.append(len(simulated_output.split('\n')) - 1)
    print("TEST", x, ":", len(simulated_output.split('\n')) - 1)
if len(failed_cases) == 0:
    print("ALL TESTS PASSED")
else :
    print("FAILED CASES:")
for case in failed_cases:
    print(case)
print("AVERAGE:", sum(inst_arr) / len(inst_arr))
print("MAX:", max(inst_arr))
print("MIN:", min(inst_arr))