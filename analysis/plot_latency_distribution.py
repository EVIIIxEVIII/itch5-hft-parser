import csv
import matplotlib.pyplot as plt
import math

def weighted_percentile(latencies, counts, percentile):
    total = sum(counts)
    threshold = total * percentile
    acc = 0
    for latency, count in zip(latencies, counts):
        acc += count
        if acc >= threshold:
            return latency
    return latencies[-1]

def plot_latency_distribution(csv_path="../data/latency_distribution.csv"):
    latencies = []
    counts = []

    with open(csv_path, "r", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            latencies.append(int(row["latency_ns"]))
            counts.append(int(row["count"]))

    if not latencies:
        raise RuntimeError("CSV is empty")

    data = sorted(zip(latencies, counts), key=lambda x: x[0])
    if not data:
        raise RuntimeError("No data <= 1000 ns")

    latencies, counts = zip(*data)

    p50 = weighted_percentile(latencies, counts, 0.50)
    p95 = weighted_percentile(latencies, counts, 0.95)
    p99 = weighted_percentile(latencies, counts, 0.99)

    buckets = {}
    for latency, count in zip(latencies, counts):
        buckets[latency] = buckets.get(latency, 0) + count

    bx = sorted(buckets.keys())
    by = [buckets[b] for b in bx]

    plt.figure(figsize=(10, 6))
    plt.bar(bx, by)
    plt.xscale("log")

    plt.xlabel("Latency bucket (ns, log2)")
    plt.ylabel("Count")
    plt.title("Latency Distribution (≤ 1000 ns)")

    text = (
        f"p50 = {p50} ns\n"
        f"p95 = {p95} ns\n"
        f"p99 = {p99} ns"
    )

    plt.text(
        0.98, 0.95,
        text,
        transform=plt.gca().transAxes,
        fontsize=10,
        verticalalignment="top",
        horizontalalignment="right",
        bbox=dict(boxstyle="round", facecolor="white", alpha=0.8)
    )

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    plot_latency_distribution()

