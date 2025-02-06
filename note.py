import random
import subprocess

inst_arr = []
failed_cases = []

for x in range(10000):
    number = 100  # Number of random numbers to generate
    limit = 699  # Instruction limit
    # Generate a unique list of 500 random numbers
    arr = random.sample(range(-10000000, 100000000), number)
    str_list = ' '.join(map(str, arr))

    # Run push_swap and capture its output
    proc2 = subprocess.run(f"./push_swap {str_list} | wc -l", shell=True, capture_output=True, text=True)
    proc = subprocess.run(f"./push_swap {str_list} | ./checker {str_list}", shell=True, capture_output=True, text=True)
    num_instructions = int(proc2.stdout.strip())
    # Check if sorting failed or exceeded the instruction limit
    print(f"Test {x}: {proc2.stdout} instructions")
    if "KO" in proc.stdout:
        print(f"❌ FAIL - Test {x}: {num_instructions} instructions")
        failed_cases.append(str_list)
    elif num_instructions > limit:
        print(f"❌ NOT LIMIT - Test {x}: {num_instructions} instructions")
        failed_cases.append(str_list)
    elif "ُError" in proc.stdout:
        print(f"❌ Error ")
    elif "OK" in proc.stdout:
        print(f"✅ PASS - Test {x}: {num_instructions} instructions")
    else:
        print(f"❌ FAIL - Test {x}: {num_instructions} instructions")
        failed_cases.append(str_list)
    inst_arr.append(num_instructions)

# Print summary
if not failed_cases:
    print("\n🎉 ALL TESTS PASSED!")
else:
    print("\n❌ FAILED CASES:")
    for case in failed_cases:
        print(case)

print("\n📊 Statistics:")
print(f"AVERAGE: {sum(inst_arr) / len(inst_arr):.2f}")
print(f"MAX: {max(inst_arr)}")
print(f"MIN: {min(inst_arr)}")
