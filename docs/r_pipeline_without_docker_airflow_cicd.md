# Run an R pipeline in the cloud without Docker, Airflow or CI/CD

## Contents
1. [Case Study](#case-study)
2. [Installation and Setup](#installation-and-setup)
3. [Tradeoffs and Limitations](#tradeoffs-and-limitations)

## Case Study

### Nick's workload outgrew his laptop

Nick needed to run a pipeline of R scripts every night. He could not do this on his laptop because his laptop did not have enough memory. Also he did not want to have to always keep his laptop on.

### He didn't want to become a data engineer

The problem he ran into is that there is no middle ground between "run a script in RStudio" and "become a full-blown data engineer to orchestrate production scripts in the cloud".

### Existing tools were either partial solutions or overkill

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

### We built a solution to meet Nick's needs (and nothing more!)

We had to use a new computer to solve the memory problem, so we started with a cloud VM with enough memory (we used AWS EC2).

Then we solved for DAG running, scheduling, and log viewing natively in Linux. This was initially a step backwards. However, we gradually built an interface on top of Linux that pulled out all the necessary functionality into an easy-to-use website.

- More memory - EC2
- DAG runner - `make` + website
- Scheduler - `cron` + website
- Log viewer - files + website

### We preserved Nick's workflow (RStudio + git)

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

### This solution was half the cost of the AWS "default"

The only cloud cost is the EC2 instance. Nick needed a max instance size of 256GB RAM, so our initial solution was roughly twice the cost of the AWS "default". However, by adding some simple logic to shrink the instance size during off-hours, we were about to reduce the cost by 4x.

| Solution | $ / Month |
|----------|-----------|
| Flank, running 256 GB 24/7 | $1,320 |
| AWS Batch + MWAA | $557 |
| Flank, with simple optimizations | $247 |

## Installation and Setup

There are 6 steps that can be accomplished with as few as 4 CLI commands. 

(If you want to test this on a Macbook first, you can optionally skip to step #3.)

1. [Setup a VM](#1-setup-a-vm)
2. [Clone your repository onto the VM](#2-clone-your-repository-onto-the-vm)
3. [Install Flank](#3-install-flank)
4. [Add your scripts to Flank](#4-add-your-scripts-to-flank)
5. [Create a pipeline in Flank](#5-create-a-pipeline-in-flank)
6. [Schedule your pipeline in Flank](#6-schedule-your-pipeline-in-flank)

### 1. Setup a VM

#### 1.a Launch an EC2 instance

_In this step, you'll create a virtual machine in AWS with enough memory to run your pipeline. We recommend starting with an AMI that has RStudioServer pre-installed so you can edit scripts directly in the browser. If you're an Azure or GCP user, there are plenty of guides for doing this same process there._

1. Go to the [AWS EC2 console](https://console.aws.amazon.com/ec2/) and click **Launch Instance**
2. Search for **RStudio** in the Community AMIs tab and select one of the RStudio Server AMIs (e.g. from Louis Aslett — these are well-maintained and free to use)
3. Choose an instance type with enough memory for your workload. If you're not sure, start with `r6a.large` (16 GB) and resize later
4. Create or select a key pair and save the `.pem` file somewhere safe
5. Under **Network Settings**, make sure SSH (port 22) is open. If you plan to access the Flank web UI from your browser, also open port 8083
6. Launch the instance

#### 1.b Connect to your instance

_In this step, you'll SSH into your new machine to confirm it's working. You only need to do this once — after that, you can use RStudioServer and the Flank web UI instead._

(Swap out `your-key.pem` and the hostname for your own values)

```bash
ssh -i your-key.pem ubuntu@ec2-xx-xx-xx-xx.compute-1.amazonaws.com
```

#### 1.c (Optional) Confirm RStudioServer is running

_RStudioServer runs on port 8787. If you open that port in your security group, you can edit R scripts on the EC2 box directly from your browser — no local setup required._

1. Open port 8787 in your instance's security group
2. Navigate to `http://ec2-xx-xx-xx-xx.compute-1.amazonaws.com:8787` in your browser
3. Log in with the default credentials from the AMI documentation

### 2. Clone your repository onto the VM

_In this step, you'll pull your R scripts onto the EC2 machine. The pipeline will run them from here, and will pull the latest version of `main` each time it runs — so your normal git push workflow stays intact._

SSH into your instance (or use the RStudioServer terminal) and clone your repo:

```bash
git clone https://github.com/your-org/your-repo.git
```

If your repository is private, the easiest path is to [create a GitHub personal access token](https://github.com/settings/tokens) and clone with it embedded in the URL:

```bash
git clone https://your-token@github.com/your-org/your-repo.git
```

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

## Tradeoffs and Limitations

### Machine Management

The main tradeoff is that Nick is accepting a little bit of EC2 machine management in order to keep everything else as simple as possible.

It's not hard to imagine a situation where the complexity of the machine management begins to outweigh the benefits of this simplicity:

- Thousands of simultaneous jobs
- TB of simultaneous memory
- Conflicting OS-level dependencies

For context, Nick's pipeline is 30 tasks, as many as 8 in parallel, with a peak memory consumption of 200 GB.

### Pipeline Complexity

Another tradeoff is that we took an "80/20" approach to pipeline features. This system can run a DAG. It is not designed for dynamic DAG generation, retries and backoffs, or branching based on runtime state.
