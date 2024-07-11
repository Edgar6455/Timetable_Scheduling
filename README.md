# Assignment: University Timetabling System
Objective: Design and develop a program that organizes university course schedules, ensuring instructors are assigned to courses according to their availability and preferences. Courses also have preferred time slots.

The assignment involves managing both soft and hard constraints.
The scheduling algorithm must satisfy all hard constraints and as many soft constraints as possible.

### Hard constraints:
- Each course must be scheduled exactly once in an available time slot and assigned to an instructor
- An instructor can only be assigned to a course if they are available during the corresponding time slot
- An instructor cannot be scheduled to teach more than one course in the same time slot

### Soft constraints:
- Courses should be scheduled in preferred time slots if possible
- Instructors should be assigned to their preferred courses if possible

See more details about the assignment by [this](https://docs.google.com/document/d/1iGzcBMqbpLfBhPh7xrKGplsiqojhlKjDzB4THlBh2ho/edit?usp=sharing) link.


## Installation and Setup
This is a **CMake** project.

If you want to run the program with an IDE, there are 2 configurations. One configuration is **Timetabling** with the same name as the executable. Second configuration is gtest with the executable  **Test**. It is advised to run both configurations on external console.

To build this project, you can simply run bash script `build.sh` in the directory `scripts`. This will make a directory `bin` in the project with 2 executable files.

### Docker:
There is also a `dockerfile` in the project which will make a new environment with all the necessary dependencies and will build the project. Additionally, in the directory `scripts` there are scripts to help install **Docker** and run the `dockerfile`.


## Usage
Running the **Test** executable will execute multiple test cases using the **gtest** framework, covering each scheduling algorithm and *JSON* file operations. These tests are designed to simulate various scenarios and ensure comprehensive testing of the system's functionalities.

Running the **Timetabling** executable will run an interactive console program, which will demonstrate scheduling algorithms' functionality in a list of provided options as input data. This interactive menu also supports options like generating random dataset to run algorithms on, or constructing a new dataset from scratch.


## Algorithms used
The project currently features three distinct scheduling algorithms, each designed for different purposes. Additionally, a **penalty system** has been introduced to evaluate the quality of a timetable. The fewer penalty points a timetable accumulates, the better it is considered.

### Penalty system:
For each assignment, the system assigns penalty points as follows:
- 1 penalty point if a course is not scheduled in it's preferred time slot.
- 2 penalty points if an instructor is assigned to a course they do not prefer.
- 3 penalty points if both conditions above are violated.

### Dummy Scheduler:
The Dummy Scheduler is the first algorithm I developed. Its primary objective is to satisfy all hard constraints while being as simple and quick as possible. The algorithm operates as follows:

1. Iterate through each available time slot. If at least one instructor is available during a specific time slot, it is preferable to assign a course to that slot. These slots are referred to as *non-empty* time slots. The maximum number of such assignments is determined by the *min(non-empty time slots count, courses count)*. The algorithm stops if the number of assignments reaches the number of courses, as only one course can be scheduled per time slot.
2. For each time slot, iterate through every instructor available during that period.
3. Check the instructor's preferred courses. If any of these courses have not yet been assigned, assign the instructor to their preferred course in that time slot.
4. If no instructors in that time slot have unassigned preferred courses, assign the first available instructor to the first available course in that time slot.

#### Time complexity:
The time complexity of the Dummy Scheduler is *O(min(T,C) ⋅ I ⋅ C*), where *T* is the number of the time slots, *I* is the maximum number of available instructors per time slot and *C* is the maximum number of preferred courses per instructor. This time complexity can also be represented as *O(N^3)*, where *N* is *max(T, I, C)*.

#### Advantages:
- Simplicity: The algorithm is straightforward and easy to understand, making it simple to implement and debug.
- Efficiency: It is designed to quickly find a solution that satisfies all hard constraints, ensuring that each course is scheduled exactly once and instructors are not double-booked.
- Flexibility with Soft Constraints: While prioritizing hard constraints, the algorithm also attempts to satisfy as many soft constraints as possible, improving the overall quality of the timetable.

#### Disadvantages:
- First-Fit Approach: The first-fit method for assigning instructors and courses in time slots can lead to less optimal scheduling as it does not consider future assignments, potentially missing better overall solutions, resulting in higher penalty points.


### Brute Force Scheduler:

The Brute Force Scheduler is a comprehensive algorithm developed to find the optimal solution by exhaustively exploring all possible permutations of time slots, instructors, and courses. Its primary objective is to satisfy all hard constraints while also aiming to meet the maximum number of soft constraints. The algorithm operates as follows:

1. Iterate through each available time slot, identifying non-empty time slots where at least one instructor is available. Generate all permutations of these non-empty time slots.
2. For each permutation of non-empty time slots, generate permutations of instructors who are available in those time slots.
3. For each combination of time slot and instructor permutations, generate all permutations of courses.
4. For each generated timetable, calculate penalty points based on soft constraints. Compare each timetable with the one with less penalty points and select that timetable as the new best. Also save timetables with the same penalty points as alternatives for the best timetable.

#### Time Complexity:

The time complexity of the Brute Force Scheduler is *O(2<sup>T</sup> ⋅ I<sup>T</sup> ⋅ C<sup>min(C, T)</sup>)*:

- Time Slot Permutations: *O(2<sup>T</sup>)*, where *T* is the number of non-empty time slots.
- Instructor Permutations: *O(I<sup>T</sup>)*, where *I* is the maximum number of available instructors per time slot.
- Course Permutations: *O(C<sup>min(C, T)</sup>)*, where *C* is the number of courses.

#### Advantages:

- Optimal and Multiple Solutions: By exploring all possible permutations, the algorithm ensures the best possible timetable with the fewest penalty points and identifies all other timetables that achieve the same minimum penalty, providing multiple optimal solutions.
- Comprehensive: It considers all potential combinations, ensuring no possible solution is overlooked.
- All Constraints Satisfaction: This approach not only satisfies all mandatory hard constraints but also maximizes the satisfaction of optional soft constraints.

#### Disadvantages:

- High Computational Complexity: The exhaustive search approach results in exponential time complexity, making it computationally intensive and impractical for large datasets. The algorithm requires significant computational resources and time, especially as the number of time slots, instructors, and courses increases.
- Scalability Issues: Due to its exponential growth, the algorithm may not scale well for larger universities with a high number of courses, instructors and time slots.


### Hybrid Scheduler:

The Hybrid Scheduler combines the strengths of both the Dummy Scheduler and the Brute Force Scheduler to find a high-quality timetable efficiently. The primary objective is to utilize the Dummy Scheduler to quickly find a feasible solution and then refine it using the Brute Force Scheduler to minimize penalty points. The algorithm operates as follows:

1. The algorithm starts by running the Dummy Scheduler to generate an initial feasible timetable. This timetable is evaluated, and its penalty points are calculated.
2. The assignments from the Dummy Scheduler are sorted based on their penalty points. The assignments are divided into two groups: those with penalties below a certain threshold are kept, while the others are subject to improvement.
 
       A threshold is determined based on the sorted assignments. This threshold is used to keep at least 20% of the assignments from the Dummy Scheduler.

3. The Brute Force Scheduler is run on the remaining assignments to find the optimal timetables.
4. The results from the Brute Force Scheduler are combined with the base timetable to form the final timetables.

#### Time Complexity:

The time complexity of the Hybrid Scheduler is influenced by both the Dummy Scheduler and the Brute Force Scheduler.
However, the Hybrid Scheduler significantly reduces the input size for the Brute Force Scheduler by keeping high-quality assignments from the Dummy Scheduler, leading to a more practical overall complexity.

#### Advantages:

- Efficiency and Quality: The Hybrid Scheduler leverages the quick initial solution and refines it, ensuring high-quality timetables with reduced computational effort.
- Scalability: The Hybrid approach reduces the input size for the Brute Force Scheduler, making it more scalable for larger datasets compared to using the Brute Force Scheduler alone.

#### Disadvantages:

- Resource Intensive: While it reduces the input size for the Brute Force Scheduler, the Hybrid Scheduler still requires significant computational resources for larger datasets.
