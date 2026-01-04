import csv
import matplotlib.pyplot as plt

prices = []

with open("../data/prices.csv", newline="") as f:
    reader = csv.DictReader(f)
    for row in reader:
        if int(row["price"]) != 0:
            prices.append(int(row["price"]) / 10_000)

plt.figure()
plt.plot(prices)
plt.xlabel("Index")
plt.ylabel("Price")
plt.title("Price Distribution")
plt.grid(True)

plt.savefig("nvidia_best_bids.png", dpi=100, bbox_inches="tight")
plt.show()

