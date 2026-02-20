# Run an R pipeline in the cloud without Docker, Airflow, CI/CD, etc.

## Nick's workload outgrew his laptop

Nick needed to run a pipeline of R scripts every night. He could not do this on his laptop because his laptop did not have enough memory. Also he did not want to have to always keep his laptop on.

## He didn't want to become a data engineer

The problem he ran into is that there is no middle ground between "run a script in RStudio" and "become a full-blown data engineer to orchestrate production scripts in the cloud".

## Existing tools were either partial solutions or overkill

Nick needed the following features:

- More memory
- DAG runner
- Scheduler
- Log viewer

We surveyed the existing tools, but they were either partial solutions or overkill:

- **`target`** solved the DAG problem, but that's it.
- **Snakemake and Nextflow** are like `target`.
- **GitHub Actions**  solved the memory problem and the scheduling problem, but it's a clumsy DAG runner and it's bad for viewing logs.
- **Docker + AWS Batch + Airflow** solved all four problems, but they created new problems in the forms of CI/CD, DSLs, and cloud configuration.

## We added the bare minimum to meet Nick's needs

We had to use a new computer to solve the memory problem, so we started with a cloud VM with enough memory (we used AWS EC2).

Then we solved for DAG running, scheduling, and log viewing natively in Linux. This was initially a step backwards. However, we gradually built an interface on top of Linux that pulled out all the necessary functionality into an easy-to-use website.

- More memory - EC2
- DAG runner - `make` + website
- Scheduler - `cron` + website
- Log viewer - files + website

## Nick's workflow is still just RStudio + git

#### Updating scripts in the pipeline

1. Nick makes a change to the script in RStudio, on his laptop
2. He pushes changes to the `main` branch of his repository
3. The EC2 box running his pipeline pulls `main` the next time it runs

#### Debugging

1. Nick goes to the website running on his EC2 box
2. He drills down into a particular run (the run history is saved) and inspects the logs
3. The EC2 box actually runs RStudioServer, so he can make the change directly on that machine through RStudioServer, or he can make the change locally and push to `main` (see above)

#### Updating the pipeline

1. Nick goes to the website running on his EC2 box
2. He navigates to the pipeline and edits a text file that defines the DAG

## Tradeoffs and Limitations

The big tradeoff is that Nick is accepting a little bit of EC2 machine management in order to keep everything else as simple as possible.

It's not hard to imagine a situation where the complexity of the machine management begins to outweigh the benefits of this simplicity. If you had thousands and thousands of cron jobs, I could see that being the case. Having said that, his pipeline is running 30 tasks, as many as 8 in parallel, with a peak memory consumption of 200 GB. We've added some spinup/spindown logic to keep the EC2 instance type very small during off hours, so the whole system is actually cheaper that it would be if it were running on Docker + AWS Batch.

On the flipside, if everything had run on Nick's laptop and hardware had not been a constraint, then we could have solved the problem with `target`, `cron`, and some file organization.

## Steps to setup your own pipeline

