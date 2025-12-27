# Flank
I'm a data analytics consultant. Flank is a set of tools that I've built to speed up common tasks that annoyingly complicated in 2025.

### Examples
- R
  - [Run an R script on a schedule](#run-an-r-script-on-a-schedule)
  - [Build a pipeline of R scripts](#build-a-pipeline-of-r-scripts)

### Case Studies
- [Building a memory-intensive pipeline without Docker, Airflow, etc.](#building-a-memory-intensive-pipeline-without-docker-airflow-etc)

### Setup
- [Install Flank](#install-flank)
  - Mac
  - Linux/Ubuntu
  - Windows
- [Start Flank Server](#start-flank-server)
- [Update Flank](#update-flank)

### Basics
- [Add Your Script to Flank](#add-your-script-to-flank)

# Examples
## Run an R script on a schedule

1. Prerequisites
   - [Install Flank](#install-flank)
   - [Start Flank Server](#start-flank-server)
2. [Add your script to Flank](#add-your-script-to-flank)
3. Schedule exeuction of script through Flank website

## Build a pipeline of R scripts
1. Prerequisites
   - [Install Flank](#install-flank)
   - [Start Flank Server](#start-flank-server)
2. [Add your script to Flank](#add-your-script-to-flank)
3. Schedule exeuction of script through Flank website
   
# Case Studies
## Building a memory-intensive pipeline without Docker, Airflow, etc.

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

## Add Your Script to Flank

1. Run the following command
  ```bash
  flank add helloWorld.R
  
  # Example output:
  # localhost:8083/helloWorld.R
  ```
2. Add parameters in Flank
   - Go to URL outputted above
   - Click on "Edit" at the bottom
