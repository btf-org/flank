# Run an R pipeline in the cloud without Docker, Airflow, CI/CD, etc.

[Skip to the setup guide](#setup-your-own-pipeline)

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

## Setup your own pipeline

There are 6 steps, at a high level. If you want to test this on a Macbook first, you can optionally skip to step #3.

1. [Setup an EC2 box](#setup-an-ec2-box)
2. [Clone your repository onto the EC2 box](#clone-your-repository-onto-the-ec2-box)
3. [Install Flank](#install-flank)
4. [Add your scripts to Flank](#add-your-scripts-to-flank)
5. [Create a pipeline in Flank](#create-a-pipeline-in-flank)
6. [Schedule your pipeline in Flank](#schedule-your-pipeline-flank)

### 1. Setup an EC2 box
### 2. Clone your repository onto the EC2 box
### 3. Install Flank

#### Linux

_In this step, apt installs a webserver and a program that wraps your CLI. It automatically starts the webserver, and uses `whoami` to run it as the current user rather than root._

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

#### Mac

_In this step, Homebrew installs a webserver and a program that wraps your CLI. Then it starts the webserver, running as the user who's logged into the shell._

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

### 4. Add your scripts to Flank

#### 4.a Add your script to Flank

_In this step, Flank will create a "wrapper script" that 1) `cd`s into the directory of your script and 2) runs your script. The wrapper script lives on your computer like any other file, in a folder set up by Flank._

(Swap out `myscript.R` for whatever your script name is)

```
iflank add myscript.R
```

#### 4.b Confirm that the Flank-generated "wrapper script" is correct

_In this step, you'll edit a file on your computer through the Flank web app, but you could also edit the same file through a text editor._

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R?edit)
2. Confirm that Flank created the correct instructions to run your script.

#### 4.c (Optional) Run your script and view output in the browser

_In this step, Flank is calling the "wrapper script" under the hood._

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

### 5. Create a pipeline in Flank

### 6. Schedule your pipeline in Flank
