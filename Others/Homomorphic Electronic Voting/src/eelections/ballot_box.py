from eelections.paillier import PublicKey, Ciphertext, encrypt, add_encrypted


class BallotBox:
    def __init__(self, parties: list[str]) -> None:
        self._parties = parties
        self._public_key: PublicKey | None = None
        self._tally: list[Ciphertext] = []

    def set_public_key(self, pk: PublicKey) -> None:
        """Called by Authority after keypair generation. Initialises tally with Enc(0)."""
        self._public_key = pk
        self._tally = [encrypt(pk, 0) for _ in self._parties]

    @property
    def tally(self) -> list[Ciphertext]:
        return self._tally

    def cast(self, vote: list[Ciphertext]) -> None:
        assert self._public_key is not None, "BallotBox not initialised - call set_public_key first"
        self._tally = [
            add_encrypted(self._public_key, acc, enc_v)
            for acc, enc_v in zip(self._tally, vote)
        ]
