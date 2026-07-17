import re
import matplotlib.pyplot as plt
from collections import Counter, defaultdict
import math


# -----------------------------------------
# 1. Extract dialogue corpus
# -----------------------------------------

def extract_dialogue_corpus(path):
    with open(path, "r", encoding="utf-8") as f:
        text = f.read()

    lines = text.splitlines()
    character_line_regex = re.compile(r"^[A-Z][A-Z0-9\s\-']{2,}$")

    dialogue = []
    current_speaker = None

    for line in lines:
        stripped = line.strip()

        if not stripped:
            continue

        # Speaker line (e.g. "HAMLET")
        if character_line_regex.match(stripped):
            current_speaker = stripped
            continue

        # Stage directions
        if stripped.startswith("[") and stripped.endswith("]"):
            continue

        # Dialogue lines
        if current_speaker:
            cleaned = re.sub(r"\[.*?\]|\(.*?\)|<.*?>", "", stripped)
            cleaned = re.sub(r"\s+", " ", cleaned).strip()
            if cleaned:
                dialogue.append(cleaned)

    corpus = " ".join(dialogue)
    corpus = corpus.replace("—", " ").replace("--", " ")
    corpus = re.sub(r"[ ]+", " ", corpus).strip()

    return corpus


# -----------------------------------------
# 2. Load and process Hamlet
# -----------------------------------------

corpus = extract_dialogue_corpus("hamlet_TXT_FolgerShakespeare.txt")
words = corpus.split()
freq = Counter(words)

print("Total words:", len(words))
print("Unique words:", len(freq))


# -----------------------------------------
# 3. Plot: Top 20 most frequent words
# -----------------------------------------

top20 = freq.most_common(20)

plt.figure(figsize=(10,6))
labels = [w for w, c in top20]
counts = [c for w, c in top20]
plt.barh(labels, counts, color="orange")
plt.title("Top 20 Most Frequent Words in Hamlet Dialogue")
plt.xlabel("Frequency")
plt.gca().invert_yaxis()
plt.tight_layout()
plt.show()


# -----------------------------------------
# 4. Plot: Word frequency distribution (Zipf, log-log)
# -----------------------------------------

ordered_counts = sorted(freq.values(), reverse=True)

plt.figure(figsize=(10,6))
plt.plot(ordered_counts, color="orange")
plt.yscale("log")
plt.xscale("log")
plt.title("Word Frequency Distribution (Log-Log, Zipf)")
plt.xlabel("Rank")
plt.ylabel("Frequency")
plt.grid(True, which="both", linestyle="--", alpha=0.4)
plt.tight_layout()
plt.show()


# -----------------------------------------
# 5. Markov chain + entropy per word
# -----------------------------------------

chain = defaultdict(list)
for i in range(len(words) - 1):
    chain[words[i]].append(words[i+1])
chain[words[-1]].append("<END>")

entropy = {}
for w, nexts in chain.items():
    cnt = Counter(nexts)
    total = sum(cnt.values())
    H = -sum((c/total) * math.log2(c/total) for c in cnt.values())
    entropy[w] = H

# Take 20 highest entropy words
top_entropy = sorted(entropy.items(), key=lambda x: x[1], reverse=True)[:20]

plt.figure(figsize=(10,6))
plt.barh([w for w, h in top_entropy],
         [h for w, h in top_entropy],
         color="orange")
plt.title("Top 20 Most Unpredictable Words (Highest Markov Entropy)")
plt.xlabel("Entropy (bits)")
plt.gca().invert_yaxis()
plt.tight_layout()
plt.show()
