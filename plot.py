# plot.py
import sys
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

def main():
    # argv: [script, title, out_path, x0, y0, x1, y1, ...]
    if len(sys.argv) < 5 or (len(sys.argv) - 3) % 2 != 0:
        print("Usage: plot.py <title> <output.png> <x0> <y0> [<x1> <y1> ...]")
        sys.exit(1)

    title    = sys.argv[1]
    out_path = sys.argv[2]
    coords   = list(map(float, sys.argv[3:]))
    xs = coords[0::2]
    ys = coords[1::2]

    fig, ax = plt.subplots(figsize=(5, 3))
    ax.plot(xs, ys, marker='o', linewidth=2)

    # Titlu și etichete
    ax.set_title(title)
    ax.set_xlabel("Ani")
    ax.set_ylabel("Populație")

    # Tick-uri pe axa X la fiecare 1 an
    ax.xaxis.set_major_locator(ticker.MultipleLocator(1))
    ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%d'))

    # Tick-uri pe axa Y – adaptate la valori mari
    # Alege un locator potrivit (de ex. la fiecare 1 milion)
    ax.yaxis.set_major_locator(ticker.MaxNLocator(nbins=6, integer=True))
    # Dar dacă vrei fix la fiecare 1.000.000:
    # ax.yaxis.set_major_locator(ticker.MultipleLocator(1_000_000))
    # Separator de mii în etichete
    ax.yaxis.set_major_formatter(ticker.StrMethodFormatter('{x:,.0f}'))

    # Grilă orizontală pentru claritate
    ax.grid(which='major', axis='y', linestyle='--', linewidth=0.5, alpha=0.7)

    plt.tight_layout()
    plt.savefig(out_path)
    plt.close()

if __name__ == "__main__":
    main()
