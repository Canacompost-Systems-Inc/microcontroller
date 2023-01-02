start = 60 # leftmost value
distance = 65 # distance between two end positions of flap
num_steps = 20 # how many states we want

step = distance/(num_steps-1)
output = []

for x in range(num_steps):
  output.append(round(start+x*step))

print(output)