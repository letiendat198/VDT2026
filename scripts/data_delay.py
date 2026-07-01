avg = 1

ship_recv = {}
ship_display = {}

with open("data_delay_5000.log", "r") as f:
    for line in f:
        if (not line.startswith("d") and not line.startswith("r")):
            continue
        ls = line.split(":", 1)
        print(ls)
        id = ls[0]
        millis = ls[1]
        id = id[1:].strip()
        if (line.startswith("r")):
            ship_recv[id] = int(millis.strip())
        else:
            ship_display[id] = int(millis.strip())

for id in ship_recv.keys():
    print(avg)
    avg = (avg + abs(ship_display[id] - ship_recv[id])) / 2

print("Average delay:", avg,"ms")
