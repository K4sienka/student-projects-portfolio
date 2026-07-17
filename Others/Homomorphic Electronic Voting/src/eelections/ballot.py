from eelections.paillier import PublicKey, Ciphertext, encrypt


class Ballot:
    def __init__(self, parties: list[str], public_key: PublicKey) -> None:
        self._parties = parties
        self._public_key = public_key

    def encode(self, vote: str) -> list[Ciphertext]:
        """One-hot encode the vote and encrypt each element with Paillier."""
        return [
            encrypt(self._public_key, 1 if vote == party else 0)
            for party in self._parties
        ]
