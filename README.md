# Flank
I'm a data analytics consultant, and I've built a browser <=> CLI tool to simplify some common tasks that are annoyingly complicated in 2026.

# Table of Contents
### Quick Examples
- R
  - [Run an R script on a schedule](#run-an-r-script-on-a-schedule)
  - [Build a pipeline of R scripts](#build-a-pipeline-of-r-scripts)
  - [Run an R script with more memory than you've got on your laptop](#run-an-r-script-with-more-memory-than-youve-got-on-your-laptop)
### Putting it all together
  - [Build a memory-intensive pipeline without Docker, Airflow, etc.](#build-a-memory-intensive-pipeline-without-docker-airflow-etc)

<br>

# Examples

## Run an R script on a schedule

1. [Install Flank](#install-flank)
2. [Start Flank Server](#start-flank-server)
3. [Add your script to Flank](#add-your-script-to-flank)
4. [Parameterize your script](#parameterize-your-script)
5. Create a scheduled job
   1. Navigate to your script in Flank
   2. Click on "Create Cron" at the bottom

## Build a pipeline of R scripts
1. [Install Flank](#install-flank)
2. [Start Flank Server](#start-flank-server)
3. [Add 2 scripts to Flank](#add-your-script-to-flank)
4. [Parameterize your scripts](#parameterize-your-script)
5. Create a pipeline
   1. TBD

## Run an R script with more memory than you've got on your laptop
TBD

## Build a memory-intensive pipeline without Docker, Airflow, etc.
**Common Problem:** Data Scienitst outgrew his laptop -- his nightly pipeline of R scripts needed ~200GB of memory.

**Annoyingly Complicated Default Solution:** Introduce Docker, a deployment process, a cloud running system like AWS Batch, and an orchestration tool like Airflow.

**Simple Alternative:** Run the R scripts directly on a VM (no Docker/AWS Batch), automatically pull changes from GitHub (no deployment tools), and configure the pipeline DAG with Make (no Airflow). Runs natively on Mac/Linux with no dependencies that will ever break. Also store logs in regular files that are easily viewable/downloadable (no AWS Cloudwatch).

**Optimized Solution:** Scale the VM down to a tiny instance size in off-hours, which makes the whole system cheaper than the serverless way.

**See:** [Run an R script on a schedule](#run-an-r-script-on-a-schedule), [Build a pipeline of R scripts](#build-a-pipeline-of-r-scripts), [Always run the latest version of a script](#always-run-the-latest-version-of-a-script), [Strategies for scaling VMs up/down](#strategies-for-optimizing-vm-cost)

# Setup
## Install Flank

### Mac

```bash
brew tap btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu / apt

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time


## Start Flank Server

```bash
flank start
```

## Update Flank

### Mac
```bash
brew update # should update all your "taps", including btf-org/flank
brew install btf-org/flank/flank
```

### Linux / Ubuntu

```bash
# From any directory
wget https://github.com/btf-org/flank/releases/download/v0.1.36/flank_0.1.36_amd64.deb
sudo apt install ./flank_0.1.36_amd64.deb
```

### Windows / Other Linux Distros

Not available at this time

# Guides

## Add Your Script to Flank

If you've run the command and it's in your history...
```bash
# check your history
history
# let's say the history number was 157, print that command without executing
fc -ln 157 157
# now add it to Flank
fc -ln 157 157 | flank add
```

## Parameterize your script


## Always run the latest version of a script

## Strategies for optimizing VM cost
