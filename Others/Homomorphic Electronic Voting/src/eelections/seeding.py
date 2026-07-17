from collections import Counter
from datetime import date, timedelta
import hashlib
import itertools
import random
import string

from eelections.ballot import Ballot
from eelections.paillier import PublicKey, Ciphertext


PESEL_WEIGHTS = [1, 3, 7, 9, 1, 3, 7, 9, 1, 3]


def _encoded_pesel_month(birth_date: date) -> int:
    """Returns PESEL month value encoded according to the birth century."""
    year = birth_date.year
    month = birth_date.month

    if 1800 <= year <= 1899:
        return month + 80
    if 1900 <= year <= 1999:
        return month
    if 2000 <= year <= 2099:
        return month + 20
    if 2100 <= year <= 2199:
        return month + 40
    if 2200 <= year <= 2299:
        return month + 60

    raise ValueError("Unsupported birth year for PESEL generation.")


def _decode_pesel_birth_date(pesel: str) -> date | None:
    """Decodes birth date from PESEL. Returns None if the date is invalid."""
    year = int(pesel[0:2])
    encoded_month = int(pesel[2:4])
    day = int(pesel[4:6])

    if 1 <= encoded_month <= 12:
        full_year = 1900 + year
        month = encoded_month
    elif 21 <= encoded_month <= 32:
        full_year = 2000 + year
        month = encoded_month - 20
    elif 81 <= encoded_month <= 92:
        full_year = 1800 + year
        month = encoded_month - 80
    elif 41 <= encoded_month <= 52:
        full_year = 2100 + year
        month = encoded_month - 40
    elif 61 <= encoded_month <= 72:
        full_year = 2200 + year
        month = encoded_month - 60
    else:
        return None

    try:
        return date(full_year, month, day)
    except ValueError:
        return None


def is_valid_pesel(pesel: str) -> bool:
    """Checks if PESEL has correct length, date and checksum."""
    if len(pesel) != 11 or not pesel.isdigit():
        return False

    if _decode_pesel_birth_date(pesel) is None:
        return False

    checksum = sum(
        int(digit) * weight
        for digit, weight in zip(pesel[:10], PESEL_WEIGHTS)
    )

    control_digit = (10 - checksum % 10) % 10

    return control_digit == int(pesel[10])


def generate_pesel() -> str:
    """
    Generates a valid Polish PESEL.

    PESEL structure:
    YYMMDDSSSSK

    YYMMDD - birth date, with month encoded by century,
    SSSS   - serial number,
    K      - checksum digit.
    """
    start_date = date(1940, 1, 1)
    end_date = date(2008, 12, 31)

    days_range = (end_date - start_date).days
    birth_date = start_date + timedelta(days=random.randint(0, days_range))

    year = birth_date.year % 100
    month = _encoded_pesel_month(birth_date)
    day = birth_date.day

    serial_number = random.randint(0, 9999)

    pesel_without_checksum = (
        f"{year:02d}"
        f"{month:02d}"
        f"{day:02d}"
        f"{serial_number:04d}"
    )

    checksum = sum(
        int(digit) * weight
        for digit, weight in zip(pesel_without_checksum, PESEL_WEIGHTS)
    )

    control_digit = (10 - checksum % 10) % 10

    return pesel_without_checksum + str(control_digit)


def generate_unique_pesels(amount: int) -> list[str]:
    """Generates a list of unique, valid PESEL numbers."""
    pesels: set[str] = set()

    while len(pesels) < amount:
        pesels.add(generate_pesel())

    return list(pesels)


class Voter:
    def __init__(self, pesel: str, party: str, ballot: Ballot) -> None:
        if not is_valid_pesel(pesel):
            raise ValueError(f"Invalid PESEL: {pesel}")

        self._pesel = pesel
        self._pesel_hash = hashlib.sha256(pesel.encode()).hexdigest()[:16]
        self._party = party
        self._ballot = ballot

    @property
    def vote(self) -> list[Ciphertext]:
        """Returns freshly encrypted one-hot ballot."""
        return self._ballot.encode(self._party)

    @property
    def pesel(self) -> str:
        """Raw PESEL used only for audit logging."""
        return self._pesel

    @property
    def pesel_hash(self) -> str:
        """Hashed PESEL used for duplicate vote detection."""
        return self._pesel_hash


def party_labels(num_parties: int) -> list[str]:
    labels = list[str]()
    curr_length = 1

    while len(labels) < num_parties:
        names_of_curr_length = itertools.product(
            string.ascii_uppercase,
            repeat=curr_length,
        )

        for name in names_of_curr_length:
            labels.append("".join(name))

            if len(labels) == num_parties:
                return labels

        curr_length += 1

    return labels


def seed_voters(num_parties: int, num_votes: int, public_key: PublicKey) -> list[Voter]:
    """Creates initial seeding of voters with duplicate PESELs possible."""
    parties = party_labels(num_parties)
    ballot = Ballot(parties=parties, public_key=public_key)

    pesel_pool = generate_unique_pesels(num_votes)

    return [
        Voter(
            pesel=random.choice(pesel_pool),
            party=random.choice(parties),
            ballot=ballot,
        )
        for _ in range(num_votes)
    ]


def get_real_vote_count(voters: list[Voter]) -> Counter:
    """Real vote count excluding duplicate voting attempts. First vote wins."""
    counts: Counter = Counter()
    seen: set[str] = set()

    for voter in voters:
        if voter.pesel_hash in seen:
            continue

        seen.add(voter.pesel_hash)
        counts[voter._party] += 1

    return counts