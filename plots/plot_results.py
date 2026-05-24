from __future__ import annotations

import csv
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "data" / "results.csv"
OUT = ROOT / "png"

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt


def read_rows() -> list[dict[str, str]]:
    with DATA.open(newline="", encoding="utf-8") as f:
        return list(csv.DictReader(f))


def plot_metric(rows: list[dict[str, str]], dataset: str, metric: str) -> None:
    grouped: dict[str, list[tuple[int, float]]] = defaultdict(list)
    for row in rows:
        if row["dataset"] != dataset:
            continue
        grouped[row["algorithm"]].append((int(row["size"]), float(row[metric])))

    plt.figure(figsize=(11, 6))
    for algorithm, points in sorted(grouped.items()):
        points.sort()
        xs = [x for x, _ in points]
        ys = [y for _, y in points]
        plt.plot(xs, ys, marker="o", linewidth=1.8, markersize=3, label=algorithm)

    title_metric = "time, us" if metric == "time_us" else "character comparisons"
    plt.title(f"{dataset}: {title_metric}")
    plt.xlabel("array size")
    plt.ylabel(title_metric)
    plt.grid(True, alpha=0.3)
    plt.legend(fontsize=8)
    plt.tight_layout()
    plt.savefig(OUT / f"{dataset}_{metric}.png", dpi=160)
    plt.close()


def main() -> None:
    OUT.mkdir(exist_ok=True)
    for old_plot in OUT.glob("*.png"):
        old_plot.unlink()
    rows = read_rows()
    datasets = sorted({row["dataset"] for row in rows})
    for dataset in datasets:
        plot_metric(rows, dataset, "time_us")
        plot_metric(rows, dataset, "char_comparisons")
    print(f"Saved plots to {OUT}")


if __name__ == "__main__":
    main()
