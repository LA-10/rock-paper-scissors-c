class QTable:
    def __init__(self):
        self.q_table = {}  # dictionary to store Q-values

    def get(self, state, action):
        """Get Q-value for a (state, action) pair. Returns 0 if not yet stored."""
        return self.q_table.get((state, action), 0.0)

    def set(self, state, action, value):
        """Set Q-value for a (state, action) pair."""
        self.q_table[(state, action)] = value

    def best_action(self, state, possible_actions):
        """Returns the action with the highest Q-value for a given state."""
        best = None
        best_value = float('-inf')
        for action in possible_actions:
            q = self.get(state, action)
            if q > best_value:
                best = action
                best_value = q
        return best

    def update(self, state, action, reward, next_state, alpha, gamma, possible_actions):
        """Update the Q-value using the Q-learning formula."""
        old_value = self.get(state, action)
        next_best = max([self.get(next_state, a) for a in possible_actions], default=0.0)
        new_value = old_value + alpha * (reward + gamma * next_best - old_value)
        self.set(state, action, new_value)