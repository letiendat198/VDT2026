avg = 1

ship_recv = {}
ship_display = {}

with open("data_delay_5000.log", "r") as f:
    for line in f:
        if (not line.startswith("d") and not line.startswith("r")):
            continue
        ls = line.split(":", 1)
        # print(ls)
        id = ls[0]
        millis = ls[1]
        id = id[1:].strip()
        if (line.startswith("r")):
            ship_recv[id] = int(millis.strip())
        else:
            ship_display[id] = int(millis.strip())

max = 0
min = 99999999

for id in ship_recv.keys():
    diff = abs(ship_display[id] - ship_recv[id])
    if diff > max:
        max = diff
    if diff < min:
        min = diff
    avg += diff

avg /= len(ship_recv)

print("Average delay:", avg,"ms")
print("Max", max, "ms")
print("Min", min, "ms")
