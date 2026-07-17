import re
import random
from collections import defaultdict, Counter
import matplotlib.pyplot as plt


# ============================================================
# 1) EKSTRAKCJA CZYSTEGO TEKSTU (DIALOGI)
# ============================================================

def extract_dialogue_corpus(path, skip_first_n_lines=40):
    with open(path, "r", encoding="utf-8") as f:
        text = f.read()

    lines = text.splitlines()
    lines = lines[skip_first_n_lines:]  # <-- TU POMIJAMY WSTĘP

    character_line_regex = re.compile(r"^[A-Z][A-Z0-9\s\-']{2,}$")

    dialogue = []
    current_speaker = None

    for line in lines:
        stripped = line.strip()
        if not stripped:
            continue

        # Nazwa postaci (np. HAMLET)
        if character_line_regex.match(stripped):
            current_speaker = stripped
            continue

        # Didaskalia
        if stripped.startswith("[") and stripped.endswith("]"):
            continue

        # Linia dialogu
        if current_speaker:
            cleaned = re.sub(r"\[.*?\]|\(.*?\)|<.*?>", "", stripped)
            cleaned = re.sub(r"\s+", " ", cleaned).strip()
            if cleaned:
                dialogue.append(cleaned)

    corpus = " ".join(dialogue)
    corpus = corpus.replace("—", " ").replace("--", " ")
    corpus = re.sub(r"[ ]+", " ", corpus).strip()
    return corpus



# ============================================================
# 2) BUDOWANIE ŁAŃCUCHA MARKOVA
# ============================================================

def build_markov_chain(corpus):
    words = corpus.split()
    chain = defaultdict(list)

    for i in range(len(words) - 1):
        chain[words[i]].append(words[i + 1])

    chain[words[-1]].append("<END>")
    return chain


# ============================================================
# 3) GENERATOR ZDAŃ MARKOVA
# ============================================================

def generate_markov_sentence(chain, words, length=10):
    word = random.choice(words)
    sentence = [word]

    for _ in range(length - 1):
        nexts = chain[word]
        word = random.choice(nexts)
        if word == "<END>":
            word = random.choice(words)
        sentence.append(word)

    return " ".join(sentence)


# ============================================================
# 4) GENERATOR ZDAŃ LOSOWYCH — BEZ MARKOVA
# ============================================================

def generate_random_sentence(words, length=10):
    return " ".join(random.choice(words) for _ in range(length))



# ============================================================
# 6) URUCHOMIENIE PIPELINE
# ============================================================

path = "hamlet_TXT_FolgerShakespeare.txt"

corpus = extract_dialogue_corpus(path)
chain = build_markov_chain(corpus)
words = corpus.split()


# --- 3 przykładowe zdania Markova ---
print("=== 3 Markov sentences ===")
for _ in range(3):
    print(generate_markov_sentence(chain, words, length=10))


# --- 3 przykładowe zdania losowe ---
print("\n=== 3 Random sentences ===")
for _ in range(3):
    print(generate_random_sentence(words, length=10))
    
# ============================================================
# 7) MONTE CARLO: generowanie masy zdań Markova
# ============================================================

def monte_carlo_markov(chain, words, sentence_len=10, samples=100000):
    sentences = []
    for _ in range(samples):
        word = random.choice(words)
        generated = [word]

        for _ in range(sentence_len - 1):
            nexts = chain[word]
            word = random.choice(nexts)
            if word == "<END>":
                word = random.choice(words)  # restart if end token
            generated.append(word)

        sentences.append(" ".join(generated))

    return sentences


# ============================================================
# 8) POLICZ NAJCZĘSTSZE ZDANIA
# ============================================================

def most_common_markov_sentences(chain, words, sentence_len=10, samples=50000, top_k=10):
    print(f"\n[Monte Carlo] Generating {samples} Markov sentences...")

    sentences = monte_carlo_markov(chain, words, sentence_len=sentence_len, samples=samples)

    cnt = Counter(sentences)
    return cnt.most_common(top_k)


# ============================================================
# 9) URUCHOMIENIE Monte Carlo
# ============================================================

top_sentences = most_common_markov_sentences(
    chain,
    words,
    sentence_len=10,
    samples=10000000,   # możesz zwiększyć do 200k–500k
    top_k=20
)

print("\n=== TOP 10 most repeated Markov sentences ===")
for s, c in top_sentences:
    print(f"{c}x   {s}")
