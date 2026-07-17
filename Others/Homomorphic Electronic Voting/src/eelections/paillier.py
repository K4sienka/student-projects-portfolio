from __future__ import annotations
import math
import random
from dataclasses import dataclass

type Ciphertext = int

_SMALL_PRIMES = [
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
]


def _miller_rabin(n: int, rounds: int = 20) -> bool:
    if n < 2:
        return False
    if n in _SMALL_PRIMES:
        return True
    if any(n % p == 0 for p in _SMALL_PRIMES):
        return False

    # write n-1 as 2^r * d
    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    for _ in range(rounds):
        a = random.randrange(2, n - 1)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True


def _generate_prime(bits: int) -> int:
    while True:
        candidate = random.getrandbits(bits)
        candidate |= (3 << (bits - 2))  # force top two bits set
        candidate |= 1                   # force odd
        if any(candidate % p == 0 for p in _SMALL_PRIMES):
            continue
        if _miller_rabin(candidate):
            return candidate


@dataclass(frozen=True)
class PublicKey:
    n: int
    g: int  # always n+1 in simplified Paillier

    @property
    def n_sq(self) -> int:
        return self.n * self.n


@dataclass(frozen=True)
class PrivateKey:
    lam: int         # lcm(p-1, q-1)
    mu: int          # lam^-1 mod n
    public_key: PublicKey


def generate_keypair(bits: int = 512) -> tuple[PublicKey, PrivateKey]:
    half = bits // 2
    p = _generate_prime(half)
    q = _generate_prime(half)
    while q == p:
        q = _generate_prime(half)

    n = p * q
    g = n + 1
    lam = (p - 1) * (q - 1) // math.gcd(p - 1, q - 1)
    # With g = n+1, L(g^lam mod n^2) = lam exactly, so mu = lam^-1 mod n
    mu = pow(lam, -1, n)

    pk = PublicKey(n=n, g=g)
    sk = PrivateKey(lam=lam, mu=mu, public_key=pk)
    return pk, sk


def encrypt(pk: PublicKey, plaintext: int) -> Ciphertext:
    assert 0 <= plaintext < pk.n, "plaintext must be in [0, n)"
    while True:
        r = random.randrange(1, pk.n)
        if math.gcd(r, pk.n) == 1:
            break
    # c = g^m * r^n mod n^2
    return (pow(pk.g, plaintext, pk.n_sq) * pow(r, pk.n, pk.n_sq)) % pk.n_sq


def decrypt(sk: PrivateKey, ciphertext: Ciphertext) -> int:
    pk = sk.public_key
    x = pow(ciphertext, sk.lam, pk.n_sq)
    l_x = (x - 1) // pk.n          # L function: (x-1)/n
    return (l_x * sk.mu) % pk.n


def add_encrypted(pk: PublicKey, c1: Ciphertext, c2: Ciphertext) -> Ciphertext:
    """Homomorphic addition: Enc(a) * Enc(b) mod n^2 = Enc(a+b)."""
    return (c1 * c2) % pk.n_sq
