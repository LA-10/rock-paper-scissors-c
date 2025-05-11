import random
import os
from hash_map import QTable

# Q-learning setup
alpha = 0.1
gamma = 0.9
epsilon = 0.1
actions = [1, 2, 3]

q = QTable()

def read_file_lines(file_path):
    """Read lines from a file."""
    if os.path.exists(file_path):
        with open(file_path, 'r') as file:
            return [line.strip() for line in file.readlines()]
    return []

def get_username():
    """Read the username from the username.txt file."""
    lines = read_file_lines("save/username.txt")
    if lines:
        return lines[0]  # Assume first line is the username
    return ""

def read_user_history(file_path):
    """Reads the user's move history from the log file."""
    moves = []
    username = get_username()
    if not username:
        return moves

    if os.path.exists(file_path):
        with open(file_path, 'r') as file:
            for line in file:
                if line.startswith(f"{username}:"):
                    try:
                        move = int(line.split(":")[1].strip())
                        moves.append(move)
                    except ValueError:
                        continue
    return moves

def get_state_from_history(moves, n=3):
    """Get the last N moves as a state."""
    return tuple(moves[-n:]) if len(moves) >= n else tuple(moves)

def q_learning_predict():
    history_file = "save/game_moves.txt"
    moves = read_user_history(history_file)
    state = get_state_from_history(moves)

    q_values = {action: q.get(state, action) for action in actions}
    if all(v == 0 for v in q_values.values()):
        return random.choice(actions)

    return max(q_values, key=q_values.get)

def counter_move(user_move):
    """Return the winning move against the given user move."""
    if user_move == 1:
        return 2  # Paper beats Rock
    elif user_move == 2:
        return 3  # Scissors beats Paper
    elif user_move == 3:
        return 1  # Rock beats Scissors
    return random.choice(actions)  # Fallback in case of invalid input

# Example usage
predicted_user_move = q_learning_predict()
predicted_ai_move = counter_move(predicted_user_move)

