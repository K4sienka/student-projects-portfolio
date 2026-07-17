from eelections.ballot_box import BallotBox
from eelections.paillier import PublicKey, PrivateKey, Ciphertext, generate_keypair, decrypt
from eelections.seeding import Voter


class Authority:
    """Election authority. Owns the Paillier keypair and is the only entity that decrypts."""

    def __init__(self, parties: list[str], ballot_box: BallotBox, key_bits: int = 512) -> None:
        self._parties = parties
        self._ballot_box = ballot_box
        self._seen: set[str] = set()
        self._public_key, self._private_key = generate_keypair(key_bits)
        ballot_box.set_public_key(self._public_key)

    @property
    def public_key(self) -> PublicKey:
        return self._public_key

    def submit(self, voter: Voter) -> bool:
        """Encrypt vote on the fly and cast it. Returns True if accepted, False if duplicate."""
        return self.submit_encoded(voter.pesel_hash, voter.vote)

    def submit_encoded(self, pesel_hash: str, enc_vote: list[Ciphertext]) -> bool:
        if pesel_hash in self._seen:
            return False

        self._seen.add(pesel_hash)
        self._ballot_box.cast(enc_vote)

        return True

    @property
    def tally(self) -> dict[str, int]:
        """Decrypt the current tally. Authority is the only caller of decrypt."""
        return {
            party: decrypt(self._private_key, enc_count)
            for party, enc_count in zip(self._parties, self._ballot_box.tally)
        }
