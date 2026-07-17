import re
import random
from collections import defaultdict, Counter
from pyvis.network import Network


# ==========================================
# 1) EXTRACT CLEAN CORPUS
# ==========================================

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

        if character_line_regex.match(stripped):
            current_speaker = stripped
            continue

        if stripped.startswith("[") and stripped.endswith("]"):
            continue

        if current_speaker:
            cleaned = re.sub(r"\[.*?\]|\(.*?\)|<.*?>", "", stripped)
            cleaned = re.sub(r"\s+", " ", cleaned).strip()
            if cleaned:
                dialogue.append(cleaned)

    corpus = " ".join(dialogue)
    corpus = corpus.replace("—", " ").replace("--", " ")
    corpus = re.sub(r"[ ]+", " ", corpus).strip()
    return corpus


# ==========================================
# 2) BUILD MARKOV
# ==========================================

def build_markov_chain(corpus):
    words = corpus.split()
    chain = defaultdict(list)

    for i in range(len(words) - 1):
        chain[words[i]].append(words[i + 1])

    chain[words[-1]].append("<END>")
    return chain


# ==========================================
# 3) TRANSITION PROBABILITIES
# ==========================================

def transition_probabilities(chain, word):
    next_words = chain[word]
    count = Counter(next_words)
    total = sum(count.values())
    return {w: count[w] / total for w in count}


# ==========================================
# 4) INTERACTIVE GRAPH (PYVIS)
# ==========================================

def visualize_markov_interactive(chain, center_word, top_k=12, output="graph.html"):
    nt = Network(height="800px", width="100%", directed=True, bgcolor="#222222", font_color="white")

    nt.force_atlas_2based()  # dynamic layout

    probs = transition_probabilities(chain, center_word)
    probs_sorted = dict(sorted(probs.items(), key=lambda x: x[1], reverse=True)[:top_k])

    # Dodaj główny węzeł
    nt.add_node(center_word, label=center_word, color="#ffcc00", size=25)

    # Dodaj połączenia
    for w, p in probs_sorted.items():
        nt.add_node(w, label=w, color="#00aaff", size=15)
        nt.add_edge(center_word, w, value=p, title=f"p={p:.3f}")

    nt.write_html(output)

    print(f"Interaktywny graf zapisany jako: {output}")


# ==========================================
# 5) FULL PIPELINE
# ==========================================

path = "hamlet_TXT_FolgerShakespeare.txt"

corpus = extract_dialogue_corpus(path)
chain = build_markov_chain(corpus)

# Przykład wizualizacji
visualize_markov_interactive(chain, center_word="there", top_k=12, output="markov_there.html")


from pyvis.network import Network
from collections import Counter
import math

from pyvis.network import Network
from collections import Counter

def markov_big_graph(chain, root_word, depth=3, top_k=8, output="big_markov.html"):
    net = Network(
        height="900px",
        width="100%",
        directed=True,
        bgcolor="#111111",
        font_color="white"
    )

    net.force_atlas_2based(gravity=-50)

    added_nodes = set()   # <-- kontrola duplikatów

    def safe_add_node(word, level):
        """Dodaje węzeł tylko jeśli jeszcze go nie ma."""
        if word not in added_nodes:
            color = "#ffcc00" if level == 1 else "#00aaff"
            size = 35 - level * 6
            net.add_node(word, label=word, color=color, size=size)
            added_nodes.add(word)

    def add_layer(word, level):
        if level > depth:
            return

        safe_add_node(word, level)

        next_words = chain[word]
        count = Counter(next_words)
        next_words_sorted = count.most_common(top_k)

        for w, c in next_words_sorted:
            p = c / sum(count.values())
            label = f"{p:.2f}"

            # upewnij się, że node istnieje
            safe_add_node(w, level + 1)

            # dopiero teraz rysujemy krawędź
            net.add_edge(word, w, value=p, title=label, label=label)

            # rekurencja
            add_layer(w, level + 1)

    # start
    add_layer(root_word, 1)

    net.write_html(output)
    print(f"[OK] Wygenerowano graf: {output}")

markov_big_graph(chain, root_word="There", depth=4, top_k=8, output="There_big.html")


from pyvis.network import Network
from collections import Counter

def p_to_color(p):
    """Mapuje prawdopodobieństwo na ładny kolor."""
    if p > 0.6:
        return "#ff4444"   # czerwony
    elif p > 0.3:
        return "#ff8800"   # pomarańczowy
    elif p > 0.15:
        return "#ffcc00"   # żółty
    else:
        return "#00aaff"   # niebieski


def markov_big_clean_graph(chain, root_word, depth=3, top_k=10, min_p=0.05, output="clean_big_graph.html"):
    net = Network(
        height="900px",
        width="100%",
        directed=True,
        bgcolor="#000000",
        font_color="white"
    )

    net.force_atlas_2based(
        gravity=-60,
        central_gravity=0.005,
        spring_length=170,
        spring_strength=0.015,
        damping=0.9
    )

    added_nodes = set()

    def safe_add_node(word, level):
        if word not in added_nodes:
            color = ["#ffd700", "#00e6b8", "#66b3ff", "#999999"][level - 1]
            size = 35 - level * 5
            net.add_node(word, label=word, color=color, size=size)
            added_nodes.add(word)

    def add_layer(word, level):
        if level > depth:
            return

        safe_add_node(word, level)

        next_words = chain[word]
        count = Counter(next_words)
        total = sum(count.values())

        for w, c in count.most_common(top_k):
            p = c / total
            if p < min_p:
                continue  # FILTR: tylko mocne przejścia

            safe_add_node(w, level + 1)

            edge_color = p_to_color(p)
            label = f"{p:.2f}"

            net.add_edge(
                word,
                w,
                value=p,
                title=label,
                label=label,
                color=edge_color,
                width=2 + p * 8  # grubość krawędzi rośnie z p
            )

            add_layer(w, level + 1)

    add_layer(root_word, 1)

    net.write_html(output)
    print(f"✔ Wygenerowano czytelny, zoptymalizowany graf: {output}")


markov_big_clean_graph(
    chain,
    root_word="there",
    depth=3,
    top_k=12,
    min_p=0.05,
    output="there_clean_graph.html"
)