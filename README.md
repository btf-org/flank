# Flank

Build, monitor, and schedule pipelines of R scripts.

- Runs on your laptop
- Integrates with `argparse`
- Saves logs automatically

<img width="410" alt="Screenshot 2026-02-11 at 5 04 09 PM" src="https://github.com/user-attachments/assets/195718fb-832c-4a3d-b81c-26b55482cb58" />   <img width="410" alt="Screenshot 2026-02-11 at 5 04 32 PM" src="https://github.com/user-attachments/assets/affb410b-f1dc-45b7-a8bb-b87cc3c4d141" />

## Quickstart

In this quickstart, you'll install Flank through your terminal. You will use Flank to create some "wrapper scripts" that will run your scripts. Then, you'll create a pipeline from those "wrapper scripts".

1. [Install](#1-install-flank)
2. [Add your scripts (Part I)](#2-add-your-scripts-to-flank)
3. [Add your scripts (Part II)](#3-confirm-that-the-flank-generated-wrapper-scripts-are-correct)
4. [Create pipeline](#4-create-a-pipeline)
5. [Schedule pipeline](#5-schedule-your-pipeline)

### 1. Install Flank

#### Mac

```bash
brew tap btf-org/flank && brew install btf-org/flank/flank && brew services start flank
```

#### Linux

```bash
wget https://github.com/btf-org/flank/releases/download/v0.1.65/flank_0.1.65_amd64.deb && sudo FLANK_USER=$(whoami) apt install ./flank_0.1.65_amd64.deb
```

### 2. Add your scripts to Flank

#### Add a single script

```bash
iflank add myscript.R
```

#### Add multiple scripts

To recursively add all the .R scripts in your project, run this:
```bash
find . -name *.R | iflank add --
```

To add all the R scripts in your current folder, run this:
```bash
ls *.R | iflank add --
```

#### If you're using `argparse`...

Add the `--argparse` flag and Flank will use the output to prepopulate the "wrapper script" with the correct inputs (this saves time on the next step)
```bash
iflank add --argparse myscript.R
```

### 3. Confirm that the Flank-generated "wrapper scripts" are correct

1. Follow the hyperlink outputted by `iflank add` (it'll be something like http://localhost:8083/myscript.R?edit on Mac or http://43.158.119.101:8083/myscript.R?edit on a networked VM)
2. Confirm that Flank created the correct instructions to run your script.

### 4. Create a pipeline

### 5. Schedule your pipeline

## Contact

Feel free to shoot me an email at anguspmitchell@gmail.com
