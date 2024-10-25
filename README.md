<img width="474" alt="Screenshot 2024-10-25 at 15 36 22" src="https://github.com/user-attachments/assets/8781d487-0538-4dd8-be8d-edad9cd1fe2a">


The Dining Philosophers problem models a scenario in which a group of philosophers engage in the activities of eating, thinking, and sleeping.
These philosophers are seated at a round table with an equal number of forks, and each philosopher requires two forks to eat.
However, each pair of adjacent philosophers shares a fork. The primary challenge is to ensure that the philosophers can perform their activities without starving or blocking each other.

In my implementation, I represented each philosopher as a `thread` and each fork as a `mutex`. This setup allows philosophers to pick up the forks they need while locking them to ensure synchronization.
Since they cannot all start simultaneously, I introduced a slight delay for the even-numbered philosophers at the beginning to manage concurrency.
