# Run an R pipeline in the cloud without Docker, Airflow, CI/CD, etc.

This is a way to run a pipeline of R scripts in the cloud with as few moving parts as possible.

## Background

Nick needed to run a pipeline of R scripts every night. He could not do this on his laptop because 1) his laptop did not have enough memory, 2) he did not want to have to always keep his laptop on.

## The problem with existing tools

The problem he ran into is that there is no middle ground between "run a script in RStudio" and "become a full-blown data engineer to orchestrate production scripts in the cloud".

## What did we REALLY need

From first principles, we needed:

- More memory
- DAG runner
- Scheduler
- Log viewer

## Existing tools were not quite right

- **`target`** solved the DAG problem, but not memory, scheduling, or log viewing.
- **Snakemake and Nextflow** had the same issues as `target`
- **GitHub Actions**  solved the memory problem and the scheduling problem, but it's a clumsy DAG runner and it's bad for viewing logs.
- **Docker + AWS Batch + Airflow** solved all four problems, but they created new problems in the forms of CI/CD, DSLs, and cloud configuration.

## The smallest possible solution

We had to use a new computer to solve the memory problem, so we started with a cloud VM with a lot of memory (we used AWS EC2).

Then we solved for DAG running, scheduling, and log viewing natively in Linux. This was a step backwards since Nick is not a CLI wizard. However, we gradually built a website on top of Linux that pulled out all the necessary functionality into an easy-to-use website.

## Steps

