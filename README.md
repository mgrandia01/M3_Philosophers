# 🍝 Philosophers

> A multi-threaded concurrency solution to the classic Dining Philosophers problem in C using POSIX threads and mutex synchronization.

## 📖 Overview

`Philosophers` is a concurrent systems programming project designed to tackle thread synchronization, shared resource competition, race conditions, and deadlock avoidance. The simulation models Dijkstra's classic problem: a set of philosophers seated around a table sharing a limited number of forks, alternating between thinking, eating, and sleeping without starving or causing deadlocks.

## ⚙️ Technical Constraints & Architecture

- **Language:** C (compiled with `gcc -Wall -Wextra -Werror`).
- **Concurrency & Synchronization:** POSIX Threads (`pthread_create`, `pthread_join`, `pthread_detach`) and Mutex locks (`pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`).
- **Timing Precision:** High-resolution time tracking using `gettimeofday` down to millisecond accuracy.
- **Race Condition Prevention:** Zero data races allowed. Checked and audited using ThreadSanitizer (`-fsanitize=thread`) and Valgrind (Helgrind/DRD).
- **Memory Safety:** Strict heap and thread resource lifecycle management. Guaranteed zero memory leaks or unjoined thread handles upon exit.
- **Standards:** 100% compliant with 42's **Norminette** coding standard.

---

## ✨ Key Features & Technical Implementation

- **Thread-Per-Entity Model:** Each philosopher executes inside an independent POSIX thread running a cyclic state machine (`Eat` -> `Sleep` -> `Think`).
- **Mutex-Protected Resources:** Each fork is represented as an individual `pthread_mutex_t` to ensure atomic resource acquisition and prevent concurrent access.
- **Asymmetric Locking & Deadlock Prevention:** Implemented strict resource hierarchy rules (e.g., alternating fork acquisition order between odd and even threads) to completely eliminate circular wait conditions.
- **Thread-Safe Console Output:** Console logging (`printf`) is guarded by a dedicated display mutex to prevent message interleaving across concurrent threads.
- **Asynchronous Monitor Routine:** Includes an active monitoring mechanism that tracks timestamps since the last meal for every philosopher, terminating the entire simulation within milliseconds of a starvation event.

---

## 🛠️ Quickstart & Execution

### Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
