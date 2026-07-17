# Homomorphic Electronic Voting System

## Authors

Jan Dworak, Paweł Moćko, Katarzyna Wesołowska

## Project Overview

This project presents a simple simulation of an electronic voting system based on the Paillier homomorphic encryption scheme.

Its purpose is to demonstrate that individual votes can be encrypted, stored in a ballot box, and counted without revealing how a specific voter voted. Only the final election result is decrypted by the election authority.

The system also includes protection against duplicate voting. Voters are identified by PESEL numbers, but duplicate detection is performed using a SHA-256 hash of the PESEL.

> This project is an educational prototype and is not intended for use in real elections.

## How It Works

Each voter has:

- a PESEL number,
- a selected party or candidate,
- a one-hot encoded vote.

Example for five parties, `A`, `B`, `C`, `D`, and `E`:

```text
Vote for party D:
[0, 0, 0, 1, 0]
```

Each value is encrypted using the Paillier public key:

```text
[Enc(0), Enc(0), Enc(0), Enc(1), Enc(0)]
```

The ballot box receives only the encrypted vector and cannot read the vote.

Encrypted votes are aggregated homomorphically. In the Paillier scheme, multiplication of ciphertexts corresponds to addition of plaintext values:

```text
Enc(a) * Enc(b) mod n² = Enc(a + b)
```

This allows all votes to be counted without decrypting individual ballots.

## Project Structure

```text
eelections/
├── src/eelections/
│   ├── __init__.py
│   ├── authority.py
│   ├── ballot.py
│   ├── ballot_box.py
│   ├── csv_logger.py
│   ├── paillier.py
│   └── seeding.py
├── election_logs/
│   ├── 1_voters.csv
│   ├── 2_encrypted_ballots.csv
│   ├── 3_running_tally.csv
│   └── 4_final_results.csv
├── pyproject.toml
├── uv.lock
├── README.md
└── README_RAPORT.md
```

## Main Modules

### `src/eelections/__init__.py`

The main entry point of the application. It is responsible for:

1. reading command-line parameters,
2. generating the list of parties,
3. creating the ballot box,
4. creating the election authority,
5. generating voters,
6. accepting votes,
7. rejecting duplicate votes,
8. writing CSV audit logs,
9. decrypting the final election result.

### `src/eelections/seeding.py`

Generates test data for the simulation, including voters, PESEL numbers, and randomly assigned votes.

PESEL numbers follow the standard structure:

```text
YYMMDDSSSSK
```

Where:

- `YY` — year of birth,
- `MM` — month with century encoding,
- `DD` — day of birth,
- `SSSS` — serial number,
- `K` — checksum digit.

The checksum uses the following weights:

```python
PESEL_WEIGHTS = [1, 3, 7, 9, 1, 3, 7, 9, 1, 3]
```

Inside the `Voter` class, the PESEL is hashed:

```python
self._pesel_hash = hashlib.sha256(pesel.encode()).hexdigest()[:16]
```

The hash is used to detect repeated voting attempts.

### `src/eelections/authority.py`

Represents the election authority. It:

- generates the Paillier public and private keys,
- provides the public key to the ballot box,
- checks whether a voter has already voted,
- accepts only the first vote associated with a PESEL hash,
- decrypts the final election result.

### `src/eelections/ballot.py`

Creates and encrypts a ballot.

For example, for parties `A`, `B`, and `C`, a vote for party `B` becomes:

```text
[Enc(0), Enc(1), Enc(0)]
```

### `src/eelections/ballot_box.py`

Represents the electronic ballot box.

It never decrypts individual votes. It stores only encrypted running totals and aggregates ballots using the homomorphic property of Paillier encryption.

### `src/eelections/paillier.py`

Contains the Paillier cryptosystem implementation, including:

- prime number generation,
- public and private key generation,
- encryption,
- decryption,
- homomorphic addition of encrypted values.

### `src/eelections/csv_logger.py`

Writes audit data to CSV files so that the simulation can be inspected and verified.

Generated files:

| File | Description |
|---|---|
| `1_voters.csv` | All voting attempts, including duplicates |
| `2_encrypted_ballots.csv` | Accepted encrypted ballots |
| `3_running_tally.csv` | Encrypted tally after each accepted vote |
| `4_final_results.csv` | Final decrypted results and verification |

## Duplicate Vote Protection

The system stores hashes of PESEL numbers that have already been used.

First voting attempt:

```text
pesel_hash not in seen
→ vote accepted
```

Repeated voting attempt:

```text
pesel_hash already in seen
→ vote rejected
```

The `accepted` column in `1_voters.csv` records the outcome:

```text
True  — vote accepted
False — duplicate vote rejected
```

## Vote Privacy

The vote is encrypted before it is added to the ballot box.

The ballot box receives only encrypted values:

```text
[Enc(0), Enc(0), Enc(1), Enc(0), Enc(0)]
```

Only the election authority has the private key required to decrypt the final tally.

The encrypted values stored in `2_encrypted_ballots.csv` are shortened for readability.

## Audit Logs

### `1_voters.csv`

Contains all voting attempts and duplicate-detection results.

Columns:

```text
pesel_raw,pesel_hashed,party_voted,one_hot_plaintext,accepted
```

Raw PESEL numbers and plaintext votes are stored only to make the educational demonstration easy to verify.

> In a real system, raw PESEL numbers and plaintext votes must never be stored together.

### `2_encrypted_ballots.csv`

Contains only accepted encrypted ballots.

### `3_running_tally.csv`

Shows how the encrypted tally changes after each accepted vote.

### `4_final_results.csv`

Contains the decrypted election result and compares it with the ground-truth count.

Example:

```text
party,decrypted_count,real_count,correct
A,2,2,True
B,3,3,True
D,6,6,True
```

A value of `True` in the `correct` column means that the decrypted result matches the expected result.

## Installation

The project uses `uv` for dependency management.

Install `uv` if necessary:

```powershell
pip install uv
```

## Running the Project

Run the simulation with default parameters:

```powershell
uv run eelections
```

Run it with custom parameters:

```powershell
uv run eelections --num-parties 5 --num-voters 20 --key-bits 512
```

After execution, the program prints the election result and writes audit logs to:

```text
election_logs/
```

Open the log directory on Windows:

```powershell
explorer .\election_logs
```

## Example Output

```text
Generating 512-bit Paillier keypair...
Keypair ready.

Real vote counts (ground truth): {'E': 3, 'A': 2, 'D': 6, 'B': 3}
Tally before election:           {'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0}

Tally after election:            {'A': 2, 'B': 3, 'C': 0, 'D': 6, 'E': 3}

Audit logs written to election_logs/
```

## Security Notes

This implementation demonstrates selected cryptographic ideas but does not provide all properties required by a real electronic voting system.

A production-grade system would also require, among other things:

- secure voter authentication,
- anonymous credentials,
- protection against linking voters to ballots,
- verifiable ballot submission,
- integrity protection for audit logs,
- secure key management,
- distributed or threshold decryption,
- protection against coercion and vote selling,
- independent security audits.

## Technologies

- Python
- Paillier homomorphic encryption
- SHA-256 hashing
- CSV-based audit logging
- `uv` package management
