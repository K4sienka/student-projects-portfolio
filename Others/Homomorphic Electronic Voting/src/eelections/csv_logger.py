import csv
from collections import Counter
from pathlib import Path

from eelections.paillier import Ciphertext
from eelections.seeding import Voter

_TRUNC = 24  # chars to show from each ciphertext in CSVs


class CsvLogger:
    """Writes four CSV audit files capturing the full election pipeline."""

    def __init__(self, parties: list[str], output_dir: str = "election_logs") -> None:
        self._parties = parties
        self._dir = Path(output_dir)
        self._dir.mkdir(parents=True, exist_ok=True)

        self._f1 = open(self._dir / "1_voters.csv", "w", newline="")
        self._f2 = open(self._dir / "2_encrypted_ballots.csv", "w", newline="")
        self._f3 = open(self._dir / "3_running_tally.csv", "w", newline="")
        self._f4 = open(self._dir / "4_final_results.csv", "w", newline="")

        self._w1 = csv.writer(self._f1)
        self._w2 = csv.writer(self._f2)
        self._w3 = csv.writer(self._f3)
        self._w4 = csv.writer(self._f4)

        self._write_headers()

    def _write_headers(self) -> None:
        self._w1.writerow([
            "voter_index", "pesel_raw", "pesel_hashed",
            "party_voted", "one_hot_plaintext", "accepted",
        ])
        self._w2.writerow([
            "ballot_num", "pesel_hashed",
            "plaintext_vote_debug", "enc_votes_truncated",
        ])
        enc_cols = [f"{p}_enc_trunc" for p in self._parties]
        dec_cols = [f"{p}_dec" for p in self._parties]
        self._w3.writerow(["after_ballot_n"] + enc_cols + dec_cols)
        self._w4.writerow([
            "party", "encrypted_sum_truncated",
            "decrypted_count", "real_count", "correct",
        ])

    def log_voters(self, voters: list[Voter]) -> None:
        """Log all voters (ground truth) before any encryption. Called once."""
        seen: set[str] = set()
        for i, voter in enumerate(voters):
            accepted = voter.pesel_hash not in seen
            seen.add(voter.pesel_hash)
            one_hot = [1 if voter._party == p else 0 for p in self._parties]
            self._w1.writerow([
                i, voter.pesel, voter.pesel_hash,
                voter._party, one_hot, accepted,
            ])
        self._f1.flush()

    def log_encrypted_ballot(
        self,
        ballot_num: int,
        voter: Voter,
        enc_vote: list[Ciphertext],
    ) -> None:
        """Log what the ballot box actually received for this accepted vote."""
        one_hot = [1 if voter._party == p else 0 for p in self._parties]
        enc_trunc = [str(c)[:_TRUNC] + "..." for c in enc_vote]
        self._w2.writerow([ballot_num, voter.pesel_hash, one_hot, enc_trunc])
        self._f2.flush()

    def log_tally_snapshot(
        self,
        after_n: int,
        enc_tally: list[Ciphertext],
        authority,  # Authority - untyped to avoid circular import
    ) -> None:
        """Log the encrypted tally and its decryption after each accepted vote."""
        enc_trunc = [str(c)[:_TRUNC] + "..." for c in enc_tally]
        dec_values = list(authority.tally.values())
        self._w3.writerow([after_n] + enc_trunc + dec_values)
        self._f3.flush()

    def log_final_results(
        self,
        enc_tally: list[Ciphertext],
        decrypted_tally: dict[str, int],
        real_count: Counter,
    ) -> None:
        """Log final comparison: decrypted result vs ground truth."""
        for party, enc_sum in zip(self._parties, enc_tally):
            dec = decrypted_tally[party]
            real = real_count.get(party, 0)
            self._w4.writerow([
                party,
                str(enc_sum)[:_TRUNC] + "...",
                dec,
                real,
                dec == real,
            ])
        self._f4.flush()

    def close(self) -> None:
        for f in (self._f1, self._f2, self._f3, self._f4):
            f.close()

    def __enter__(self) -> "CsvLogger":
        return self

    def __exit__(self, *_) -> None:
        self.close()
