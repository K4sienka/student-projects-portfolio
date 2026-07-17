import argparse

from eelections.authority import Authority
from eelections.ballot_box import BallotBox
from eelections.csv_logger import CsvLogger
from eelections.seeding import party_labels, seed_voters, get_real_vote_count


def main() -> None:
    parser = argparse.ArgumentParser(description="E-voting simulation with Paillier homomorphic encryption")
    parser.add_argument("--num-parties", type=int, default=5)
    parser.add_argument("--num-voters", type=int, default=20)
    parser.add_argument("--key-bits", type=int, default=512, help="Paillier key size in bits (256 is faster for testing)")
    parser.add_argument("--output-dir", type=str, default="election_logs")
    args = parser.parse_args()

    num_parties = args.num_parties
    num_voters = args.num_voters

    print(f"Generating {args.key_bits}-bit Paillier keypair...")
    parties = party_labels(num_parties=num_parties)
    ballot_box = BallotBox(parties=parties)
    # Authority generates keypair and injects public key into BallotBox
    authority = Authority(parties=parties, ballot_box=ballot_box, key_bits=args.key_bits)
    print("Keypair ready.\n")

    # Voters are seeded after keypair exists so Ballot can encrypt
    voters = seed_voters(num_parties=num_parties, num_votes=num_voters, public_key=authority.public_key)
    real_count = get_real_vote_count(voters)

    print("Real vote counts (ground truth):", dict(real_count))
    print("Tally before election:          ", authority.tally)
    print()

    with CsvLogger(parties=parties, output_dir=args.output_dir) as logger:
        logger.log_voters(voters)

        accepted_n = 0
        for voter in voters:
            enc_vote = voter.vote  # single call - one fresh encryption per voter
            accepted = authority.submit_encoded(voter.pesel_hash, enc_vote)
            if accepted:
                logger.log_encrypted_ballot(accepted_n, voter, enc_vote)
                logger.log_tally_snapshot(accepted_n, ballot_box.tally, authority)
                accepted_n += 1

        final_tally = authority.tally
        logger.log_final_results(ballot_box.tally, final_tally, real_count)

    print("Tally after election:           ", final_tally)
    print(f"\nAudit logs written to {args.output_dir}/")
    print("  1_voters.csv           - all voters incl. duplicates (ground truth)")
    print("  2_encrypted_ballots.csv - encrypted ballots received by BallotBox")
    print("  3_running_tally.csv    - homomorphic tally evolving after each vote")
    print("  4_final_results.csv    - decrypted result vs ground truth")
