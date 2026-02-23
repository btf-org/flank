# An app for an R developer to build/monitor his pipelines without a Data Engineer

This is like "Airflow lite", designed for an R developer, Nick, who did not want to learn/maintain Airflow, Docker, etc.

It currently works on Mac and Debian-based systems (Debian, Ubuntu)

## Contents
1. [Case Study](#case-study)
2. [Installation and Setup](#installation-and-setup)
3. [Tradeoffs and Limitations](#tradeoffs-and-limitations)
4. [Contact](#contact)

## Case Study

### Nick's workload outgrew his laptop

Nick needed to run a pipeline of R scripts every night. He could not do this on his laptop because his laptop did not have enough memory. Also he did not want to have to always keep his laptop on.

### He didn't want to become a data engineer

The problem he ran into is that there is no middle ground between "schedule a cron job on your laptop" and "become a full-blown data engineer to orchestrate production scripts in the cloud".

### Existing tools were either partial solutions or overkill

Nick needed the following features:

- More memory
- A way to specify / run a pipeline
- Scheduler
- An interface to check the status, drill into specific logs, etc.

We surveyed the existing tools, but they were either partial solutions or overkill:

- **`target`** solved the pipeline problem, but that's it.
- **Snakemake and Nextflow** are like `target`.
- **GitHub Actions**  solved the memory problem and the scheduling problem, but it's a clumsy DAG runner and it's bad for viewing logs.
- **Docker + AWS Batch + Airflow** solved all four problems, but they created new problems in the forms of CI/CD, DSLs, and cloud configuration.

The one tool we did not seriously evaluate was **Posit Connect**. Nick's system was already deeply integrated with AWS S3, and Posit Connect seems to be designed for large, enterprise use cases.

### We built the simplest thing we could think of

We needed more memory, so we either needed to utilize a serverless cloud service like AWS Batch or to build something that would work on a VM. The problem with a serverless solution is that it adds new complexity in the form of deployment, reproducing the environment, tracking down bugs in logs, etc. So we decided to build on a VM with enough memory (we used EC2).

Once we settled on a VM, we solved for pipelining, scheduling, and log viewing natively with command line tools. This was initially a step backwards since Nick is not a command line user. However, we gradually built an interface on top of the command line that pulled out all the necessary functionality into an easy-to-use website.

### We preserved Nick's workflow (RStudio + git)

The main benefit to Nick is that he gets the basic features of Airflow without having to learn anything new or add any meaningful process. He gets to continue spending time in his happy place (RStudio). When he needs to make an update one of his scripts, he simply pushes a change to his repo. When he needs to make changes to the pipeline, he can do so through the website.

### This solution was half the cost of the AWS "default"

The only cloud cost is the EC2 instance. Nick needed a max instance size of 256 GB RAM, so our initial solution was roughly twice the cost of the AWS "default". However, by adding some simple logic to shrink the instance size during off-hours, we were about to reduce the cost by 4x.

| Solution | $ / Month |
|----------|-----------|
| Flank, running 256 GB 24/7 | $1,320 |
| AWS Batch + MWAA | $557 |
| Flank, with simple optimizations | $247 |

However, the main cost savings was in terms of Nick's time. It's more difficult to put an exact number on that, but we saved him from having to learn / use / maintain Airflow, Docker, and AWS Batch. Conservatively, that probably saved him 10% of his development time, arguably more.

### Minimal dependencies have meant minimal maintenance

Nik has texted me a handful of times when the website has crashed, but there is very little to maintain since everything is running on native shell tools. We've built a website to make those shell tools more accessible, but that's about it.

## Installation and Setup

(If you already have a machine with enough memory or you just want to test on your Macbook, you can optionally skip to step #3.)

1. [Install Flank](#1-install-flank)
2. [Add your scripts to Flank](#2-add-your-scripts-to-flank)
3. [Create a pipeline in Flank](#3-create-a-pipeline-in-flank)
4. [Schedule your pipeline in Flank](#4-schedule-your-pipeline-in-flank)


### 1. Install Flank

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

### 2. Add your scripts to Flank

#### 2.a Add your script to Flank

_In this step, Flank will create a "wrapper script" that 1) `cd`s into the directory of your script and 2) runs your script. The wrapper script lives on your computer like any other file, in a folder set up by Flank._

(Swap out `myscript.R` for whatever your script name is)

```
iflank add myscript.R
```

#### 2.b Confirm that the Flank-generated "wrapper script" is correct

_In this step, you'll edit a file on your computer through the Flank web app, but you could also edit the same file through a text editor._

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R?edit)
2. Confirm that Flank created the correct instructions to run your script.

#### 2.c (Optional) Run your script and view output in the browser

_In this step, Flank is calling the "wrapper script" under the hood._

You should be presented with a page with \[ Run \] button where you can trigger your script. Run it and you should see the output in the browser. 

### 3. Create a pipeline in Flank

### 4. Schedule your pipeline in Flank

## Tradeoffs and Limitations

### Single Machine Architecture

Initially there was the question of whether this system should run on one machine, or whether it should be some sort of distributed delegation architecture.

We opted for one machine because Nick's workload could fit on one machine.

The benefit is that it's easy to debug. For Nick, the easiest environment in which to debug is his laptop. Next is RStudio Server on a VM (that's what we set up). Then a VM. Then a Docker container. And finally a distributed system.

The downside is that Nick has to think about memory and storage (very occasionally) unlike a purely serverless architecture. 

### Single OS Environment

We also debated whether each task should be containerized, or whether everything should just run on one OS.

We opted for one OS because Nick is a one-man operation with a consistent set of dependencies.

Once again the benefit is that it's easy to debug (see above).

There really was no downside for Nick, although if he had pipeline tasks that needed different OS-level dependencies it would introduce some complexity.

### Simple Pipeline Rules

We had to decide whether to write the pipeline logic ourselves or whether to piggyback on an existing tool.

We decided to piggyback off `make` because 1) it satisfied all of Nick's needs, 2) it's extremely stable and ubiquitous, 3) the things that make it hard-to-use could be alleviated with a little UI. 

The benefit is that it just works and we've never thought about it.

There was no downside for Nick, but if his pipeline needs became more complex, it would stretch this design. (e.g. dynamic DAG generation, retries and backoffs, or branching based on runtime state)

### Simple UI

This system has a website for monitoring and editing pipelines, so we had to decide what it really needed to support.

Ultimately, we decided that it needed to have 1) a History page, 2) a way to download logs, 3) a way to monitor the status of the pipeline DAG, and 4) a way to edit pipelines. This allowed us to use a very simple web architecture -- basically 1990s web technology. 

The benefit is that it's simple -- both from the standpoint of being easy to use and reliable/stable.

The downside is that it limits the complexity of future designs.

### Bash as a specification language

We debated whether to make the specification of pipelines pure R (e.g. using a tool like `target`) or whether to roll something ourselves.

The developer experience we wanted was to make it "as simple as running `Rscript myscript.R` from the command line". We wanted the saving of logs to happen automatically. And we actually needed to run a couple Python scripts too. So for that reason, there is some wrapper code around each task. We decided to use bash, because it's just redirecting the output to a file. And then we used `make` for the pipeline configuration. Given that, if it were purely R, Nick would have either learn a new library anyway (or wrap the bash calls in a `system()` call), we considered this overhead to be acceptable.

The benefit is that Nick keeps the same "mental API" for running things (e.g. `Rscript myscript.R`)

The downside is that as things get more complicated, that complexity tends to creep into bash one-liners.

## Contact

Feel free to shoot me an email at anguspmitchell@gmail.com.
