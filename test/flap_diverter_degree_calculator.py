start = 38

distance = 40
num_steps = 18
step = distance/(num_steps-1)
output = []

for x in range(num_steps):
  output.append(round(start+x*step))

print(output)